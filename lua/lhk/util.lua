local lhk_core = require 'lhk_core'

local G = {}

---Creates a keymap from `from` to `to`
---@param from integer[] List of keycodes
---@param to integer[] List of keycodes
---@return lhk.Layer
function G.keymap(from, to)
	if #from ~= #to then
		error('`from` and `to` have different lengths', 2)
	end

	local layer = lhk_core.layer.new()

	for i = 1, #from, 1 do
		if from[i] ~= to[i] then
			layer:register(from[i], lhk_core.hotkey.new {
				actions = {
					lhk_core.action.new(to[i], 'Mirror')
				}
			})
		end
	end

	return layer
end

return G
