#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define PORT 8070
#define BUFFER_SIZE 1024


int main(){

    int server_fd,new_socket;

    struct sockaddr_in address;

    int addrlen = sizeof(address);

    char buffer[BUFFER_SIZE] = {0};

    const char *welcome_message = "Hello from server";
    if((server_fd = socket(AF_INET,SOCK_STREAM,0)) < 0 ){
        perror("Socket creation error\n");
        return -1;
    }


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);


    printf("%d \n",server_fd);


    if(bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0){
        perror("bind failed");
        close(server_fd);
        return -1;
    }

    if(listen(server_fd,3) < 0){
        perror("failed bang");
        return -1;
    }

    return 0;
}