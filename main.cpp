#include <iostream>
#include "crawler.h"
#include "indexer.h"

int main() {
    Crawler myCrawler;
    Indexer myIndexer;

    std::string start_url = "http://info.cern.ch/hypertext/WWW/TheProject.html";
    myCrawler.run(start_url, 10, myIndexer);

    std::string query;
    std::cout << "\nEnter word to search: ";
    std::cin >> query;

    std::vector<std::string> results = myIndexer.search(query);

    if (results.empty()) {
        std::cout << "No pages found for: " << query << std::endl;
    } else {
        std::cout << "Found " << results.size() << " pages:" << std::endl;
        for (const std::string& url : results) {
            std::cout << " - " << url << std::endl;
        }
    }

    return 0;
}
