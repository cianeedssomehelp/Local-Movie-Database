#include "HTMLRepository.h"
#include <fstream>
#include <Windows.h>
#include "../Exceptions/Exceptions.h"

HTMLRepository::HTMLRepository(const std::string& watchlistFileName) : FileWatchlist(watchlistFileName) {
}

void HTMLRepository::writeToFile() {
    std::ofstream f(this->filename);

    if (!f.is_open())
        throw FileException("The file could not be opened!");

    // Write HTML structure
    f << "<!DOCTYPE html>\n<html>\n<head>\n<title>Watchlist</title>\n</head>\n<body>\n";
    f << "<h1>Watchlist</h1>\n<table border=\"1\">\n";
    f << "<tr><th>Title</th><th>Genre</th><th>Year</th><th>Likes</th><th>Trailer</th></tr>\n";

    for (const auto& movie : this->movies) {
        f << "<tr>";
        f << "<td>" << movie.getTitle() << "</td>";
        f << "<td>" << movie.getGenre() << "</td>";
        f << "<td>" << movie.getYearOfRelease() << "</td>";
        f << "<td>" << movie.getNumberOfLikes() << "</td>";
        f << "<td><a href=\"" << movie.getTrailer() << "\">Link</a></td>";
        f << "</tr>\n";
    }

    f << "</table>\n</body>\n</html>";
    f.close();
}

void HTMLRepository::displayWatchlist() const {
    std::string command = "start " + this->filename;
    system(command.c_str());
}

