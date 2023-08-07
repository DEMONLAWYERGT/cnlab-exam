#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

void reverseString(char *str) {
    int len = strlen(str);
    int i, j;
    char temp;
    for (i = 0, j = len - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int main() {
    int server_fd, client_fd, valread;
    struct sockaddr_in server_addr, client_addr;
    int addrlen = sizeof(server_addr);
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);

    // Bind the socket to the specified address and port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", SERVER_PORT);

    while (1) {
        // Accept incoming connection
        if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&addrlen)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        // Receive string from client
        valread = read(client_fd, buffer, BUFFER_SIZE);
        buffer[valread] = '\0';
        printf("Received: %s\n", buffer);

        // Reverse the string
        reverseString(buffer);

        // Send reversed string back to the client
        send(client_fd, buffer, strlen(buffer), 0);
        printf("Reversed string sent: %s\n", buffer);

        close(client_fd); // Close the current client connection
    }

    return 0;
}
