#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int is_palindrome(const char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0; // Not a palindrome
        }
    }
    return 1; // Palindrome
}

char most_repeated_char(const char* str) {
    int frequency[256] = {0};
    int max_frequency = 0;
    char most_repeated = '\0';

    for (int i = 0; i < strlen(str); i++) {
        char ch = str[i];
        frequency[ch]++;
        if (frequency[ch] > max_frequency) {
            max_frequency = frequency[ch];
            most_repeated = ch;
        }
    }

    return most_repeated;
}

int main() {
    struct sockaddr_in server_addr, client_addr;
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
    memset(&client_addr, 0, sizeof(client_addr));

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(sockfd, (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        len = sizeof(client_addr);

        // Receive data from the client
        n = recvfrom(sockfd, (char*)buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &len);
        buffer[n] = '\0';

        // Check if the received string is a palindrome
        if (is_palindrome(buffer)) {
            printf("Received: %s (Palindrome)\n", buffer);
        } else {
            printf("Received: %s (Not a Palindrome)\n", buffer);
        }

        // Find the most repeated character
        char most_repeated = most_repeated_char(buffer);
        printf("Most Repeated Character: %c\n", most_repeated);

        // Send the result back to the client
        sendto(sockfd, (const char*)&most_repeated, sizeof(most_repeated), 0, (const struct sockaddr*)&client_addr, len);
    }

    return 0;
}
