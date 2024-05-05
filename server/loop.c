#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

void createServer() {
    int sfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sfd == -1) {
        printf("Errore creature del socket.");
        return;
    }

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(6000);
    addr.sin_addr.s_addr = INADDR_LOOPBACK;

    if (bind(sfd, &addr, sizeof(addr)) == -1) {
        printf("Errore nella parte bind.");
        close(sfd);
        return;
    }

    if (listen(sfd, 64) == -1) {
        printf("Errore nella parte listen.");    
        close(sfd);
        return;
    }

    struct sockaddr_in addrClient;
    socklen_t addrClientLen = sizeof(addrClient);
    int cfd = accept(sfd, (struct sockaddr *)&addrClient, &addrClientLen);
    if (cfd == -1) {
        printf("Errore nella parte accept.");    
        close(sfd);
        return;
    }

    struct pollfd pfd[2] = {
        {0, POLLIN, 0},
        {cfd, POLLIN, 0}
    };

    if (poll(pfd, 2, 64000) == -1) {
        printf("Errore nel polling");
        close(cfd);
        close(sfd);
        return;
    }

    while (1) {
        char buffer[1024] = {0};

        if (pfd[0].revents & POLLIN) {
            if (read(0, buffer, 1024) == -1) {
                printf("Errore reading");
            }
            if (send(cfd, buffer, strlen(buffer), 0) == -1) {
                printf("Errore parte sending");
            }
        } else if (pfd[1].revents & POLLIN) {
            recv(cfd, buffer, 1024, 0);
            printf("Buffer: %s\n", buffer);
        }
    }
}