#include <Board.h>
#include <Card.h>
#include <CardDeck.h>
#include <Game.h>
#include <Player.h>
#include <Rubis.h>
#include <Rules.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    // user intput variables
    int num_players;
    string name;
    int card_letter;
    int card_number;

    cout << "MEMORARRRRRRRRRRRRRRRR!!";

    // ask for game version: TODO

    // get number of players
    cout << "Enter the number of Players: ";
    cin >> num_players;

    Game game;   // default constructor to create game (will create shuffled board as well)
    Rules rules; // will probably change based on game type

    for (int i = 0; i < num_players; ++i) {
        cout << "Enter Player " << i + 1 << " name: ";
        cin >> name;
        Player player(name, static_cast<Player::Side>(i));
        game.addPlayer(player); // pass by reference
    }

    cout << game << endl; // print board and also players with Game os

    // MAIN LOOP
    while (!rules.gameOver(game)) {
        cout << "####### BEGINNING OF ROUND " << game.getRound() << " #######";
        // flip all cards down
        game.allFacesDown();

        // let each player look at the 3 cards in front of them (temporarily)

        while (!rules.roundOver(game)) {
            Player &currentPlayer = game.getCurrentPlayer();

            if (!currentPlayer.isActive()) {
                game.nextTurn();
                continue;
            }

            cout << "Turn to choose a card: " << currentPlayer << endl << "Enter the card you would like to pick (letter first then number)" << endl;
            cout << "Letter: ";
            cin >> card_letter;
            cout << "Number: ";
            cin >> card_number;

            // update current and previous cards (to check if theres a match). Cast the user inputs to enums to call getCard
            game.setCurrentCard(game.getCard(static_cast<const Board::Letter>(card_letter), static_cast<const Board::Number>(card_number)));

            // if the round just started and its the first players turn, let them pick 2 cards
            // game.previous will be nullptr if only one card has been selected
            if (game.getPreviousCard() == nullptr) {
                continue; // let the same first player choose another card
            }

            bool isValid = rules.isValid(game);
        }
    }
}