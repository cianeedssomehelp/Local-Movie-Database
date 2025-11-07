#include "Exceptions.h"

FileException::FileException(const std::string& msg) : message(msg) {}

RepositoryException::RepositoryException() : exception{}, message{""} {}

RepositoryException::RepositoryException(const std::string& msg) : message{msg} {}

const char* RepositoryException::what() const noexcept {
    return this->message.c_str();
}

const char* DuplicateMovieException::what() const noexcept {
    return "There is another movie with the same name, genre, and year of release!";
}

const char* InexistentMovieException::what() const noexcept {
    return "There are no movies with the given name, genre, and year of release!";
}