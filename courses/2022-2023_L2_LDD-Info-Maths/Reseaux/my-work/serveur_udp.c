#include <stdio.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <netdb.h>

#include <string.h>
#include <arpa/inet.h>

/* Port local du serveur */

#define PORT 9600

int main(int argc, char *argv[]){
    //vars
    int sockfd;
    struct in_addr a;
    struct sockaddr_in sa;
    int client_size;

    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    sa.sin_family = AF_INET;
    sa.sin_port = PORT;
    a.s_addr = inet_addr("127.0.0.1");
    sa.sin_addr = a;
    client_size = sizeof(sa);
    char buf[100];
    int b = bind(sockfd, (struct sockaddr*)&sa, sizeof(sa));    if(b<0){
            printf("error bind");
            return 0;
        }
    while (1) {
        int r  = recvfrom(sockfd,buf, 100, 0, (struct sockaddr*)&sa, (socklen_t*)sizeof(sa));
        if(r<0){
            printf("error rec");
            return 0;
        }
        write(sockfd, buf, 100);
    }
    return 0;
}

