#pragma once
#include "../WatchList/Watchlist.h"

#ifndef FILEWATCHLIST_H
#define FILEWATCHLIST_H

class FileWatchlist: public WatchList {
public:
    std::string filename;
    FileWatchlist();
    explicit FileWatchlist(const std::string& file) {
        this->filename = file;
    }
    virtual ~FileWatchlist() {}
    void setFilename(const std::string& filename);
    virtual void writeToFile() = 0;
    virtual void displayWatchlist() const = 0;
    std::string getFilename() const {
        return filename;
    }
    void setMovies(const std::vector<Movies>& movies) {
        this->movies = movies;
    }
};


#endif //FILEWATCHLIST_H
