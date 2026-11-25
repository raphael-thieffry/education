#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 100

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
    // int b = bind(sockfd, (struct sockaddr*)&sa, sizeof(sa));
    // if(b<0){
    //     printf("bind error %d", b);
    //     return 0;
    // }
    
    char buf[100];
    int r = read(sockfd, buf, 100);
    if(r<0){
        printf("read error");
        return 0;
    }
    int s = sendto(sockfd, buf, 100, 0, (struct sockaddr*)&sa, sizeof(sa));
    if(s<0){
        printf("send error");
        return 0;
    }
    close(sockfd);

    return 0;
}