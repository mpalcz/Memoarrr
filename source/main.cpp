#include <Board.h>
#include <Card.h>
#include <CardDeck.h>
#include <Game.h>
#include <Player.h>
#include <Rubis.h>
#include <RubisDeck.h>
#include <Rules.h>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {
    // user intput variables
    int num_players;
    string name;
    char card_letter;
    int card_number;

    cout << "MEMORARRRRRRRRRRRRRRRR!!";

    // ask for game version: TODO

    // get number of players
    cout << "Enter the number of Players: ";
    cin >> num_players;

    Game game;   // default constructor to create game (will create shuffled board as well)
    Rules rules; // will probably change based on game type
    RubisDeck &rubisDeck = RubisDeck::make_RubisDeck();

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
        game.startRound(); // put all cards face down, reset current etc.

        // let each player look at the 3 cards in front of them (temporarily)

        while (!rules.roundOver(game)) {
            Player &currentPlayer = game.getCurrentPlayer();

            // cycle to next active player
            while (!currentPlayer.isActive()) {
                game.nextTurn();
                currentPlayer = game.getCurrentPlayer();
            }

            cout << "Turn to choose a card: " << currentPlayer << endl << "Enter the card you would like to pick (letter first then number)" << endl;
            cout << "Letter: ";
            cin >> card_letter;
            cout << "Number: ";
            cin >> card_number;

            card_letter = toupper(card_letter);
            Board::Letter l = static_cast<Board::Letter>(card_letter - 'A' + 1); // since enum is A=1, etc
            Board::Number n = static_cast<Board::Number>(card_number - 1);       // cast int to Number enum

            // flip the selected card and display this in the board:
            Card *flippedCard = game.getCard(l, n); // getCard flips it as well

            // show board with flipped card
            cout << "Card (" << l << n << " was selected." << endl;
            cout << game.getBoard() << endl;

            // update current and previous cards (to check if theres a match)
            game.setCurrentCard(flippedCard);

            // if the round just started and its the first players turn, let them pick 2 cards
            // game.previous will be nullptr if only one card has been selected
            if (game.getPreviousCard() == nullptr) {
                cout << "First card of the round - you get to choose another card." << endl;
                continue; // let the same first player choose another card
            }

            // if the player did not select the right card, make them inactive. Next loop iteration the turn will rotate.
            if (!rules.isValid(game)) {
                cout << "Not a match! " << currentPlayer.getName() << " is out this round." << endl;
                flippedCard->turnFaceDown(); // is a pointer so it
                currentPlayer.setActive(false);
            } else {
                cout << "Good match! you can go again." << endl;
            }
        }

        cout << "################ ROUND " << game.getRound() + 1 << " OVER ################";

        for (Player &p : game.getPlayers()) {
            if (p.isActive()) {
                cout << p.getName() << " wins this round!!";
                if (rubisDeck.isEmpty()) {
                    cout << "Rubis Deck is Empty! Exiting";
                    return 1;
                } else {
                    const Rubis *rubiCard = rubisDeck.getNext();
                    p.addRubis(*rubiCard);
                    cout << p.getName() << " got " << *rubiCard << endl;
                }
                break;
            }
        }
    }

    cout << "#########################################################";
    cout << "##################### GAME OVER #########################";
    cout << "#########################################################";

    // get player with the most points
    int maxRubis = 0;
    Player winner;
    for (const Player &p : game.getPlayers()) {
        int playerRubis = p.getNRubies();
        if (playerRubis > maxRubis) {
            maxRubis = playerRubis;
            winner = p;
        }
    }

    cout << winner.getName() << " WINS THE GAME!!!!!!!!!!";
    return 0;
}