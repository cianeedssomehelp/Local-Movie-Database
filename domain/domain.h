#pragma once
#include <string>
#include <vector>
#ifndef DOMAIN_H
#define DOMAIN_H
#include "C:\Users\patri\OneDrive\Documents\GitHub\a6-7-cianeedssomehelp\Utils.h"
#include <iostream>
using namespace std;
class Movies {
    Movies* movie{};
    private:
        std::string title; //unique, the movie is identified by its title
        std::string genre;
        int year_of_release; //unique, the movie is identified by its year of release
        int number_of_likes;
        std::string trailer;
    public:
        Movies();
        Movies(const std::string& title, const std::string& genre, int year_of_release, int number_of_likes, const std::string& trailer);
        int getYearOfRelease() const;
        int getNumberOfLikes() const;

        std::string getTrailer() const;
        std::string getTitle() const;
        std::string getGenre() const;
        void setNumberOfLikes(int newNumberOfLikes);
        void setTrailer(const std::string &newTrailer);

        void play();

        friend std::ostream& operator<<(std::ostream& os, const Movies& movie) {
            os << movie.getTitle() << ","
               << movie.getGenre() << ","
               << movie.getYearOfRelease() << ","
               << movie.getNumberOfLikes() << ","
               << movie.getTrailer() << "\n";
            return os;
        }

        friend std::istream& operator>>(std::istream& is, Movies& movie) {
            std::string line;
            getline(is, line);
            std::vector<std::string> result = split(line, ',');
            if (result.size() == 5) {
                movie.title = result[0];
                movie.genre = result[1];
                movie.year_of_release = std::stoi(result[2]);
                movie.number_of_likes = std::stoi(result[3]);
                movie.trailer = result[4];
            }
            return is;
        }

    bool operator==(const Movies &other) const {
            return this->title == other.title && this->genre == other.genre && this->year_of_release == other.year_of_release;
    }

};

#endif //DOMAIN_H
