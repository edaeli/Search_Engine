#include "indexer.h"
#include <sstream>
#include <algorithm>

void Indexer::addPage(const std::string& url, const std::string& html) {
    std::string cleanText = stripTags(html);
    std::stringstream ss(cleanText);
    std::string word;

    while (ss >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        
        word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());

        if (word.length() > 2) {
            database[word].insert(url);
        }
    }
}

std::vector<std::string> Indexer::search(const std::string& query) {
    std::string q = query;
    std::transform(q.begin(), q.end(), q.begin(), ::tolower);

    if (database.find(q) != database.end()) {
        return std::vector<std::string>(database[q].begin(), database[q].end());
    }
    return {};
}

std::string Indexer::stripTags(const std::string& html) {
    std::string out;
    bool insideTag = false;
    for (char c : html) {
        if (c == '<') insideTag = true;
        else if (c == '>') insideTag = false;
        else if (!insideTag) out += c;
    }
    return out;
}
