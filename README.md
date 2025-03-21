# luahotkey
luahotkey is a keyboard remapper, as a luarocks package.
## Installation
`luahotkey` only builds for Lua version 5.1 (or LuaJIT). You will also need to install it as root, as you need root permissions to modify input devices.
```
sudo luarocks install --server=https://luarocks.org/dev luahotkey --lua-version=5.1
```
`luahotkey` depends on `libevdev`, so you may have to install something like `libevdev-devel` and pass in the location of the header files.
## Why would I use this instead of something more established?
1. As opposed to other keyboard remappers that have their own DSLs, `luahotkey` is a package for a general-purpose programming language. This makes achieving very specific behavior relatively easy, as you can just code it in Lua.
2. Almost all keyboard remappers use the concept of 'layers' - a set of remappings for a set of keys. `luahotkey` has layers too, but the difference is that you can chain layers together. This makes certain behavior possible:
	- Put your preferred keyboard layout at the front of the layer chain, and all further modifications will just follow the new layout.
	- Have a layer for systemwide hotkeys, and another for application-specific hotkeys which you can switch out with the IPC support.

These advantages aside, please remember that this is still very untested software that is prone to change.
## Documentation
The only documentation currently available is [lua_ls](https://luals.github.io/) annotations. You may have to do [modify your workspace.library config](https://luals.github.io/wiki/configuration/#using-built-in-lsp-client) for it to properly show up in your editor.
## Example script
```lua
local lhk = require 'lhk'
local rapidjson = require 'rapidjson'

require 'keycodes.global'

local modifiers = {
	KEY_LEFTSHIFT,
	KEY_LEFTCTRL,
	KEY_LEFTMETA,
	KEY_LEFTALT
}

-- This allows you to set separate hotkeys for each modifier key combination.
local main = lhk.switcher.new(modifiers)

-- Ctrl-Meta-Alt-Q quits the program
main:at{KEY_LEFTCTRL, KEY_LEFTMETA, KEY_LEFTALT}:register(KEY_Q, lhk.hotkey.new {
	actions = {
		lhk.action.custom(lhk.stop)
	}
})

local firefox = lhk.switcher.new(modifiers)

-- Map Alt+Up to Alt+Left
firefox:at{KEY_LEFTALT}:register(KEY_UP, lhk.hotkey.new {
	actions = lhk.actions.standard_hotkey(main.keynode, {KEY_LEFTALT}, KEY_LEFT),
	criteria = lhk.criteria.new {
		transition = 'Press'
	}
})

-- Map Alt+Down to Alt+Right
firefox:at{KEY_LEFTALT}:register(KEY_DOWN, lhk.hotkey.new {
	actions = lhk.actions.standard_hotkey(main.keynode, {KEY_LEFTALT}, KEY_RIGHT),
	criteria = lhk.criteria.new {
		transition = 'Press'
	}
})

---@type table<string, lhk.Switcher>
local application_layers = {
	['org.mozilla.firefox'] = firefox
}

-- All events will be passed to `main`
lhk.set_root(main.keynode)

lhk.settings.set {
	grab = false, -- 'grabbing' an input device prevents other processes from accessing it.
	              -- I recommend setting it to `false` while testing.
	input = '/dev/input/event3',
	output = 'test',
	use_socket = true, -- Use a socket to receive outside events
	socket = 'socket',
}

-- Receive current windo info from sway
os.execute("sh -c \"swaymsg -m -t subscribe [\\'window\\'] > socket &\"")

local buffer = ''
lhk.settings.socket_handler(function (message)
	buffer = buffer .. message

	while (true) do
		local newline_pos = buffer:find('\n')
		if not newline_pos then break end
		local single_message = buffer:sub(1, newline_pos - 1)
		buffer = buffer:sub(newline_pos + 1)
		

		local decoded_message = rapidjson.decode(single_message)
		local index = decoded_message.container.app_id
		print(index)
		-- Connect an application layer to the main layer
		main:extend(application_layers[index])
	end
end)

lhk.start()
```
