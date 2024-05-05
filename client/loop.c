#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

void listenServer() {
    int sfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sfd == -1) {
        printf("Errore creature del socket.");
        return;
    }

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(6000);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(sfd, &addr, sizeof(addr)) == -1) {
        printf("Errore quando connete");
    };

    struct pollfd pfd[2] = {
        {0, POLLIN, 0},
        {sfd, POLLIN, 0}
    };

    if (poll(pfd, 2, 64000) == -1) {
        printf("Errore nel polling");
        close(sfd);
        return;
    }


    //server loop
    while (1) {
        char buffer[1024] = {0};

        if (pfd[0].revents & POLLIN) {
            if (read(0, buffer, 1024) == -1) {
                printf("Errore reading");
            }
            if (send(sfd, buffer, strlen(buffer), 0) == -1) {
                printf("Errore parte sending");
            }
        } else if (pfd[1].revents & POLLIN) {
            recv(sfd, buffer, 1024, 0);
            printf("Buffer: %s\n", buffer);
        }
    }
}