// main.cpp - Memoarrr! FINAL VERSION WITH DEBUG CONSOLE KEPT
// CSI2372A Fall 2025 - University of Ottawa

#include "Board.h"
#include "Card.h"
#include "CardDeck.h"
#include "Exceptions.h"
#include "Game.h"
#include "Player.h"
#include "Rubis.h"
#include "RubisDeck.h"
#include "Rules.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string cleanInput(const string& input) {
    string s = input;
    size_t start = s.find_first_not_of(' ');
    if (start == string::npos) return "";
    s = s.substr(start);
    size_t end = s.find_last_not_of(' ');
    s = s.substr(0, end + 1);

    ostringstream out;
    bool inSpace = false;
    for (char c : s) {
        if (c == ' ') {
            if (!inSpace) out << ' ';
            inSpace = true;
        } else {
            out << c;
            inSpace = false;
        }
    }
    return out.str();
}

// Respect Walrus: a blocked face-down card isn't a valid choice
bool hasFaceDownCards(const Game& game) {
    auto blocked = game.getBlockedPosition();

    for (int i = 0; i < GameParameters::BoardSize; ++i) {
        for (int j = 0; j < GameParameters::BoardSize; ++j) {
            if (i == GameParameters::CenterRow && j == GameParameters::CenterCol) continue;

            Board::Letter l = Board::getEnumAt<Board::Letter>(i);
            Board::Number n = Board::getEnumAt<Board::Number>(j);

            if (blocked && l == blocked->first && n == blocked->second) {
                // Blocked by Walrus: treat as unavailable to flip
                continue;
            }

            if (!game.isFaceUp(l, n)) return true;
        }
    }
    return false;
}

