#include "crawler.h"

int main() {
    Crawler myCrawler;

    myCrawler.run("http://info.cern.ch/hypertext/WWW/TheProject.html", 5);
    return 0;
}
