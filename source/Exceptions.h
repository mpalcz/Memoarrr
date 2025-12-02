#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

struct OutOfRange : public std::out_of_range {
    OutOfRange() : std::out_of_range("Invalid Letter/Number combination") {}
};

struct NoMoreCards : public std::runtime_error {
    NoMoreCards() : std::runtime_error("No more cards available to construct the board.") {}
};

struct InvalidPosition : public std::runtime_error {
    InvalidPosition() : std::runtime_error("Card position chosen is invalid") {}
};

#endif