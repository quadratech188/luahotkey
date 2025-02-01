package = "luahotkey"
version = "dev-1"
source = {
   url = "git+https://github.com/quadratech188/luahotkey"
}
description = {
   license = "MIT"
}
build = {
    type = "make",
    build_variables = {
    	CFLAGS="$(CFLAGS)",
        LIBFLAG="$(LIBFLAG)",
        LUA_LIBDIR="$(LUA_LIBDIR)",
        LUA_BINDIR="$(LUA_BINDIR)",
        LUA_INCDIR="$(LUA_INCDIR)",
        LUA="$(LUA)",
	},
  	install_variables = {
        INST_PREFIX="$(PREFIX)",
        INST_BINDIR="$(BINDIR)",
        INST_LIBDIR="$(LIBDIR)",
        INST_LUADIR="$(LUADIR)",
        INST_CONFDIR="$(CONFDIR)",
	},
	install = {
		lua = {
			['docs.lhk_core'] = 'docs/lhk_core.lua',

			['lhk'] = 'lua/lhk/init.lua',
			['lhk.util'] = 'lua/lhk/util.lua',

			['keycodes.global'] = 'lua/keycodes/global.lua',
			['keycodes.table'] = 'lua/keycodes/table.lua',
		}
	}
}
