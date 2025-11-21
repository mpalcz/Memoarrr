#ifndef RULES_H
#define RULES_H

class Game;
class Player;

class Rules {
    public:
        bool isValid(const Game&);
        bool gameOver(const Game&);
        bool roundOver(const Game&);
        const Player& getNextPlayer(const Game&);
};

#endif