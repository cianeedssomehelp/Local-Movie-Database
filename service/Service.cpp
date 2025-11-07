#include "Service.h"
#include <string>
#include "../domain/domain.h"
#include <algorithm>
#include "../WatchList/WatchList.h"
#include "../repository/FileWatchlist.h"
#include "../validator.h"

bool Service::addMovie(const std::string& title, const std::string& genre, int year_of_release, int number_of_likes, const std::string& trailer) {
    const auto& movies = this->repo.getAllMovies();
    Movies movieToAdd = Movies(title, genre, year_of_release, number_of_likes, trailer);
    this->validator.validate(movieToAdd);
    this->repo.addMovie(title, genre, year_of_release, number_of_likes, trailer);
    return true;
}

bool Service::addMovietoWatchlist(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer) {
    Movies movieToAdd = this->repo.getMovie(title, genre, year);
    if (this->watchlist.MovieExists(movieToAdd)) {
        return false;
    }
    this->watchlist.add(movieToAdd);
    return true;
}

void Service::removeMovie(const std::string& title, const std::string& genre, int year_of_release) {
    this->repo.removeMovie(title, genre, year_of_release);
}

void Service::removeMovieFromWatchlist(const std::string& title, const std::string& genre, int year_of_release) {
    Movies movieToRemove = this->repo.getMovie(title, genre, year_of_release);

    this->watchlist.deleteMovie(movieToRemove);
}

void Service::startWatchlist() {
    this->watchlist.playTrailer();
}

void Service::nextMovieFromWatchlist() {
    this->watchlist.next();
}

void Service::updateMovieLikes(const std::string &title, const std::string &genre, int year_of_release, int newLikes) {
    Movies movieToUpdate = this->repo.getMovie(title, genre, year_of_release);
    this->validator.validate(movieToUpdate);
    this->repo.updateMovieLikes(title, genre, year_of_release, newLikes);
}

void Service::updateMovieTrailer(const std::string &title, const std::string &genre, int year_of_release, const std::string &newTrailer) {
    Movies movieToUpdate = this->repo.getMovie(title, genre, year_of_release);
    this->validator.validate(movieToUpdate);
    this->repo.updateMovieTrailer(title, genre, year_of_release, newTrailer);
}


int Service::MovieExists(const std::string& title, const std::string& genre, int year_of_release) {
    const auto& movies = this->repo.getAllMovies();
    return std::count_if(movies.begin(), movies.end(),
        [&title, &genre, year_of_release](const Movies& movie) {
            return !movie.getTitle().empty() &&
                   movie.getTitle() == title &&
                   movie.getGenre() == genre &&
                   movie.getYearOfRelease() == year_of_release;
        });
}

Movies Service::getMovies(const std::string& title, const std::string& genre, int year_of_release) {
    return this->repo.getMovie(title, genre, year_of_release);
}

std::vector<Movies> Service::getAllMovies() {
    return this->repo.getAllMovies();
}

std::vector<Movies> Service::filterMoviesByGenre(const std::string& genre, const std::string& title, int year_of_release) {
    std::vector<Movies> filteredMovies;
    const std::vector<Movies>& allMovies = this->repo.getAllMovies(); // Avoid repeated calls

    std::copy_if(allMovies.begin(), allMovies.end(), std::back_inserter(filteredMovies),
        [&genre, &title, year_of_release](const Movies& movie) {
            return (genre.empty() || movie.getGenre() == genre) &&
                   !(movie.getTitle() == title && movie.getYearOfRelease() == year_of_release);
        });

    return filteredMovies;
}

void Service::saveWatchlist(const std::string& filename) {
    if (fileWatchlist) {
        fileWatchlist->setFilename(filename);
        fileWatchlist->setMovies(this->watchlist.getMovies());
        fileWatchlist->writeToFile();
    } else {
        throw std::runtime_error("FileWatchlist is not initialized!");
    }
}

void Service::openWatchlist() const {
    if (this->fileWatchlist->isEmpty())
        return;
    this->fileWatchlist->displayWatchlist();
}
bool Service::movieExistsInWatchlist(const std::string& title, const std::string& genre, int year_of_release) const {
    Movies movieToCheck = this->repo.getMovie(title, genre, year_of_release);
    return this->watchlist.MovieExists(movieToCheck);
}
