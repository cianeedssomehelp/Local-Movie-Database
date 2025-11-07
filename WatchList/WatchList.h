#pragma once
#include <vector>
#include "../domain/domain.h"
#ifndef WATCHLIST_H
#define WATCHLIST_H

class WatchList {
    protected:
        std::vector<Movies> movies;
        int current;
    public:
        WatchList();
        void add(const Movies& movie);
        void deleteMovie(const Movies& movie);
        Movies getCurrent();
        void playTrailer();
        void next();
        bool isEmpty();
        std::vector<Movies> getMovies() const {
            return std::vector<Movies>(this->movies.begin(), this->movies.end());
        }
        bool MovieExists(const Movies& movie) const;
        virtual ~WatchList(){};


};

#endif //WATCHLIST_H
