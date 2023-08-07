#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int fibonacci(int n) {
    if (n <= 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    int limit, i;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the given address and port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding error");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("Listening error");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for the client to connect...\n");

    client_addr_len = sizeof(client_addr);

    // Accept a client connection
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_socket < 0) {
        perror("Accepting error");
        exit(EXIT_FAILURE);
    }

    printf("Client connected.\n");

    // Receive the limit from the client
    recv(client_socket, &limit, sizeof(limit), 0);
    printf("Received limit: %d\n", limit);

    // Calculate and send the Fibonacci series to the client
    int fib_series[limit];
    for (i = 0; i < limit; i++) {
        fib_series[i] = fibonacci(i);
    }
    send(client_socket, fib_series, sizeof(fib_series), 0);

    printf("Fibonacci series sent to the client.\n");

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
