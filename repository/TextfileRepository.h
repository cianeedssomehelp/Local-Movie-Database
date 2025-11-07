#pragma once
#include "../domain/domain.h"
#include "Repository.h"
#include <fstream>
#include <vector>
#ifndef TEXTFILEREPOSITORY_H
#define TEXTFILEREPOSITORY_H

class TextfileRepository : public Repository {
        std::string name;
        void ReadFromFile();
        void WriteToFile();
    public:
        TextfileRepository(const std::string& fileName);
        void addMovie(std::string title, std::string genre, int year_of_release, int number_of_likes, std::string trailer) override;
        void removeMovie(std::string title, std::string genre, int year_of_release) override;
        void updateMovieLikes(const std::string &title, const std::string &genre, int year_of_release, int newLikes) override;
        void updateMovieTrailer(const std::string &title, const std::string &genre, int year_of_release, const std::string &newTrailer) override;

};
#endif //TEXTFILEREPOSITORY_H
