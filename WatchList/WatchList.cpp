#include "WatchList.h"
#include <algorithm>

WatchList::WatchList() {
    this->current = 0;
}

void WatchList::add(const Movies &movie) {
    if (!MovieExists(movie)) {
        this->movies.push_back(movie);
    }
}

void WatchList::deleteMovie(const Movies &movie) {
    auto it = std::find(this->movies.begin(), this->movies.end(), movie);
    if (it != this->movies.end()) {
        this->movies.erase(it);
    }
}

Movies WatchList::getCurrent() {
    if (this->current == this->movies.size()) {
        this->current = 0;
    }
    return this->movies[this->current];
}

void WatchList::playTrailer() {
    if (this->movies.size() == 0) {
        return;
    }
    this->current = 0;
    Movies currentMovie = this->getCurrent();
    currentMovie.play();
}

void WatchList::next() {
    if (this->movies.size() == 0) {
        return;
    }
    this->current++;
    Movies currentMovie = this->getCurrent();
    currentMovie.play();
}

bool WatchList::isEmpty() {
    return this->movies.size() == 0;
}

bool WatchList::MovieExists(const Movies &movie) const {
    return std::find(this->movies.begin(), this->movies.end(), movie) != this->movies.end();
}

