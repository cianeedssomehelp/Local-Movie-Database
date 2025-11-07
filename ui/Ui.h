#pragma once

#ifndef UI_H
#define UI_H
#include "Service.h"

class Ui {
    private:
        Service service;
        WatchList watchlist;
        const FileWatchlist* fileWatchlist;
        std::string watchlistFileName;
    public:
        explicit Ui(const Service &service): service(service){}
        static void printMenu();
        static void printAdministratorMenu();
        static void printUserMenu();
        static void nextMenu();
        void source();

        static void stringMovie(Movies movie);

        static void stringMovieTrailer(Movies movie);

        void addMovieUi();
        void removeMovieUi();
        void updateMovieLikesUi();
        void updateMovieTrailerUi();
        void getMovieUi();
        void printAllMovies(int command);

        static void watchTrailer(const char* trailer);
        void parseThroughMovies();
        void addMovieToWatchlist();
        void removeMovieFromWatchlist();
        void printWatchlist();
        //void saveWatchlistToFile();
        void inntializeMovieDatabase();
        void innitializeWatchlist();

        void setWatchlistFilename(const std::string &filename);

        void saveWatchlistToFile();
};

#endif //UI_H
