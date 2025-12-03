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
    Player::Side turn = Player::Side::top; // probably can be removed (switched to currnetPlayerIndex)
    int currentPlayerIndex = 0;

  public:
    // methods asked for in the assignment
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

    // added methods (not in assignment description)
    void allFacesDown() { gameBoard.allFacesDown(); } // so that Game can flip all cards
    const Board &getBoard() const { return gameBoard; }
    int getCurrentPlayerIndex() const { return currentPlayerIndex; }
    Player &getCurrentPlayer() { return players[currentPlayerIndex]; }
    const Player &getCurrentPlayer() const { return players[currentPlayerIndex]; } // have a const one as well so we can get the player without change
    void activatePlayer(Player &p) { p.setActive(true); }
    void deactivatePlayer(Player &p) { p.setActive(false); }
    void deactivateCurrentPlayer() { deactivatePlayer(getCurrentPlayer()); }
    void startRound();
    const std::vector<Player> &getPlayers() const { return players; } // let others check the players but not modify them
    std::vector<Player> &getPlayers() { return players; }             // also need a non-const for adding rubis
    Player::Side getTurn() const { return turn; }                     // get the player whos turn it is
    void nextTurn() { currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); }
    void peekCards(int boardSize);
};
#endif