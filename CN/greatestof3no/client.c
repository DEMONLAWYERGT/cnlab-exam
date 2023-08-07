#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
    int client_socket;
    struct sockaddr_in serv_addr;
    int numbers[3];

    // Creating socket file descriptor
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }

    printf("Enter three numbers: ");
    scanf("%d %d %d", &numbers[0], &numbers[1], &numbers[2]);

    // Sending the numbers to the server
    send(client_socket, numbers, sizeof(numbers), 0);

    int greatest;
    // Receiving the greatest number from the server
    recv(client_socket, &greatest, sizeof(greatest), 0);

    printf("The greatest number is: %d\n", greatest);

    close(client_socket);
    return 0;
}
