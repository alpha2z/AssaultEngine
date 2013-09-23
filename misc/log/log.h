





#define FLOG(n) LogEngine::write_file_log

#define LOG(n) (g_pLogEngine->*( g_pLogEngine->get_log_func( LOG_TYPE_LOG, n)))