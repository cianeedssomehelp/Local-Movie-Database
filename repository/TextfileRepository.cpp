#include "TextfileRepository.h"
#include "Repository.h"
#include "../domain/domain.h"
#include <fstream>
using namespace std;

TextfileRepository::TextfileRepository(const std::string& fileName): name(fileName) {
    ReadFromFile();
}
void TextfileRepository::addMovie(std::string title, std::string genre, int year_of_release, int number_of_likes, std::string trailer)  {

    Repository::addMovie(title, genre, year_of_release, number_of_likes, trailer);
    WriteToFile();
}

void TextfileRepository::removeMovie(std::string title, std::string genre, int year_of_release) {
   Repository::removeMovie(title, genre, year_of_release);
   WriteToFile();
}

void TextfileRepository::updateMovieLikes(const std::string& title, const std::string& genre, int year_of_release, int newLikes) {
    Repository::updateMovieLikes(title, genre, year_of_release, newLikes);
    WriteToFile();
}


void TextfileRepository::updateMovieTrailer(const std::string& title, const std::string& genre, int year_of_release, const std::string& newTrailer) {
    Repository::updateMovieTrailer(title, genre, year_of_release, newTrailer);
    WriteToFile();
}

void TextfileRepository::WriteToFile() {
    std::ofstream file(this->name);
    for (auto& movie : this->getAllMovies()) {
        file << movie;
    }
    file.close();
}

void TextfileRepository::ReadFromFile() {
    std::ifstream file(this->name);
    Movies movie;
    while (file >> movie) {
        Repository::addMovie(movie.getTitle(), movie.getGenre(), movie.getYearOfRelease(), movie.getNumberOfLikes(), movie.getTrailer());
    }
    file.close();
}






