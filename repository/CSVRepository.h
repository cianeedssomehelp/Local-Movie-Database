#pragma once
#include "FileWatchlist.h"
#ifndef CVSREPOSITORY_H
#define CVSREPOSITORY_H

#include <string>

class CVSRepository : public FileWatchlist {
public:
    explicit CVSRepository(const std::string& watchlistFileName);
    void writeToFile() override;
    void readFromFile();
    void displayWatchlist() const override;
};

#endif // CVSREPOSITORY_H

