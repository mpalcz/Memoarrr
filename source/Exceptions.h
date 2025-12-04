// Exceptions.h: Custom exceptions for the game.

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

// Thrown when a board coordinate (Letter,Number) is outside valid range.
struct OutOfRange : public std::out_of_range {
    OutOfRange() : std::out_of_range("Invalid Letter/Number combination") {}
};

// Thrown if we run out of cards building the board.
struct NoMoreCards : public std::runtime_error {
    NoMoreCards() : std::runtime_error("No more cards available to construct the board.") {}
};

#endif
