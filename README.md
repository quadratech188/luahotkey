# IN DEVELOPMENT, VERY WIP

# `luahotkey`
*keyboard remapper, but with the power of lua*

# Overview
## How it works
`luahotkey` is configured by manipulating a linked list. This sounds complicated, but it's actually as simple as:
```lua
lhk.set_root(node1)
node1:set_next(node2)
```
In this case, each keystroke (Referred to as `Update` from now on) will be processed by `node1`, whose result will be processed by `node2`. This has some advantages:
- Toggling a 'node` is as simple as inserting the node into the linked list.
- We can easily control the order in which remaps are evaluated; Put an alternate keymap at the head of the linked list, and never worry about it again.
## Nodes
`luahotkey` currently has 2 types of nodes: Layers and Keynodes.
## Layers
This is where the remapping takes place. For each keycode, you can insert a `Hotkey`, which can have a `Criteria` for activation and an array of `Action`s to be executed.
## Keynodes
This node doesn't do any processing; it records every `Update` and keeps track of which keys are pressed. `Criteria`s can reference a `Keynode`, and require that certain keys be pressed.
# Documentation
The code is currently only documented as [lua_ls](https://luals.github.io/) annotations.
# Performance
***TBD***

