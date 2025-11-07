#include "CSVRepository.h"
#include <fstream>
#include <Windows.h>
#include "../Exceptions/Exceptions.h"
using namespace std;
#include <iostream>
#include <stdexcept>

CVSRepository::CVSRepository(const std::string& watchlistFileName) {
    this->filename = watchlistFileName;
    readFromFile();
}

void CVSRepository::writeToFile() {
    std::ofstream f(this->filename);
    if (!f.is_open()) {
        throw FileException("The file could not be opened!");
    }

    const std::vector<Movies>& watchlistMovies = this->movies;
    for (const auto& movie : watchlistMovies) {
        f << movie;
    }

    f.close();
}

void CVSRepository::readFromFile() {
    ifstream file(this->filename);
    if (!file.is_open())
        throw FileException("The file could not be opened!");

    Movies s;
    while (file >> s) {
        this->movies.push_back(s);
    }
    file.close();
}

void CVSRepository::displayWatchlist() const {
    string command = "notepad \"" + this->filename + "\"";
    system(command.c_str());
}
