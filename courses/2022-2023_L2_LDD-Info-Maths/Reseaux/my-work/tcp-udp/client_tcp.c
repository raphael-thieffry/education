#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

int SIZE = 100;
int PORT = 9600;
int ADDR;
char* ADDR_STR = "127.0.0.1";

int main(int argc, char *argv[]){

    ADDR = inet_addr(ADDR_STR);

    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){
            printf("Usage: %s [options]\n", argv[0]);
            printf("Options:\n");
            printf("  -h, --help                    Display this help and exit \n");
            printf("  -p, --port <port>             Set the port to connect on (DEFAULT = 9600)\n");
            printf("  -a, --address <adress_ip>     Set the adress to connect on (DEFAULT = 127.0.0.1)\n");
            printf("  -s, --size <size>             Set the size of the buffer (DEFAULT = 100)\n");
            printf("\ntype `exit` to close the connexion\n");

            return 0;
        }
        if(strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0){
            if(i+1 < argc){
                int port = atoi(argv[i+1]);
                if(port > 0 && port < 65535){
                    PORT = port;
                }
            }
            else{ 
                printf("Error: no port specified\n");
                return 0;
            }
        }
        if(strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--address") == 0){
            if(i+1 < argc){
                ADDR_STR = argv[i+1];
                ADDR = inet_addr(ADDR_STR);
            }
            else{ 
                printf("Error: no address specified\n");
                return 0;
            }
        }
        if(strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--size") == 0){
            if(i+1 < argc){
                int size = atoi(argv[i+1]);
                if(size > 0){
                    SIZE = size;
                }
            }
            else{ 
                printf("Error: no size specified\n");
                return 0;
            }
        }
    }

    printf("\033[35mport:\033[0m %d\n", PORT);
    printf("\033[35maddress:\033[0m %s\n", ADDR_STR);
    int sockfd;
    struct in_addr a;
    struct sockaddr_in sa;
    int client_size;

    printf("\033[33mcreating socket...\033[0m");fflush(stdout);
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    sa.sin_family = AF_INET;
    sa.sin_port = PORT;
    a.s_addr = ADDR;
    sa.sin_addr = a;
    client_size = sizeof(sa);
    printf("\033[32m OK\033[0m\n");

    printf("\033[33mtrying to connect...\033[0m");fflush(stdout);
    int c = connect(sockfd, (struct sockaddr*)&sa, sizeof(sa));
    if(c<0){
        printf("\033[31m error\033[0m\n");
        printf("connect error %d", c);
        return 0;
    }
    printf("\033[32m OK\033[0m\n\n");

    char buf[SIZE];

    while(1){
        printf("\033[2m>\033[0m "); fflush(stdout);
        fgets(buf, SIZE, stdin);
        int s = write(sockfd, buf, SIZE);
        if(s<0){
            printf("send error");
            return 0;
        }
        int r = read(sockfd, buf, SIZE);
        //close connexion when client send "exit"
        if(strcmp(buf, "exit\n") == 0){
            printf("\033[31mClient exit, Connexion closed\033[0m\n");
            close(sockfd);
            break;
        }
        if(r<0){
            printf("read error");
            return 0;
        }
    }

    close(sockfd);

    

    return 0;
}
