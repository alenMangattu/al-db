#include <libpq-fe.h>
#include <stdio.h>
#include <termio.h>
#include <stdint.h>
#include <stdlib.h>

extern int LEN;
struct termios old, new;

void turnOff(FILE* stream) {
    //https://stackoverflow.com/questions/6856635/hide-password-input-on-terminal

    if (tcgetattr (fileno (stream), &old) != 0)
        return -1;
    new = old;
    new.c_lflag &= ~ECHO;
    if (tcsetattr (fileno (stream), TCSAFLUSH, &new) != 0)
        return -1;
}

void turnOn(FILE* stream) {
    (void) tcsetattr (fileno (stream), TCSAFLUSH, &old);
}

void getDbInfo(const char* dbname, const char* user, const char* passwd, const char* host, uint16_t* port) {
    
    printf("Enter the database name: ");
    fgets(dbname, LEN, stdin);
    printf("Enter the username: ");
    fgets(user, LEN, stdin);

    turnOff(stdin);

    printf("Enter the password: ");
    fgets(passwd, LEN, stdin);

    turnOn(stdin);

    printf("\nEnter the host: ");
    fgets(host, LEN, stdin);

    printf("Enter the port: ");
    scanf("%hu", port);
}

int connectDb(const char* dbname, const char* user, const char* passwd, const char* host, uint16_t port) {
    char* conninfo = malloc(sizeof(char) * (LEN * 4 + 6));
    if (conninfo == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }

    sprintf(conninfo, "dbname=%s user=%s password=%s host=%s port=%hu", dbname, user, passwd, host, port);

    PGconn* conn = PQconnectdb(conninfo);
    free(conninfo);
    
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return -1;
    }

    printf("Conntected succesfully.\nPort: %s\n", PQport(conn));
    printf("Host: %s\n", PQhost(conn));
    printf("DBName: %s\n", PQdb(conn));
    PQfinish(conn);
    return 0;
}