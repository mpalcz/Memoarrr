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
    Player::Side turn = Player::Side::top; // keep track of whos turn it is (top by default)

  public:
    Game(); // default constructor, we will add players after construction
    int getRound() const { return round; }
    void addPlayer(const Player &);
    Player &getPlayer(Player::Side);
    const Card *getPreviousCard() const { return previous; } // return a const and also make the method const since we arent changing anyhting
    const Card *getCurrentCard() const { return current; }   // can only call const methods on a const object (relevant for Rules class)
    void setCurrentCard(const Card *c);
    Card *getCard(const Board::Letter &, const Board::Number &);
    void setCard(const Board::Letter &, const Board::Number &, Card *);
    friend std::ostream &operator<<(std::ostream &os, const Game &g); // cout << operator

    const std::vector<Player> &getPlayers() const { return players; } // let others check the players but not modify them
    Player::Side getTurn() const { return turn; }                     // get the player whos turn it is
    void rotateTurn() {
        // cast the integer back to an enum and have turn circle back based on number of players
        turn = static_cast<Player::Side>((static_cast<int>(turn) + 1) % players.size());
    }
};
#endif