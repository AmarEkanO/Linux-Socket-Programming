#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 
    

    char sendBuff[1025];
    time_t ticks; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    if(listen(listenfd, 10) == -1){
        printf("\nUnable to listen to port 5000\n");
    }else{
        printf("\nListening on port 5000\n");
    }

    while(1)
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_addr_len); 

        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        write(connfd, sendBuff, strlen(sendBuff)); 

        char client_name[INET_ADDRSTRLEN];
        if(inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_name, sizeof(client_name)) != NULL){
            printf("Handling client %s:%d\n", client_name, ntohs(client_addr.sin_port));
        }else{
            puts("Unable to get client address");
        }


        close(connfd);
        sleep(1);
     }
}