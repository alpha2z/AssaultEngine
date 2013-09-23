

#ifndef __DATASTRUCT_H__
#define __DATASTRUCT_H__

struct hive_env {
	int lock;
	lua_State * L;
} ;


struct hive_config {
	int thread;
	int harbor;
	const char * logger;
	const char * module_path;
	const char * master;
	const char * local;
	const char * start;
	const char * standalone;
};


#endif //__DATASTRUCT_H__
