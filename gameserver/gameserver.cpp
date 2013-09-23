
//------------------------------------------------------------------------
//
//	CloudEngine wrote for MMORPG.
//
//	Copyright (c) 2013 by Riddick Zhou
// 
//	For latest updates, please visit
//
//	Date 2013-08-25
//
//------------------------------------------------------------------------



#include "gameserver.h"
#include "HiveEngine.h"

#include <stdlib.h>


HiveEngine * g_pHiveEngine = NULL;

extern "C" {

static void read_config_file(lua_State * L);
static const char * set_env_string(const char* key, const char * value);
static int set_env_int(const char* key, const char * value);

}

int main(int argc, char const *argv[]) {

	/* code */
	const char * config_file = "config";
	if (argc > 1) {
		config_file = argv[1];
	}
	
	g_pHiveEngine = new HiveEngine();
	if (!g_pHiveEngine->init_hive_env()) {
		FLOG("error.log", "init hive environment failed in init_hive_env.");
		return 1;
	}

	struct lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	lua_close(L);

	L = luaL_newstate();
	int err = luaL_dofile(L, config_file);
	if (err) {
		FLOG("error.log", "do file failed. file name is ", lua_tostring(L, -1));
		lua_close(L);
		return 1;
	}
	read_config_file(L);


	struct hive_config config;
	const char * path = set_env_string("lua_path", "./lualib/?.lua;./lualib/?/init.lua");
	setenv("LUA_PATH", path, 1);
	const char * cpath = set_env_string("lua_cpath", "./luaclib/?.so");
	setenv("LUA_CPATH", cpath, 1);
	set_env_string("luaservice", "./service/?.lua");

	config.thread = set_env_int("thread", 8);
	config.module_path = set_env_string("cpath", "./service/?.so");
	config.logger = set_env_string("logger", NULL);
	config.harbor = set_env_int("harbor", 1);
	config.master = set_env_string("master", "127.0.0.1:2012");
	config.start = set_env_string("start", "main.lua");
	config.local = set_env_string("address", "127.0.0.1:2525");
	config.standalone = set_env_string("standalone", NULL);

	lua_close(L);
	int cur_pid = g_pHiveEngine->start_engine(config);
	LOG("[HIVE ENGINE] start success. pid : %d, void * = %d, ulong = %d, int = %d, Node = %d, list_head = %d.",
		cur_pid, sizeof(void*), sizeof(unsigned long), sizeof(int), sizeof(Node), sizeof(list_head));

	SAFE_DELETE(g_pHiveEngine);
	return 0;
}

extern "C" {

static void read_config_file(lua_State * L) {
	lua_pushglobaltable(L);
	lua_pushnil(L);
	while (lua_next(L, -2) != 0) {
		int keyt = lua_type(L, -2);
		if (keyt != LUA_TSTRING) {
			FLOG("error.log", "Invalid config table");
			exit(1);
		}
		const char * key = lua_tostring(L, -2);
		if (lua_type(L, -1) == LUA_TBOOLEAN) {
			int b = lua_toboolean(L, -1);
			g_pHiveEngine->set_env(key, b ? "true" : "false");
		} else {
			const char * value = lua_tostring(L, -1);
			g_pHiveEngine->set_env(key, value);
		}
		lua_pop(L, 1);
	}
}

static void set_env_string(const char * key, const char * value) {
	const char * str = g_pHiveEngine->get_env(key);
	if (str == NULL) {
		if (value) {
			g_pHiveEngine->set_env(key, value);
		}
		return value;
	}
	return str;
}

static int set_env_int(const char * key, int value) {
	const char * str = g_pHiveEngine->get_env(key);
	if (str) {
		return strtol(str, NULL, 10);
	}

	char tmp[20] = {0};
	sprintf(tmp, "%d", value);
	g_pHiveEngine->set_env(key, tmp);
	return value;
}


}

HiveEngine * getHiveEngine() {
	return g_pHiveEngine;
}
