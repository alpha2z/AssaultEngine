
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


HiveEngine::HiveEngine() {

}

HiveEngine::~HiveEngine() {

}

bool HiveEngine::init_hive_env() {
	m_pHiveEnv = new struct hive_env;
	m_pHiveEnv->lock = 0;
	m_pHiveEnv->L = luaL_newstate();
}

bool HiveEngine::init_hive_env_data(lua_State * L) {

}

void HiveEngine::set_env(const char * key, const char * value) {
	LOCK(m_pHiveEnv)
	lua_State * L = m_pHiveEnv->L;
	lua_getglobal(L, key);
	assert(lua_isnil(L, -1));
	lua_pop(L, 1);
	lua_pushstring(L, value);
	lua_setglobal(L, key);
	UNLOCK(m_pHiveEnv);
}


const char * HiveEngine::get_env(const char *key) {
	LOCK(m_pHiveEnv)
	lua_State *L = m_pHiveEnv->L;
	lua_getglobal(L, key);
	const char * result = lua_tostring(L, -1);
	lua_pop(L, 1);
	UNLOCK(m_pHiveEnv)
	return result;
}

void HiveEngine::start_engine(struct hive_config &config) {
	

	
}





