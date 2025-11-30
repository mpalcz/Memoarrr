#include <Card.h>
#include <Game.h>
#include <Rules.h>

bool Rules::isValid(const Game &g) {
    const Card *current = g.getCurrentCard();
    const Card *previous = g.getPreviousCard();

    // equal if either the background colour or the animal are the same
    bool animal_equal = FaceAnimal(*current) == FaceAnimal(*previous);
    bool bg_equal = FaceBackground(*current) == FaceBackground(*previous);

    return animal_equal || bg_equal;
}
bool Rules::gameOver(const Game &g) { return g.getRound() == 6; }
bool Rules::roundOver(const Game &g) {
    // check if all players in the game are active
    const std::vector<Player> &players = g.getPlayers(); // const method call
    for (int i = 0; i < players.size(); ++i) {
        if (players[i].isActive()) {
            return false; // at least one player is still active so the round is not over
        }
    }
    return true;
}
const Player &Rules::getNextPlayer(const Game &g) {
    int nextIndex = (g.getCurrentPlayerIndex() + 1) % g.getPlayers().size();
    return g.getPlayers()[nextIndex];
}