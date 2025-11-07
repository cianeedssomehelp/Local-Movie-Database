#include "validator.h"

inline MovieException::MovieException(const std::vector<std::string> &_errors) {
}

std::vector<std::string> MovieException::getErrors() const {
    return this->errors;
}

void MovieValidator::validate(const Movies &movie) {
    std::vector<std::string> errors;
    if (movie.getTitle().empty()) {
        errors.push_back("Title cannot be empty!");
    }
    if (movie.getGenre().empty()) {
        errors.push_back("Genre cannot be empty!");
    }
    if (movie.getYearOfRelease() < 1888 || movie.getYearOfRelease() > 2025) {
        errors.push_back("Year must be between 1888 and 2025!");
    }
    if (movie.getNumberOfLikes() < 0) {
        errors.push_back("Likes cannot be negative!");
    }
    if (!errors.empty()) {
        throw MovieException(errors);
    }
}