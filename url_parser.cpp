#include "url_parser.h"

ParsedUrl UrlParser::parse(const std::string& url) {
    ParsedUrl result;
    result.isValid = false;
    result.path = "/";

    std::string temp = url;

    std::string prefix = "http://";
    if (temp.substr(0, prefix.size()) == prefix) {
        temp.erase(0, prefix.size());
    } else {
        if (temp.substr(0, 8) == "https://") 
		return result;
    }

    size_t slash_pos = temp.find('/');
    
    if (slash_pos == std::string::npos) { 
        result.host = temp;
    } else {        
        result.host = temp.substr(0, slash_pos);
        result.path = temp.substr(slash_pos);
    }

    if (!result.host.empty()) {
        result.isValid = true;
    }

    return result;
}
