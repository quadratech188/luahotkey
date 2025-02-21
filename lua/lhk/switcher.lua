local math = require 'math'
local lhk_core = require 'lhk_core'

local G = {}

---@class lhk.Switcher
---@field keynode lhk.Keynode
---@field weights table<integer, integer>
---@field layers lhk.Layer[]
local Switcher = {}
Switcher.__index = Switcher

local press = lhk_core.criteria.new {
	transition = 'Press'
}
local release = lhk_core.criteria.new {
	transition = 'Release'
}

---Create a new lhk.Switcher
---@param modifiers integer[]
---@return lhk.Switcher
function G.new(modifiers)
	---@type lhk.Switcher
	local self = setmetatable({
		keynode = lhk_core.keynode.new(),
		weights = {},
		layers = {}
	}, Switcher)

	local size = 1
	for _, modifier in pairs(modifiers) do
		self.weights[modifier] = size
		size = 2 * size
	end

	for i = 0, size - 1, 1 do
		self.layers[i] = lhk_core.layer.new()
	end

	for index, layer in pairs(self.layers) do
		for modifier, weight in pairs(self.weights) do
			if math.floor(index / weight) % 2 == 0 then
				layer:register(modifier, lhk_core.hotkey.new {
					actions = {
						lhk_core.action.set_next(self.keynode, self.layers[index + weight])
					},
					criteria = press,
					passthrough = true
				})
			else
				layer:register(modifier, lhk_core.hotkey.new {
					actions = {
						lhk_core.action.set_next(self.keynode, self.layers[index - weight])
					},
					criteria = release,
					passthrough = true
				})
			end
		end
	end

	self.keynode:set_next(self.layers[0])

	return self
end

---@param modifiers integer[]
function Switcher:at(modifiers)
	local index = 0
	for _, modifier in pairs(modifiers) do
		index = index + self.weights[modifier]
	end
	return self.layers[index]
end

---@param next lhk.Node
function Switcher:set_next(next)
	for _, layer in pairs(self.layers) do
		layer:set_next(next)
	end
end

return G
