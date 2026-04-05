#include <iostream>
#include "http_client.h"
#include "url_parser.h"

int main() {
    std::string input_url = "http://info.cern.ch/hypertext/WWW/TheProject.html";
    
    ParsedUrl pUrl = UrlParser::parse(input_url);
    
    if (!pUrl.isValid) {
        std::cerr << "Invalid URL or HTTPS not supported!" << std::endl;
        return 1;
    }

    std::cout << "Target Host: " << pUrl.host << std::endl;
    std::cout << "Target Path: " << pUrl.path << std::endl;

    HttpClient client;
    std::string content = client.fetch(pUrl.host, pUrl.path);
    
    std::cout << "\n--- CONTENT START ---\n";
    std::cout << content << std::endl;
    
    return 0;
}
