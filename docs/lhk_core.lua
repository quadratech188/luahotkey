---@meta

local G = {}

---@alias lhk.State 'Up' | 'Down'

---@alias lhk.Transition 'Press' | 'Release' | 'Autorepeat'

---@alias lhk.Action_type 'Press' | 'Release' | 'Autorepeat' | 'Mirror' | 'Require_down' | 'Require_up' | 'Custom'

---@alias lhk.Node lhk.Layer | lhk.Keynode | nil

---Start the input loop.
---@param input string A path to an input file, usually `/dev/input/event#`.
---@param output string The name of the input device to be created.
function G.start(input, output)
end

--- Stop the input loop.
function G.stop()
end

---Set `root` to be the first layer called during the input loop.
---@param root lhk.Node
function G.set_root(root)
end



---@class lhk.Keynode
local Keynode = {}

G.keynode = {}

---@create a new keynode.
---@return lhk.Keynode
function G.keynode.new()
end

---Configure `next_layer` to be called after `self`.
---@param next lhk.Node? The node to be linked to `self`.
function Keynode:set_next(next)
end

---Get the current state of a key
---@param keycode integer
function Keynode:state(keycode)
end

---@class lhk.Layer
local Layer = {}

G.layer = {}

---Create a new layer.
---@return lhk.Layer
function G.layer.new()
end

---Configure `next_layer` to be called after `self`.
---@param next lhk.Node? The node to be linked to `self`.
function Layer:set_next(next)
end

---Register a hotkey to a layer.
---@param keycode integer
---@param hotkey lhk.Hotkey
function Layer:register(keycode, hotkey)
end

---@class lhk.Criteria
local Criteria = {}

G.criteria = {}

---@class lhk.Criteria_table
---@field transition lhk.Transition? The update needs to match a given transition.
---@field keynode lhk.Keynode? The keynode that keystates are sourced from
---@field keystates lhk.Keystate[]? The keyboard state needs to match these keystates. Only used when `keynode` is set
---@field handler (fun(update: lhk.Update): boolean)? Custom lua handler

---@type lhk.Criteria_table
local h = {
}

---Create a new Criteria.
---@param args lhk.Criteria_table
---@return lhk.Criteria
function G.criteria.new(args)
end

---@class lhk.Hotkey
local Hotkey = {}

G.hotkey = {}

---@class lhk.Hotkey_table
---@field criteria lhk.Criteria? The hotkey is activated when the criteria is statisfied.
---@field actions lhk.Action[]? The updates to send when the hotkey is activated.

---Create a new Hotkey.
---@param args lhk.Hotkey_table
---@return lhk.Hotkey
function G.hotkey.new(args)
end

---@class lhk.Action
local Action = {}

G.action = {}

---Create a new Hotkey
---@param data integer | fun(update: lhk.Update): nil function if `type` is 'Custom', integer otherwise
---@param type lhk.Action_type
function G.action.new(data, type)
end

---@class lhk.Keystate
local Keystate = {}

G.keystate = {}

---Create a new Keystate.
---@param keycode integer
---@param state lhk.State
---@return lhk.Keystate
function G.keystate.new(keycode, state)
end

---@class lhk.Update
local Update = {}

G.update = {}

---Create a new Update.
---@param keycode integer
---@param transition lhk.Transition
---@return lhk.Update
function G.update.new(keycode, transition)
end

return G
