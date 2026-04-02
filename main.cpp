#include <iostream>
#include "http_client.h"

int main() {
    HttpClient client;

    std::string content = client.fetch("info.cern.ch", "/");
    std::cout << content << std::endl;
    return 0;
}
