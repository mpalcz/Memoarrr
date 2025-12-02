#include "Board.h"
#include "Card.h"
#include "CardDeck.h"
#include "Game.h"
#include "Player.h"
#include "Rubis.h"
#include "RubisDeck.h"
#include "Rules.h"
#include "Exceptions.h"          // ← fixes OutOfRange undefined
#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>

using namespace std;

int main() {
    cout << "MEMORARRRRRRRRRRRRRRRR!!\n\n";

    // get number of players
    int num_players;
    cout << "Enter the number of Players (2-4): ";
    cin >> num_players;
    while (num_players < 2 || num_players > 4) {
        cout << "Invalid, please enter 2-4 players: ";
        cin >> num_players;
    }

    Game game;
    Rules rules;
    RubisDeck& rubisDeck = RubisDeck::make_RubisDeck();

    for (int i = 0; i < num_players; ++i) {
        string name;
        cout << "Enter Player " << i + 1 << " name: ";
        cin >> name;
        Player player(name, static_cast<Player::Side>(i));
        game.addPlayer(player);
    }

    cout << game << endl;

    // MAIN LOOP - exactly follows the assignment pseudo-code + all required features
    while (!rules.gameOver(game)) {
        cout << "\n####### BEGINNING OF ROUND " << game.getRound() + 1 << " #######\n";

        game.startNewRound(); // face down all cards + activate all players + reset current/previous

        // === Temporarily reveal 3 cards directly in front of each player ===
        for (const Player& p : game.getPlayers()) {                    // const is fine here
            cout << "\n" << p.getName() << ", look at your 3 secret cards (press Enter when done):\n";

            vector<pair<Board::Letter, Board::Number>> peekCards;

            if (p.getSide() == Player::Side::top) {
                Board::Letter row = Board::Letter::A;
                peekCards = {{row, Board::Number::Two}, {row, Board::Number::Three}, {row, Board::Number::Four}};
            } else if (p.getSide() == Player::Side::bottom) {
                Board::Letter row = Board::Letter::E;
                peekCards = {{row, Board::Number::Two}, {row, Board::Number::Three}, {row, Board::Number::Four}};
            } else if (p.getSide() == Player::Side::left) {
                Board::Number col = Board::Number::One;
                peekCards = {{Board::Letter::B, col}, {Board::Letter::C, col}, {Board::Letter::D, col}};
            } else if (p.getSide() == Player::Side::right) {
                Board::Number col = Board::Number::Five;
                peekCards = {{Board::Letter::B, col}, {Board::Letter::C, col}, {Board::Letter::D, col}};
            }

            for (auto [l, n] : peekCards) game.turnFaceUp(l, n);
            cout << game.getBoard() << "\n";
            cin.ignore();
            cin.get(); // wait for Enter

            for (auto [l, n] : peekCards) game.turnFaceDown(l, n);
        }

        // === Round play ===
        while (!rules.roundOver(game)) {
            Player& currentPlayer = game.getCurrentPlayer();

            // skip inactive players
            while (!currentPlayer.isActive()) {
                game.nextPlayer();
                currentPlayer = game.getCurrentPlayer();
            }

            cout << "\nTurn: " << currentPlayer.getName() << "\n";
            cout << "Enter card (letter then number): ";

            char card_letter;
            int card_number;
            cin >> card_letter >> card_number;

            card_letter = toupper(card_letter);
            Board::Letter l = static_cast<Board::Letter>(card_letter - 'A');           // A → 0, B → 1, ...
            Board::Number n = static_cast<Board::Number>(card_number - 1);             // 1 → one, 2 → two, ...

            try {
                // Flip the card
                if (!game.turnFaceUp(l, n)) {
                    cout << "Card already face up or invalid → you are out this round!\n";
                    currentPlayer.setActive(false);
                    continue;
                }

                Card* flippedCard = game.getCard(l, n);
                game.setCurrentCard(flippedCard);

                cout << game.getBoard() << "\n";

                // First card of the round → free second turn
                if (game.getPreviousCard() == nullptr) {
                    cout << "First card of the round - choose another card!\n";
                    continue;
                }

                // Check match
                if (!rules.isValid(game)) {
                    cout << "No match! " << currentPlayer.getName() << " is out this round.\n";
                    game.turnFaceDown(l, n);
                    currentPlayer.setActive(false);
                } else {
                    cout << "Match! Play again!\n";
                }

            } catch (const OutOfRange&) {                     // ← now compiles
                cout << "Invalid position → you are out this round!\n";
                currentPlayer.setActive(false);
            }
        }

        // === Round over - give rubies to the winner ===
        cout << "\n################ ROUND " << game.getRound() << " OVER ################\n";

        for (Player& p : game.getPlayers()) {                     // ← non-const version needed
            if (p.isActive()) {
                cout << p.getName() << " wins the round!\n";

                Rubis* r = rubisDeck.getNext();
                if (!r) {
                    cout << "No more rubies!\n";
                } else {
                    p.addRubis(*r);
                    cout << p.getName() << " receives " << *r << "\n";
                }
                break;
            }
        }
    }

    // === Game over - final results ===
    cout << "\n#########################################################\n";
    cout << "##################### GAME OVER #########################\n";
    cout << "#########################################################\n\n";

    // Show scores sorted from least to most rubies
    vector<Player> finalStandings = game.getPlayers();        // copy
    sort(finalStandings.begin(), finalStandings.end(),
         [](const Player& a, const Player& b) { return a.getNRubies() < b.getNRubies(); });

    for (Player& p : finalStandings) p.setDisplayMode(true);

    cout << "Final scores (least → most rubies):\n";
    for (const Player& p : finalStandings) {
        cout << p << "\n";
    }

    cout << "\n*** " << finalStandings.back().getName() << " WINS THE GAME!!! ***\n";

    return 0;
}