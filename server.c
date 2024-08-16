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

    //create socket file descriptor
    if((server_fd = socket(AF_INET,SOCK_STREAM,0)) < 0 ){
        perror("Socket creation error\n");
        return -1;
    }

    //configure server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    printf("%d \n",server_fd);

    //bind socket to the port
    if(bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0){
        perror("bind failed");
        close(server_fd);
        return -1;
    }

    if(listen(server_fd,3) < 0){
        perror("failed bang");
        exit(EXIT_FAILURE);
    }

     printf("Server listening on port %d...\n", PORT);

    // Accept a connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Send a welcome message to the client
    send(new_socket, welcome_message, strlen(welcome_message), 0);
    printf("Welcome message sent\n");

    // Receive a message from the client
    int valread = read(new_socket, buffer, BUFFER_SIZE);
    printf("Received from client: %s\n", buffer);

    // Close the connection
    close(new_socket);
    close(server_fd);
    return 0;


    return 0;
}