int main() {
    cout << "WELCOME TO MEMOARRR!\n\n";

    // Choose game version
    string gameVersion;
    const array<string, 4> validVersions = {"base", "expert display", "expert rules", "both"};
    do {
        cout << "Choose game version (base/expert display/expert rules/both): ";
        getline(cin, gameVersion);
        gameVersion = cleanInput(gameVersion);
    } while (find(validVersions.begin(), validVersions.end(), gameVersion) == validVersions.end());

    bool expertDisplay = (gameVersion == "expert display" || gameVersion == "both");
    bool expertRules   = (gameVersion == "expert rules"   || gameVersion == "both");

    // Create card deck first (must exist before Board constructor)
    CardDeck::make_CardDeck(expertRules);

    // Number of players
    int num_players;
    string input;
    do {
        cout << "Enter the number of Players [2-4]: ";
        getline(cin, input);
        input = cleanInput(input);
    } while (input != "2" && input != "3" && input != "4");
    num_players = stoi(input);

    // Create game and players
    Game game(expertDisplay, expertRules);
    Rules rules;
    RubisDeck& rubisDeck = RubisDeck::make_RubisDeck();

    for (int i = 0; i < num_players; ++i) {
        string name;
        do {
            cout << "Enter Player " << i + 1 << " name: ";
            getline(cin, name);
            name = cleanInput(name);
            if (name.empty()) cout << "Name cannot be empty.\n";
        } while (name.empty());
        Player p(name, Board::getEnumAt<Player::Side>(i));
        game.addPlayer(p);
    }

    cout << '\n' << game << '\n';

    // ==================================================================
    // ==================== DEBUG FULL BOARD REVEAL =====================
    // ==================================================================
    cout << "\n=== DEBUG: FULL BOARD REVEAL ===\n";
    for (int i = 0; i < GameParameters::BoardSize; ++i) {
        for (int j = 0; j < GameParameters::BoardSize; ++j) {
            if (i == GameParameters::CenterRow && j == GameParameters::CenterCol) continue;
            Board::Letter l = Board::getEnumAt<Board::Letter>(i);
            Board::Number n = Board::getEnumAt<Board::Number>(j);
            game.turnFaceUp(l, n);
        }
    }
    cout << game << "\n";
    cout << "(press Enter to continue to actual game)";
    string dummy;
    getline(cin, dummy);

    // Turn everything face down again
    game.allFacesDown();
    cout << "\n=== DEBUG: END FULL BOARD REVEAL ===\n\n";
    // ==================================================================

    // MAIN GAME LOOP - 7 rounds
    while (!rules.gameOver(game)) {
        cout << "\n-------- BEGINNING OF ROUND " << game.getRound() + 1 << " --------\n";

        game.startNewRound();

        // Peek at 3 cards in front of each player
        for (const Player& p : game.getPlayers()) {
            cout << "\n" << p.getName() << ", look at your 3 secret cards:\n";

            vector<pair<Board::Letter, Board::Number>> peek;
            Player::Side side = p.getSide();
            int mid = GameParameters::BoardSize / 2;

            switch (side) {
                case Player::Side::top:
                    peek = {
                        {Board::getEnumAt<Board::Letter>(0), Board::getEnumAt<Board::Number>(mid-1)},
                        {Board::getEnumAt<Board::Letter>(0), Board::getEnumAt<Board::Number>(mid)},
                        {Board::getEnumAt<Board::Letter>(0), Board::getEnumAt<Board::Number>(mid+1)}
                    };
                    break;
                case Player::Side::bottom:
                    peek = {
                        {Board::getEnumAt<Board::Letter>(4), Board::getEnumAt<Board::Number>(mid-1)},
                        {Board::getEnumAt<Board::Letter>(4), Board::getEnumAt<Board::Number>(mid)},
                        {Board::getEnumAt<Board::Letter>(4), Board::getEnumAt<Board::Number>(mid+1)}
                    };
                    break;
                case Player::Side::left:
                    peek = {
                        {Board::getEnumAt<Board::Letter>(mid-1), Board::getEnumAt<Board::Number>(0)},
                        {Board::getEnumAt<Board::Letter>(mid),   Board::getEnumAt<Board::Number>(0)},
                        {Board::getEnumAt<Board::Letter>(mid+1), Board::getEnumAt<Board::Number>(0)}
                    };
                    break;
                case Player::Side::right:
                    peek = {
                        {Board::getEnumAt<Board::Letter>(mid-1), Board::getEnumAt<Board::Number>(4)},
                        {Board::getEnumAt<Board::Letter>(mid),   Board::getEnumAt<Board::Number>(4)},
                        {Board::getEnumAt<Board::Letter>(mid+1), Board::getEnumAt<Board::Number>(4)}
                    };
                    break;
            }

            for (auto [l, n] : peek) game.turnFaceUp(l, n);
            cout << game << "\n(press Enter when done)...";
            getline(cin, dummy);
            for (auto [l, n] : peek) game.turnFaceDown(l, n);
        }

        // PLAY ROUND
        while (!rules.roundOver(game)) {
            Player& current = game.getCurrentPlayer();
            while (!current.isActive()) {
                game.nextPlayer();
                current = game.getCurrentPlayer();
            }

            cout << "\nTurn: " << current.getName() << "\n";

            if (!hasFaceDownCards(game)) {
                cout << "No more cards to flip - you lose this turn!\n";
                current.setActive(false);
                cout << game << '\n';
                // Walrus effect counts this as a full turn for whoever was up
                game.advanceWalrusEffect();
                if (rules.roundOver(game)) break;
                game.nextPlayer();
                continue;
            }

            // Get valid position
            Board::Letter l;
            Board::Number n;
            string userInput;
            do {
                cout << "Enter card - letter then number (ex. \"a1\" or \"B2\"): ";
                getline(cin, userInput);
                userInput = cleanInput(userInput);
                if (userInput.size() != 2 ||
                    !isalpha(static_cast<unsigned char>(userInput[0])) ||
                    !isdigit(static_cast<unsigned char>(userInput[1]))) {
                    cout << "Invalid input. Please try again.\n";
                    continue;
                }
                char let = static_cast<char>(toupper(static_cast<unsigned char>(userInput[0])));
                int num = userInput[1] - '0';
                if (let < 'A' || let > 'E' || num < 1 || num > 5) {
                    cout << "Position out of range. Try again.\n";
                    continue;
                }
                l = Board::getEnumAt<Board::Letter>(let - 'A');
                n = Board::getEnumAt<Board::Number>(num - 1);

                // Check if blocked by Walrus
                auto blocked = game.getBlockedPosition();
                if (blocked && l == blocked->first && n == blocked->second) {
                    cout << "Blocked position - choose another!\n";
                    continue;
                }

                break;
            } while (true);

            try {
                if (!game.turnFaceUp(l, n)) {
                    cout << "Card already face up - you are out this round!\n";
                    current.setActive(false);
                    cout << game << '\n';
                    game.advanceWalrusEffect();
                    if (rules.roundOver(game)) break;
                    game.nextPlayer();
                    continue;
                }

                game.setCurrentPosition(l, n);
                game.setCurrentCard(game.getCard(l, n));
                cout << '\n' << game << '\n';

                // SPECIAL EFFECTS TRIGGER IMMEDIATELY (except Penguin on first card)
                if (game.isExpertRules()) {
                    game.getCurrentCard()->applyEffect(game);
                }

                // Match checking (only if not first card)
                if (game.getPreviousCard() != nullptr) {
                    if (!rules.isValid(game)) {
                        cout << "No match! " << current.getName() << " is out this round.\n";
                        current.setActive(false);
                        cout << game << '\n';
                        // Round might now be over; Walrus effect still counts this as the blocked player's turn
                    } else {
                        cout << "Match!\n";
                    }
                } else {
                    cout << "First card flipped!\n";
                }

                if (!game.getExtraTurn()) game.nextPlayer();
                game.setExtraTurn(false);

                // End of this player's turn: tick Walrus effect
                game.advanceWalrusEffect();

                if (rules.roundOver(game)) break;

            } catch (const OutOfRange&) {
                cout << "Invalid position - you are out this round!\n";
                current.setActive(false);
                cout << game << '\n';
                game.advanceWalrusEffect();
                if (rules.roundOver(game)) break;
                game.nextPlayer();
            }
        }

        // ROUND OVER - announce winner and give rubies
        cout << "\n-------- ROUND " << game.getRound() << " OVER --------\n";
        for (const Player& p : game.getPlayers()) {
            if (p.isActive()) {
                cout << p.getName() << " wins the round!\n";
                Rubis* r = rubisDeck.getNext();
                if (r) {
                    game.getPlayer(p.getSide()).addRubis(*r);
                    cout << p.getName() << " receives " << *r << "\n";
                }
                break;
            }
        }
        cout << "------------------------------\n";
    }

    // FINAL RESULTS
    cout << "\n#########################################################\n";
    cout << "##################### GAME OVER #########################\n";
    cout << "#########################################################\n\n";

    // Use pointers to the real players inside Game (no copies)
    vector<Player*> standings;
    for (Player& p : game.getPlayers()) {
        p.setDisplayMode(true);      // show rubies instead of active/side
        standings.push_back(&p);     // store address of real player
    }

    // Sort by rubies, descending
    sort(standings.begin(), standings.end(),
         [](const Player* a, const Player* b) {
             return a->getNRubies() > b->getNRubies();
         });

    cout << "Final scores (most to least rubies):\n";
    for (const Player* p : standings) {
        cout << *p << '\n';
    }

    cout << "\n-------- " << standings.front()->getName() << " WINS THE GAME!!! --------\n";

    return 0;
}
