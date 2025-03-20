local settings_core = require 'lhk_core'.settings

---@class lhk.Settings
---@field grab boolean?
---@field input string?
---@field output string?
---@field use_socket boolean?
---@field socket string?
---@field socket_handler function<string>?

---Use a table to change lhk settings
---@param settings lhk.Settings
function settings_core.set(settings)
	for key, value in pairs(settings) do
		if settings_core[key] == nil then
			error('Invalid key: ' .. key, 2)
		end

		settings_core[key](value)
	end
end

return settings_core
