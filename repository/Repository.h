#pragma once
#include <vector>
#include "IRepository.h"
#include "../domain/domain.h"
#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <iostream>
#include <fstream>
class Repository: public IRepository{
    private:
        std::vector<Movies> movies;
    public:
        Repository();
        void addMovie(std::string title, std::string genre, int year_of_release, int number_of_likes, std::string trailer) override;
        void removeMovie(std::string title, std::string genre, int year_of_release) override;
        void updateMovieLikes(const std::string &title, const std::string &genre, int year_of_release, int newLikes) override;
        void updateMovieTrailer(const std::string &title, const std::string &genre, int year_of_release, const std::string &newTrailer) override;
        Movies getMovie(std::string title, std::string genre, int year_of_release) override;
        std::vector<Movies> getAllMovies() override;
        int getSize() const override;

};

#endif //REPOSITORY_H
