#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <libpq-fe.h>
//#include <loop.h>
//#include <connectdb.h>

const int LEN = 50;

int main() {

    char dbname[LEN], user[LEN], host[LEN];
    const char* passwd = malloc(sizeof(char) * LEN);
    uint16_t port;

    getDbInfo(dbname, user, passwd, host, &port);
    if (connectDb(dbname, user, passwd, host, port) == -1) {
        printf("Impossible accedere al database");
        return 0;
    };
    free(passwd);

    createServer();
}