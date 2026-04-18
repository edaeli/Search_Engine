#ifndef INDEXER_H
#define INDEXER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <set>

class Indexer {
public:
    void addPage(const std::string& url, const std::string& html);

    std::vector<std::string> search(const std::string& query);

private:
    std::unordered_map<std::string, std::set<std::string>> database;

    std::string stripTags(const std::string& html);
};

#endif
