#include "crawler.h"
#include <iostream>

void Crawler::run(const std::string& seed_url, int max_pages) {
    to_visit.push(seed_url);
    int pages_crawled = 0;

    while (!to_visit.empty() && pages_crawled < max_pages) {
        std::string current_url = to_visit.front();
        to_visit.pop();

        if (visited.find(current_url) != visited.end()) continue;

        std::cout << "Step [" << pages_crawled + 1 << "/" << max_pages 
                  << "] Visiting: " << current_url << std::endl;

        ParsedUrl pUrl = UrlParser::parse(current_url);
        if (!pUrl.isValid) continue;

        std::string html = client.fetch(pUrl.host, pUrl.path);
        
        if (html.empty() || html.find("Error") == 0) {
            std::cout << "  Failed to fetch content." << std::endl;
            continue;
        }

        extractLinks(html, pUrl.host);

        visited.insert(current_url);
        pages_crawled++;
    }
    std::cout << "\nDone! Visited " << pages_crawled << " pages." << std::endl;
}

void Crawler::extractLinks(const std::string& html, const std::string& base_host) {
    std::vector<std::string> tags = {"href=\"", "HREF=\"", "href='", "HREF='"};
    
    for (const std::string& tag : tags) {
        size_t pos = 0;
        while ((pos = html.find(tag, pos)) != std::string::npos) {
            pos += tag.length();
            
            char quote = tag.back(); 
            size_t end_pos = html.find(quote, pos);
            
            if (end_pos == std::string::npos) break;

            std::string link = html.substr(pos, end_pos - pos);

            if (link.find("http") != 0) {
                if (link.empty()) continue;
                if (link[0] == '/') {
                    link = "http://" + base_host + link;
                } else {
                    link = "http://" + base_host + "/hypertext/WWW/" + link; 
                }
            }

            if (link.find(".jpg") == std::string::npos && link.find(".png") == std::string::npos) {
                to_visit.push(link);
            }
        }
    }
}
