---@meta

local G = {}

---@alias lhk.State 'Up' | 'Down'

---@alias lhk.Transition 'Press' | 'Release' | 'Autorepeat'

---@alias lhk.Action_type 'Press' | 'Release' | 'Autorepeat' | 'Mirror' | 'Require_down' | 'Require_up' | 'Custom'

---@alias lhk.Node lhk.Layer | lhk.Keynode | nil

---Start the input loop.
function G.start()
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
---@field criteria lhk.Criteria | lhk.Criteria_table? The hotkey is activated when the criteria is statisfied.
---@field actions lhk.Action[] The updates to send when the hotkey is activated.
---@field passthrough boolean? Whether the original keystroke should also be sent

---Create a new Hotkey.
---@param args lhk.Hotkey_table
---@return lhk.Hotkey
function G.hotkey.new(args)
end

---@class lhk.Action
local Action = {}

G.action = {}

---Create a new press action
---@param keycode integer
---@return lhk.Action
function G.action.press(keycode)
end

---Create a new release action
---@param keycode integer
---@return lhk.Action
function G.action.release(keycode)
end

---Create a new autorepeat action
---@param keycode integer
---@return lhk.Action
function G.action.autorepeat(keycode)
end

---Create a new mirror action
---@param keycode integer
---@return lhk.Action
function G.action.mirror(keycode)
end

---Create a new require_up action
---@param reference lhk.Keynode
---@param keycode integer
---@return lhk.Action
function G.action.require_up(reference, keycode)
end

---Create a new require_down action
---@param reference lhk.Keynode
---@param keycode integer
---@return lhk.Action
function G.action.require_down(reference, keycode)
end

---Create a new enforce action
---@param reference lhk.Keynode
---@param keycode integer
---@return lhk.Action
function G.action.enforce(reference, keycode)
end

---Create a new enforce_from_down action
---@param reference lhk.Keynode
---@param keycode integer
---@return lhk.Action
function G.action.enforce_from_down(reference, keycode)
end

---Create a new enforce_from_up action
---@param reference lhk.Keynode
---@param keycode integer
---@return lhk.Action
function G.action.enforce_from_up(reference, keycode)
end

---Create a new set_next action
---@param from lhk.Layer|lhk.Keynode
---@param to lhk.Layer|lhk.Keynode|nil
function G.action.set_next(from, to)
end

---Create a new custom action
---@param func fun(lhk.Update)
---@return lhk.Action
function G.action.custom(func)
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
---@field keycode integer
---@field transition lhk.Transition
local Update = {}

G.update = {}

---Create a new Update.
---@param keycode integer
---@param transition lhk.Transition
---@return lhk.Update
function G.update.new(keycode, transition)
end

G.settings = {}

---Determine whether to grab the original input device.
---@param grab boolean
function G.settings.grab(grab)
end

---Specify the event device lhk receives input from.
---@param input string
function G.settings.input(input)
end

---Specify the name of the event device lhk outputs keystrokes from.
---@param output string
function G.settings.output(output)
end

---Specify the path of the FIFO socket that lhk reads from.
---@param socket string
function G.settings.socket(socket)
end

---Specify whether to use sockets.
---@param use_socket boolean
function G.settings.use_socket(use_socket)
end

---Specify the function that is called when a message is received.
---@param socket_handler any
function G.settings.socket_handler(socket_handler)
end

return G
