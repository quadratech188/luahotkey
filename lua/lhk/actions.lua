local k = require 'keycodes.local'
local lhk_core = require 'lhk_core'

G = {}

---Send a 'standard hotkey'
---@param reference lhk.Keynode
---@param modifiers integer[]
---@param key integer
---@return lhk.Action[]
function G.standard_hotkey(reference, modifiers, key)
	local result = {}

	local all_modifiers = {
		[k.KEY_LEFTSHIFT] = false,
		[k.KEY_LEFTCTRL] = false,
		[k.KEY_LEFTMETA] = false,
		[k.KEY_LEFTALT] = false,
		[k.KEY_RIGHTALT] = false,
		[k.KEY_RIGHTMETA] = false,
		[k.KEY_RIGHTCTRL] = false,
		[k.KEY_RIGHTSHIFT] = false
	}

	for _, modifier in pairs(modifiers) do
		result[#result+1] = lhk_core.action.require_down(reference, modifier)
		all_modifiers[modifier] = true
	end

	for modifier, used in pairs(all_modifiers) do
		if not used then
			result[#result+1] = lhk_core.action.require_up(reference, modifier)
		end
	end

	result[#result+1] = lhk_core.action.press(key)
	result[#result+1] = lhk_core.action.release(key)

	for modifier, used in pairs(all_modifiers) do
		if used then
			result[#result+1] = lhk_core.action.enforce_from_down(reference, modifier)
		else
			result[#result+1] = lhk_core.action.enforce_from_up(reference, modifier)
		end
	end

	return result
end

return G
