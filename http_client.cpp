#include "http_client.h"
#include <iostream>
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <netdb.h>      
#include <unistd.h>     
#include <cstring>

std::string HttpClient::fetch(const std::string& host, const std::string& path) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       
    hints.ai_socktype = SOCK_STREAM; 

    if (getaddrinfo(host.c_str(), "80", &hints, &res) != 0) {
        return "Error: DNS lookup failed";
    }

    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0) {
        freeaddrinfo(res);
        return "Error: Could not create socket";
    }

    if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
        close(sockfd);
        freeaddrinfo(res);
        return "Error: Could not connect";
    }
    freeaddrinfo(res);

    std::string request = "GET " + path + " HTTP/1.1\r\n";
    request += "Host: " + host + "\r\n";
    request += "Connection: close\r\n";
    request += "\r\n";

    send(sockfd, request.c_str(), request.length(), 0);

    std::string response;
    char buffer[4096];
    ssize_t bytes_received;
    
    while ((bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        response.append(buffer);
    }

    close(sockfd);
    return response;
}
