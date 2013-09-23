
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


#ifndef __HIVEENGINE__
#define __HIVEENGINE__

class HiveEngine
{
public:
	HiveEngine(arguments);
	~HiveEngine();
    void start_engine(struct hive_config &config);
	bool init_hive_env();
	bool init_hive_env_data(lua_State * L);
    void set_env(const char * key, const char * value);
	const char * get_env(const char * key);

private:

	MemPooler<Ar> * m_pMemPool;
	MemPooler<LAr> * m_pScriptMemPool;

    LuaServer * m_pLuaServer;
    NetServer * m_pNetServer;
    BillServerr * m_pBillServer;

    TimerMng * m_pTimerMng;
    RandMng * m_pRandMng;
    DatabaseMng * m_pDatabaseMng;
    SendCacheMng * m_pSendCacheMng;

    SceneMng * m_pSceneMng;
    AOIMng * m_pAOIMng;
    BufferPoolMng * m_pBufferPoolMng;

    hive_env * m_pHiveEnv;


	/* data */
};

#endif //__HIVEENGINE__

