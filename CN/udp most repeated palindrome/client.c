#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
    struct sockaddr_in server_addr;
    int sockfd, n;
    socklen_t len;
    char buffer[BUFFER_SIZE];

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    printf("Enter a string: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline character

    // Send the string to the server
    sendto(sockfd, (const char*)buffer, strlen(buffer), 0, (const struct sockaddr*)&server_addr, sizeof(server_addr));

    // Receive the most repeated character from the server
    recvfrom(sockfd, (char*)buffer, BUFFER_SIZE, 0, (struct sockaddr*)&server_addr, &len);

    printf("Most Repeated Character: %c\n", buffer[0]);

    close(sockfd);

    return 0;
}
