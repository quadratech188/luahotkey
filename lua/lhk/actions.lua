require 'keycodes.global'
lhk_core = require 'lhk_core'

G = {}

---Send a 'standard hotkey'
---@param reference lhk.Keynode
---@param modifiers integer[]
---@param key integer
---@return lhk.Action[]
function G.standard_hotkey(reference, modifiers, key)
	local result = {}

	local all_modifiers = {
		[KEY_LEFTSHIFT] = false,
		[KEY_LEFTCTRL] = false,
		[KEY_LEFTMETA] = false,
		[KEY_LEFTALT] = false,
		[KEY_RIGHTALT] = false,
		[KEY_RIGHTMETA] = false,
		[KEY_RIGHTCTRL] = false,
		[KEY_RIGHTSHIFT] = false
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

	for modifier, _ in pairs(all_modifiers) do
		result[#result+1] = lhk_core.action.enforce(reference, modifier)
	end

	return result
end

return G
