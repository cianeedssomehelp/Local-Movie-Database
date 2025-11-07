#pragma once
#include "FileWatchlist.h"
#ifndef HTMLREPOSITORY_H
#define HTMLREPOSITORY_H
class HTMLRepository : public FileWatchlist {
public:
    explicit HTMLRepository(const std::string &watchlistFileName);
    void writeToFile() override;
    void displayWatchlist() const override;
    HTMLRepository() = default;
};
#endif //HTMLREPOSITORY_H
