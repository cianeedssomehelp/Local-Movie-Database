#pragma once
#include <string>
#include <vector>
#include "domain/domain.h"
#ifndef VALIDATOR_H
#define VALIDATOR_H

class MovieException : public std::exception {
private:
    std::vector<std::string> errors;
public:
    MovieException(const std::vector<std::string>& _errors);
    std::vector<std::string> getErrors() const;

};



class MovieValidator {
    public:
        MovieValidator() = default;
        void validate(const Movies& m);
};

#endif //VALIDATOR_H
