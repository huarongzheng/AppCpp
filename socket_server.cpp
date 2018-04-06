#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    unsigned short port = 8000;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in my_addr;
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port   = htons(port);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int err_log = bind(sockfd, (struct sockaddr*)&my_addr, sizeof(my_addr));
    if( err_log != 0)
    {
        perror("binding");
        close(sockfd);
        exit(-1);
    }

    err_log = listen(sockfd, 2);    // listen queue size 2  
    if(err_log != 0)
    {
        perror("listen");
        close(sockfd);
        exit(-1);
    }
    printf("after listen\n");

    sleep(20);  //dealy 20s  

    printf("listen client @port=%d...\n",port);

    int i = 0;

    while(1)
    {

        struct sockaddr_in client_addr;
        char cli_ip[INET_ADDRSTRLEN] = "";
        socklen_t cliaddr_len = sizeof(client_addr);

        int connfd;
        connfd = accept(sockfd, (struct sockaddr*)&client_addr, &cliaddr_len);
        if(connfd < 0)
        {
            perror("accept");
            continue;
        }

        inet_ntop(AF_INET, &client_addr.sin_addr, cli_ip, INET_ADDRSTRLEN);
        printf("-----------%d------\n", ++i);
        printf("client ip=%s,port=%d\n", cli_ip,ntohs(client_addr.sin_port));

        char recv_buf[512] = {0};
        while( recv(connfd, recv_buf, sizeof(recv_buf), 0) > 0 )
        {
            printf("recv data ==%s\n",recv_buf);
            break;
        }

        close(connfd);     //close connected socket
        //printf("client closed!\n");  
    }
    close(sockfd);         //close listening socket
    return 0;
}
