#ifndef URL_PARSER_H
#define URL_PARSER_H

#include <string>

struct ParsedUrl {
    std::string host;
    std::string path;
    bool isValid;
};

class UrlParser {
public:
    static ParsedUrl parse(const std::string& url);
};

#endif
