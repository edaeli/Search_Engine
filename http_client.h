#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>

struct HttpClient {
    std::string fetch(const std::string& host, const std::string& path);
};

#endif
