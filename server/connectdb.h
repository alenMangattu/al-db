#include <stdint.h>

void getDbInfo(const char* dbname, const char* user, const char* passwd, const char* host, uint16_t* port);
int connectDb(const char* dbname, const char* user, const char* passwd, const char* host, uint16_t port);