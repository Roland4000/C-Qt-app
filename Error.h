//
// Created by Legion user on 03.05.2024.
//

#ifndef QTIE_ERROR_H
#define QTIE_ERROR_H

#include <string>
#include <utility>
using std::string;

class Error: public std::exception {
public:
    explicit Error(string message):message(std::move(message)){};
    [[nodiscard]] const string& getMessage() const;
private:
    string message;
};



#endif //QTIE_ERROR_H
