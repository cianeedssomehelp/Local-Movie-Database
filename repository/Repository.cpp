#include "Repository.h"
#include "../domain/domain.h"
#include <fstream>
#include <algorithm>
using namespace std;
#include "../Exceptions/Exceptions.h"
Repository::Repository() {
}


void Repository::addMovie(std::string title, std::string genre, int year_of_release, int number_of_likes, std::string trailer)  {
    /*
     * Adds a movie to our repository.
     * parameters: title - the title of the movie
     *            genre - the genre of the movie
     *            year_of_release - the year the movie was released
     *            number_of_likes - the number of likes the movie has received
     *            trailer - the URL of the movie's trailer
     * return: void
     */
    Movies movie = Movies(title, genre, year_of_release, number_of_likes, trailer);
    auto it = std::find_if(this->movies.begin(), this->movies.end(),
        [&movie](const Movies& existingMovie) {
            return existingMovie.getTitle() == movie.getTitle() &&
                   existingMovie.getGenre() == movie.getGenre() &&
                   existingMovie.getYearOfRelease() == movie.getYearOfRelease();
        });

    if (it != this->movies.end()) {
        throw DuplicateMovieException();
    }

    this->movies.push_back(movie);
}

void Repository::removeMovie(std::string title, std::string genre, int year_of_release) {
    Movies movieToRemove = getMovie(title, genre, year_of_release);
    auto it = std::find_if(this->movies.begin(), this->movies.end(),
        [&movieToRemove](const Movies& movie) {
            return movie == movieToRemove;
        });
    if (it == this->movies.end()) {
        throw InexistentMovieException();
    }
    this->movies.erase(it);
}

void Repository::updateMovieLikes(const std::string& title, const std::string& genre, int year_of_release, int newLikes) {
    auto it = std::find_if(this->movies.begin(), this->movies.end(),
        [&title, &genre, year_of_release](const Movies& movie) {
            return movie.getTitle() == title && movie.getGenre() == genre && movie.getYearOfRelease() == year_of_release;
        });
    if (it == this->movies.end()) {
        throw InexistentMovieException();
    }
    it->setNumberOfLikes(newLikes);
}


void Repository::updateMovieTrailer(const std::string& title, const std::string& genre, int year_of_release, const std::string& newTrailer) {
    auto it = std::find_if(this->movies.begin(), this->movies.end(),
        [&title, &genre, year_of_release](const Movies& movie) {
            return movie.getTitle() == title && movie.getGenre() == genre && movie.getYearOfRelease() == year_of_release;
        });
    if (it == this->movies.end()) {
        throw InexistentMovieException();
    }
    it->setTrailer(newTrailer);
}


Movies Repository::getMovie(std::string title, std::string genre, int year_of_release) {
    auto it = std::find_if(this->movies.begin(), this->movies.end(),
        [&title, &genre, year_of_release](const Movies& movie) {
            return movie.getTitle() == title && movie.getGenre() == genre && movie.getYearOfRelease() == year_of_release;
        });

    if (it != this->movies.end()) {
        return *it;
    }
    return Movies("", "", 0, 0, "");
}

std::vector<Movies> Repository::getAllMovies() {
    /*
     * Returns all movies stored in the repository.
     */
    return this->movies;
}

int Repository::getSize() const {
    /*
     * Returns the size of the repository.
     */
    return this->movies.size();
}





