#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/time.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(int argc,char * argv[]){
    //Declaring variables
    int master_socket,new_socket,port_no,n,MAX_CLIENT=10,client_socket[MAX_CLIENT],max_sd;
    int activity,val_read,cli_len,sd;
    struct sockaddr_in serv_addr,cli_addr;
    char buffer[256];
    //Testing Argument
    if(argc<2){
        printf("Invalid argument\n");
        exit(0);
    }
    
    //creating socket for listening
    master_socket=socket(AF_INET,SOCK_STREAM,0);

    if(master_socket<0){
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
    if(bind(master_socket,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0){
        printf("Bind failed\n");
        exit(0);
    }

    //listen
    listen(master_socket,5);
    for(int i=0;i<MAX_CLIENT;++i){
        client_socket[i]=0;
    }

    fd_set readfds;
    char *message="Welcome to server";
    cli_len=sizeof(cli_addr);
    while(1){
        FD_ZERO(&readfds);
        FD_SET(master_socket,&readfds);
        max_sd=master_socket;
        for(int i=0;i<MAX_CLIENT;++i){
            sd=client_socket[i];
            if(sd>0){
                FD_SET(sd,&readfds);
            }
            if(sd>max_sd){
                max_sd=sd;
            }
        }
        activity=select(max_sd+1,&readfds,NULL,NULL,NULL);

         if ((activity < 0))   
        {   
            printf("select error");   
        } 
        if(FD_ISSET(master_socket,&readfds)){
            printf("%d %d,mas")
            new_socket=accept(master_socket,(struct sockaddr *)&cli_addr,&cli_len);
            if(new_socket<0){
                printf("accept error\n");
                exit(0);
            }
            write(new_socket,message,sizeof(message));
            for(int i=0;i<MAX_CLIENT;++i){
                if(client_socket[i]==0){
                    client_socket[i]=new_socket;
                    printf("Adding socket to list\n");
                    break;
                }
            }
        }
        for(int i=0;i<MAX_CLIENT;++i){
            sd=client_socket[i];
            if(FD_ISSET(sd,&readfds)){
                n=read(sd,buffer,sizeof(buffer));
                if(n==0){
                     printf("Connection Terminated of some client\n");
                }
                else{
                    // buffer[n]='\0'
                    printf("Some client send :%s\n",buffer);
                    write(sd,buffer,sizeof(buffer));
                }
            }
        }
    }
    

}