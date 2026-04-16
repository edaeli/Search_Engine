#ifndef CRAWLER_H
#define CRAWLER_H

#include <string>
#include <vector>
#include <set>
#include <queue>
#include "http_client.h"
#include "url_parser.h"

class Crawler {
public:
    void run(const std::string& seed_url, int max_pages);

private:
    std::set<std::string> visited;
    std::queue<std::string> to_visit;
    HttpClient client;

    void extractLinks(const std::string& html, const std::string& base_host);
};

#endif
