#pragma once
#include <stdexcept>
#include <string>

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class FileException : public std::exception {
private:
    std::string message;

public:
    explicit FileException(const std::string& msg);

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class RepositoryException : public std::exception {
protected:
    std::string message;

public:
    RepositoryException();
    RepositoryException(const std::string& msg);
    virtual ~RepositoryException() {}
    virtual const char* what() const noexcept override;
};

class DuplicateMovieException : public RepositoryException {
public:
    const char* what() const noexcept override;
};

class InexistentMovieException : public RepositoryException {
public:
    const char* what() const noexcept override;
};

#endif // EXCEPTIONS_H