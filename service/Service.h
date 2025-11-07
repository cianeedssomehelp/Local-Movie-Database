#pragma once
#include "../domain/domain.h"
#include "../repository/Repository.h"
#include "../repository/IRepository.h"
#include "../WatchList/WatchList.h"
#include "../repository/FileWatchlist.h"
#include "C:\Users\patri\OneDrive\Documents\GitHub\a6-7-cianeedssomehelp\validator.h"


#ifndef SERVICE_H
#define SERVICE_H

class Service {
    private:
        IRepository& repo;
        WatchList& watchlist;
        MovieValidator validator;
        FileWatchlist* fileWatchlist;
    public:

    Service(IRepository& repo, WatchList& watchlist, FileWatchlist* fileWatchlist = nullptr)
    : repo(repo), watchlist(watchlist), fileWatchlist(fileWatchlist) {}
        bool addMovie(const std::string &title, const std::string &genre, int year_of_release, int number_of_likes, const std::string &
                      trailer);
        bool addMovietoWatchlist(const std::string &title, const std::string &genre, int year_of_release,
                                 int number_of_likes,
                                 const std::string &trailer);
        void removeMovie(const std::string &title, const std::string &genre, int year_of_release);
        void removeMovieFromWatchlist(const std::string &title, const std::string &genre, int year_of_release);
        void startWatchlist();
        void nextMovieFromWatchlist();
        void updateMovieLikes(const std::string &title, const std::string &genre, int year_of_release, int newLikes);
        void updateMovieTrailer(const std::string &title, const std::string &genre, int year_of_release,
                                const std::string &newTrailer);
        int MovieExists(const std::string &title, const std::string &genre, int year_of_release);
        Movies getMovies(const std::string &title, const std::string &genre, int year_of_release);
        std::vector<Movies> getAllMovies();
        std::vector<Movies> filterMoviesByGenre(const std::string &genre, const std::string &title, int year_of_release);
        IRepository& getRepo() const {return repo;}
        WatchList& getWatchlist() const {return watchlist;}
        void saveWatchlist(const std::string &filename);

        void openWatchlist() const;

        bool movieExistsInWatchlist(const std::string &title, const std::string &genre, int year_of_release) const;

        void setWatchlistFilename(const std::string& filename) {
            if (fileWatchlist) {
                fileWatchlist->setFilename(filename);
            }
        }

        std::string getWatchlistFilename() const {
            if (fileWatchlist) {
                return fileWatchlist->getFilename();
            }
            return "";
        }

};

#endif //SERVICE_H
