#ifndef GAME_H
#define GAME_H
#include <Board.h>
#include <Card.h>
#include <Player.h>
#include <vector> // for keep track of players

class Game {
  private:
    Board gameBoard; // calls Board constructor
    int round = 0;
    std::vector<Player> players;
    const Card *current = nullptr; // const since these are just pointers not changing the Card
    const Card *previous = nullptr;

  public:
    Game(); // default constructor, we will add players after construction
    int getRound() { return round; }
    void addPlayer(const Player &);
    Player &getPlayer(Player::Side);
    const Card *getPreviousCard() { return previous; }
    const Card *getCurrentCard() { return current; }
    void setCurrentCard(const Card *c);
    Card *getCard(const Board::Letter &, const Board::Number &);
    void setCard(const Board::Letter &, const Board::Number &, Card *);
    friend std::ostream &operator<<(std::ostream &os, const Game &g); // cout << operator
};
#endif