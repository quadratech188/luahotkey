local lhk_core = require 'lhk_core'

local keylogger = lhk_core.layer.new()

local codes = require 'keycodes.table'

local hotkey = lhk_core.hotkey.new {
	actions = {
		lhk_core.action.custom(
		---@param update lhk.Update
		function (update)
			print(codes[update.keycode], update.transition)
		end
		),
	},
	passthrough = true
}

for i = 0, 255, 1 do
	keylogger:register(i, hotkey)
end

return keylogger
