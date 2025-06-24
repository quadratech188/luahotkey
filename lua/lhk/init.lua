local G = require 'lhk_core'

local criteria = G.criteria

criteria.PRESS = G.criteria.new {
	transition = 'Press'
}

criteria.RELEASE = G.criteria.new {
	transition = 'Release'
}

G.criteria = criteria

G.actions = require 'lhk.actions'

G.util = require 'lhk.util'

G.switcher = require 'lhk.switcher'

G.settings = require 'lhk.settings'

return G
