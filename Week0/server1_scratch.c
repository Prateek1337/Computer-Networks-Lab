#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
int main(char argc,char* argv[] ){
    //Declaring variables
    int sockfd,newsockfd,port_no,cli_len,n;
    struct sockaddr_in serv_addr,cli_addr;
    char buffer[256];
    //Testing Argument
    if(argc<2){
        printf("Invalid argument\n");
        exit(0);
    }
    
    //creating socket for listening
    sockfd=socket(AF_INET,SOCK_STREAM,0);

    if(sockfd<0){
        printf("Socket Creation failed\n");
        exit(0);
    }

    //Initilising to 0 and typecasting.
    bzero((char *) &serv_addr,sizeof(serv_addr));

    //getting port number
    port_no=atoi(argv[1]);

    //setting server address
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(port_no);
    serv_addr.sin_addr.s_addr=INADDR_ANY;

    //binding server address to main port
    if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0){
        printf("Bind failed\n");
        exit(0);
    }

    //listen
    listen(sockfd,5);

    cli_len=sizeof(cli_addr);
    newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&cli_len);

    if(newsockfd<0){
        printf("Accept failed\n");
        exit(0);
    }
    while(1){
        bzero(buffer,sizeof(buffer));
        int n=read(newsockfd,&buffer,sizeof(buffer));
        if(n<=0){
            printf("read failed\n");
        }
        else{
            printf("Message is :%s\n",buffer);
            printf("Enter message to write\n");
            fgets(buffer,sizeof(buffer),stdin);
            printf("Your message:%s\n",buffer);
            int n=write(newsockfd,buffer,sizeof(buffer));
            if(n<0){
                printf("Write failed\n");
            }
            else{
                printf("Write Success\n");
            }
        }
    }
}