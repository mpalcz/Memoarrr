#ifndef GAME_H
#define GAME_H
#include <Board.h>
#include <Card.h>
#include <Player.h>

class Game {
  private:
    Board board;

  public:
    Game();
    int getRound();
    void addPlayer(const Player &);
    Player &getPlayer(Player::Side);
    const Card *getPreviousCard();
    const Card *getCurrentCard();
    void setCurrentCard(const Card *);
    Card *getCard(const Board::Letter &, const Board::Number &);
    void setCard(const Board::Letter &, const Board::Number &, Card *);
};
#endif