#include "domain.h"
#include <iostream>
#include <cstring>
#include <Windows.h>
#include <shellapi.h>

using namespace std;

Movies::Movies() {
    /*
    Description: Initializes a Movies object with default values.
    Default Values:
    title: ""
    genre: ""
    trailer: ""
    year_of_release: 0
    number_of_likes: 0
     */
    this->title = "";
    this->genre = "";
    this->trailer = "";
    this->year_of_release = 0;
    this->number_of_likes = 0;
}

Movies::Movies(const std::string& title, const std::string& genre, int year_of_release, int number_of_likes, const std::string& trailer) {
    /*
    Description: Initializes a Movies object with the provided values.
    Parameters:
        title: The title of the movie.
        genre: The genre of the movie.
        year_of_release: The year the movie was released.
        number_of_likes: The number of likes the movie has received.
        trailer: The URL of the movie's trailer.
     */
    this->title = title;
    this->genre = genre;
    this->year_of_release = year_of_release;
    this->number_of_likes = number_of_likes;
    this->trailer = trailer;
}
int Movies::getNumberOfLikes() const {
    /*
     * return: number of likes of the movie
     */
    return this->number_of_likes;
}

std::string Movies::getTrailer() const {
    /*
     * return: trailer of the movie
     */
    return this->trailer;
}

std::string Movies::getTitle() const {
    /*
     * return: title of the movie
     */
    return this->title;
}

std::string Movies::getGenre() const {
    /*
     * return: genre of the movie
     */
    return this->genre;
}

int Movies::getYearOfRelease() const {
    /*
     * return: year of release of the movie
     */
    return this->year_of_release;
}

void Movies::setNumberOfLikes(int newNumberOfLikes) {
    /*
     * Sets the number of likes of the movie.
     * param: newNumberOfLikes - int
     */
    this->number_of_likes = newNumberOfLikes;
}


void Movies::setTrailer(const std::string& newTrailer) {
    /*
     * Sets the trailer of the movie.
     * param: newTrailer - string
     */
    this->trailer = newTrailer;
}

void Movies::play() {
    std::wstring wideBrave = L"brave.exe";
    std::wstring wideTrailer = std::wstring(this->trailer.begin(), this->trailer.end());

    ShellExecuteW(NULL, NULL, wideBrave.c_str(), wideTrailer.c_str(), NULL, SW_SHOWMAXIMIZED);
}



