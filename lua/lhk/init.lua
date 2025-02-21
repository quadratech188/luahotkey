local G = require 'lhk_core'

G.actions = require 'lhk.actions'

G.util = require 'lhk.util'

G.switcher = require 'lhk.switcher'

G.criteria.primitives = {
	press = G.criteria.new {
		transition = 'Press'
	},
	release = G.criteria.new {
		transition = 'Release'
	}
}

return G
