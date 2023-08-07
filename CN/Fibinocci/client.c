#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    int limit, i;
    int fib_series[100]; // Assuming the limit won't exceed 100

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with the server IP if not localhost

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection error");
        exit(EXIT_FAILURE);
    }

    printf("Enter the limit to find the Fibonacci series: ");
    scanf("%d", &limit);

    // Send the limit to the server
    send(client_socket, &limit, sizeof(limit), 0);

    // Receive the Fibonacci series from the server
    recv(client_socket, fib_series, sizeof(fib_series), 0);

    printf("Fibonacci series of %d numbers: ", limit);
    for (i = 0; i < limit; i++) {
        printf("%d ", fib_series[i]);
    }
    printf("\n");

    // Close the socket
    close(client_socket);

    return 0;
}
