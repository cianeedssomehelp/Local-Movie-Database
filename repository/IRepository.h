#pragma once
#include <vector>
#include "../domain/domain.h"
#ifndef IREPOSITORY_H
#define IREPOSITORY_H

class IRepository {
    public:
        virtual void addMovie(std::string title, std::string genre, int year_of_release, int number_of_likes, std::string trailer) = 0;
        virtual void removeMovie(std::string title, std::string genre, int year_of_release) = 0;
        virtual void updateMovieLikes(const std::string &title, const std::string &genre, int year_of_release, int newLikes) = 0;
        virtual void updateMovieTrailer(const std::string &title, const std::string &genre, int year_of_release, const std::string &newTrailer) = 0;
        virtual Movies getMovie(std::string title, std::string genre, int year_of_release) = 0;
        virtual std::vector<Movies> getAllMovies() = 0;

        virtual int getSize() const = 0;

        virtual ~IRepository() = default;
};

#endif //IREPOSITORY_H
