#ifndef USERINPUT_H
#define USERINPUT_H

#include "Board.h"
#include "Game.h"
#include "Exceptions.h"
#include <iostream>
#include <string>
#include <sstream>
#include <utility> // for std::pair

std::string cleanInput(const std::string& input);
std::pair<Board::Letter, Board::Number> getUserInputCard(Game& game);
std::string capitalizeName(const std::string& name);

#endif