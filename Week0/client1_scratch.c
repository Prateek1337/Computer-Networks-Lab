#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
int main(int argc,char * argv[]){
    int sockfd,portno,n;
    struct sockaddr_in serv_addr;
    char buffer[256];
    if(argc<2){
        printf("Invalid arguments\n");
        exit(0);
    }

    portno=atoi(argv[1]);
    sockfd=socket(AF_INET,SOCK_STREAM,0);

    if(sockfd<0){
        printf("Error in opening socket\n");
        exit(0);
    }

    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(portno);
    serv_addr.sin_addr.s_addr=INADDR_ANY;

    if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0){
        printf("error in connecting\n");
        exit(0);
    }
    while(1){
        printf("Enter message\n");
        scanf("%s",buffer);
        int n=write(sockfd,&buffer,sizeof(buffer));
        if(n<=0){
            printf("error in writing\n");
            exit(0);
        }
        n=read(sockfd,&buffer,sizeof(buffer));
        if(n<0){
            printf("Error in reading");
        }
        else{
            printf("Messge from server:%s\n",buffer);
        }
    }










}