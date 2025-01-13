---@meta

local G = {}

---Start the input loop
---@param input string A path to an input file, usually `/dev/input/event#`
---@param output string The name of the input device to be created
function G.start(input, output)
end

--- Stop the input loop
function G.stop()
end

---Set `root` to be the first layer called during the input loop
---@param root lhk.Layer
function G.set_root(root)
end

---@class lhk.Layer
local Layer = {}

G.layer = {}

---Create a new layer.
---@return lhk.Layer
function G.layer.new()
end

---Configure `next_layer` to be called after `self`
---@param next_layer lhk.Layer|nil The layer to be linked to `self`
function Layer.set_next_layer(next_layer)
end

return G
