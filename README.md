# luahotkey
luahotkey is a keyboard remapper, as a luarocks package.
# Installation
luahotkey only builds with Lua 5.1 (or LuaJIT). You will also need to install it as root, as you usually need root permissions to modify input devices.
```
sudo luarocks install --server=https://luarocks.org/dev luahotkey --lua-version=5.1
```

# Example script
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
