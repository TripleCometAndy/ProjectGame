#include <iostream>
#include <exception>

struct IOException : public std::exception {
private:
    std::string message;

public:
    IOException(std::string message) {
        this->message = message;
    }

    const char* what() const throw () {
        return message.c_str();
    }
};