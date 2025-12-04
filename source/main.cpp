// main.cpp: Entry point for the Memoarrr game.
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
#include <cctype>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

using namespace std;

// Function to clean up name from user input, getting rid of leading and trailing whitespace and replacing multiple spaces with one in between names
string cleanInput(const string &input) {
    string s = input;

    // Trim any leading spaces
    size_t start = s.find_first_not_of(' ');
    if (start == string::npos)
        return ""; // string was all spaces
    s = s.substr(start);

    // Trim any trailing spaces
    size_t end = s.find_last_not_of(' ');
    s = s.substr(0, end + 1);

    // Replace any multiple internal spaces with single spaces
    ostringstream out;
    bool inSpace = false;

    for (char c : s) {
        if (c == ' ') {
            if (!inSpace) {
                out << ' ';
                inSpace = true;
            }
        } else {
            out << c;
            inSpace = false;
        }
    }

    return out.str();
}
void debugPrintPlayers(const Game &game, const string &location) {
    cout << "DEBUG [" << location << "]: Players in game: " << game.getPlayers().size() << "\n";
    for (const auto &p : game.getPlayers()) {
        cout << "  - " << p.getName() << " (active: " << p.isActive() << ")\n";
    }
}

// Checks if there are any facedown cards to flip
bool hasFaceDownCards(const Game &game) {
    for (int i = 0; i < GameParameters::BoardSize; ++i) {
        for (int j = 0; j < GameParameters::BoardSize; ++j) {
            if (i == GameParameters::CenterRow && j == GameParameters::CenterCol)
                continue;
            Board::Letter l = Board::getEnumAt<Board::Letter>(i);
            Board::Number n = Board::getEnumAt<Board::Number>(j);

            // Board::Letter l = static_cast<Board::Letter>(i);
            // Board::Number n = static_cast<Board::Number>(j);

            if (!game.isFaceUp(l, n))
                return true;
        }
    }
    return false;
}

int main() {
    cout << "MEMOARRR!\n\n";

    // Get game version from user
    string gameVersion;
    const array<string, 4> validVersions = {"base", "expert display", "expert rules", "both"};
    bool gameVersionAttempted = false;

    do {
        if (gameVersionAttempted)
            cout << "Invalid input. Please try again." << endl;
        cout << "Choose game version (base/expert display/expert rules/both): ";
        getline(cin, gameVersion);
        gameVersion = cleanInput(gameVersion);
        gameVersionAttempted = true;
    } while (find(validVersions.begin(), validVersions.end(), gameVersion) == validVersions.end());

    bool expertDisplay = (gameVersion == "expert display" || gameVersion == "both");
    bool expertRules = (gameVersion == "expert rules" || gameVersion == "both");

    // initialize card deck with expert rules before Game
    CardDeck::make_CardDeck(expertRules);

    // get number of players // may need to edit so that it continuously reprompts
    int num_players;
    string num_players_string;
    bool numPlayersAttempted = false;

    do {
        if (numPlayersAttempted)
            cout << "Invalid input. Please try again." << endl;
        cout << "Enter the number of Players [2-4]: ";
        getline(cin, num_players_string);
        num_players_string = cleanInput(num_players_string);
        numPlayersAttempted = true;
    } while (num_players_string.size() != 1 || !(num_players_string == "2" || num_players_string == "3" || num_players_string == "4"));

    num_players = stoi(num_players_string);

    // Initialize game instances to run Memoarrr
    Game game(expertDisplay, expertRules);
    Rules rules;
    RubisDeck &rubisDeck = RubisDeck::make_RubisDeck();

    vector<string> playerNames;
    string name;
    for (int i = 0; i < num_players; ++i) {
        bool playerNameAttempted = false;
        while (name.empty() || find(playerNames.begin(), playerNames.end(), name) != playerNames.end()) {
            if (playerNameAttempted && name.empty())
                cout << "Invalid input, please enter a name." << endl;
            else if (playerNameAttempted)
                cout << "Player name already exists. Please enter a new player name." << endl;
            cout << "Enter Player " << i + 1 << " name: ";
            getline(cin, name);
            name = cleanInput(name);
            playerNameAttempted = true;
        }
        playerNames.push_back(name);
        Player player(name, Board::getEnumAt<Player::Side>(i));

        game.addPlayer(player);
    }
    cout << '\n' << game; // print the starting board

    // Reveal entire board at start for debugging purposes
    cout << "\n=== DEBUG: FULL BOARD REVEAL ===\n";

    for (int i = 0; i < GameParameters::BoardSize; ++i) {
        for (int j = 0; j < GameParameters::BoardSize; ++j) {
            if (i == GameParameters::CenterRow && j == GameParameters::CenterCol)
                continue; // skip center if your game rules require it

            Board::Letter l = Board::getEnumAt<Board::Letter>(i);
            Board::Number n = Board::getEnumAt<Board::Number>(j);
            game.turnFaceUp(l, n);
        }
    }

    // Print fully revealed board
    cout << game << "\n";

    // Pause so you can inspect
    cout << "(press Enter to continue to actual game)";
    cin.get();

    // Turn everything face-down again
    for (int i = 0; i < GameParameters::BoardSize; ++i) {
        for (int j = 0; j < GameParameters::BoardSize; ++j) {
            if (i == GameParameters::CenterRow && j == GameParameters::CenterCol)
                continue;

            Board::Letter l = Board::getEnumAt<Board::Letter>(i);
            Board::Number n = Board::getEnumAt<Board::Number>(j);
            game.turnFaceDown(l, n);
        }
    }

    cout << "\n### DEBUG: END FULL BOARD REVEAL ###\n\n";

    // MAIN LOOP
    while (!rules.gameOver(game)) {
        cout << "\n-------- BEGINNING OF ROUND " << game.getRound() + 1 << " --------\n";

        game.startNewRound(); // face down all cards + activate all players + reset current/previous

        //  Temporarily reveal 3 cards directly in front of each player
        for (const Player &p : game.getPlayers()) {
            cout << "\n" << p.getName() << ", look at your 3 secret cards:\n";

            vector<pair<Board::Letter, Board::Number>> peekCards;
            Player::Side playerSide = p.getSide();
            int middlepos = GameParameters::BoardSize / 2;

            switch (playerSide) {
            case Player::Side::top: {
                Board::Letter row = Board::getEnumAt<Board::Letter>(0);
                peekCards = {{row, Board::getEnumAt<Board::Number>(middlepos - 1)},
                             {row, Board::getEnumAt<Board::Number>(middlepos)},
                             {row, Board::getEnumAt<Board::Number>(middlepos + 1)}};
                break;
            }
            case Player::Side::bottom: {
                Board::Letter row = Board::getEnumAt<Board::Letter>(GameParameters::BoardSize - 1);
                peekCards = {{row, Board::getEnumAt<Board::Number>(middlepos - 1)},
                             {row, Board::getEnumAt<Board::Number>(middlepos)},
                             {row, Board::getEnumAt<Board::Number>(middlepos + 1)}};
                break;
            }
            case Player::Side::left: {
                Board::Number col = Board::getEnumAt<Board::Number>(0);
                peekCards = {{Board::getEnumAt<Board::Letter>(middlepos - 1), col},
                             {Board::getEnumAt<Board::Letter>(middlepos), col},
                             {Board::getEnumAt<Board::Letter>(middlepos + 1), col}};
                break;
            }
            case Player::Side::right: {
                Board::Number col = Board::getEnumAt<Board::Number>(GameParameters::BoardSize - 1);
                peekCards = {{Board::getEnumAt<Board::Letter>(middlepos - 1), col},
                             {Board::getEnumAt<Board::Letter>(middlepos), col},
                             {Board::getEnumAt<Board::Letter>(middlepos + 1), col}};
                break;
            }
            }

            for (auto [l, n] : peekCards)
                game.turnFaceUp(l, n);
            cout << '\n' << game << '\n';

            cout << "(press Enter when done)...";
            string dummy;
            getline(cin, dummy);
            // cin.get();

            for (auto [l, n] : peekCards)
                game.turnFaceDown(l, n);
        }

        // PLAY ROUND
        while (!rules.roundOver(game)) {
            // DEBUG: Print player list
            cout << "\n[DEBUG] Player list at start of turn:\n";
            for (const auto &p : game.getPlayers()) {
                cout << "  " << p.getName() << " (active: " << p.isActive() << ")\n";
            }

            Player &current = game.getCurrentPlayer();

            // Skip past any inactive players
            while (!current.isActive()) {
                game.nextPlayer();
                current = game.getCurrentPlayer();
            }

            cout << "\nTurn: " << current.getName() << "\n";

            if (!hasFaceDownCards(game)) {
                cout << "No more cards to flip - you lose this turn!\n";
                current.setActive(false);
                game.nextPlayer();
                continue; // Let the while loop check roundOver
            }

            // Get valid position
            Board::Letter l;
            Board::Number n;
            string userInput;
            while (true) {
                cout << "Enter card - letter then number (ex. \"a1\" or \"B2\"): ";
                getline(cin, userInput);
                userInput = cleanInput(userInput);
                if (userInput.size() != 2 || !isalpha(userInput[0]) || !isdigit(userInput[1])) {
                    cout << "Invalid input. Please try again.\n";
                    continue;
                }
                char let = toupper(userInput[0]);
                int num = userInput[1] - '0';
                if (let < 'A' || let > 'E' || num < 1 || num > 5) {
                    cout << "Position out of range. Try again.\n";
                    continue;
                }
                l = Board::getEnumAt<Board::Letter>(let - 'A');
                n = Board::getEnumAt<Board::Number>(num - 1);
                break;
            }

            // Check if blocked by Walrus
            auto blocked = game.getBlockedPosition();
            if (blocked && l == blocked->first && n == blocked->second) {
                cout << "Blocked position - choose another!\n";
                continue;
            }

            try {
                // Try to flip the card
                if (!game.turnFaceUp(l, n)) {
                    cout << "Card already face up - you are out this round!\n";
                    current.setActive(false);
                    game.nextPlayer();
                    continue; // Let the while loop check roundOver
                }

                game.setCurrentPosition(l, n);
                game.setCurrentCard(game.getCard(l, n));
                cout << '\n' << game << '\n';

                // check for match (skip if first card)
                if (game.getPreviousCard() == nullptr) {
                    cout << "First card flipped!\n";
                    if (game.isExpertRules()) {
                        game.getCurrentCard()->applyEffect(game);
                    }
                } else if (!rules.isValid(game)) {
                    cout << "No match! " << current.getName() << " is out this round.\n";
                    current.setActive(false);
                    game.nextPlayer();
                    continue; // Let the while loop check roundOver
                } else {
                    cout << "Match!\n";
                    // Apply expert rules effects ONLY on successful match
                    if (game.isExpertRules()) {
                        game.getCurrentCard()->applyEffect(game);
                    }
                }

                // Turn progression with turtle skip handling
                if (!game.getExtraTurn()) {
                    game.nextPlayer();

                    // If Turtle card was played, skip the next ACTIVE player
                    if (game.getSkipNextPlayer()) {
                        int attempts = 0;
                        int maxAttempts = game.getPlayers().size();

                        // Find next active player
                        while (attempts < maxAttempts && !game.getCurrentPlayer().isActive()) {
                            game.nextPlayer();
                            attempts++;
                        }

                        // Skip this active player (if one exists)
                        if (attempts < maxAttempts && game.getCurrentPlayer().isActive()) {
                            game.nextPlayer();
                        }

                        game.setSkipNextPlayer(false);
                    }
                }
                game.setExtraTurn(false);

            } catch (const OutOfRange &) {
                cout << "Invalid position - you are out this round!\n";
                current.setActive(false);
                game.nextPlayer();
                continue; // Let the while loop check roundOver
            }
        }

        // Round over - give rubies to the winner
        cout << "\n-------- ROUND " << game.getRound() << " OVER --------\n";

        for (Player &p : game.getPlayers()) {
            if (p.isActive()) {
                cout << p.getName() << " wins the round!\n";

                Rubis *r = rubisDeck.getNext();
                if (!r) {
                    cout << "No more rubies!\n";
                } else {
                    p.addRubis(*r);
                    cout << p.getName() << " receives " << *r << "\n";
                }
                break;
            }
        }
        cout << "------------------------------\n";
    }

    cout << "\n#########################################################\n";
    cout << "##################### GAME OVER #########################\n";
    cout << "#########################################################\n\n";

    // Show scores sorted from most to least rubies
    vector<Player> finalStandings = game.getPlayers();
    sort(finalStandings.begin(), finalStandings.end(), [](const Player &a, const Player &b) { return a.getNRubies() > b.getNRubies(); });

    for (Player &p : finalStandings)
        p.setDisplayMode(true);

    cout << "Final scores (most to least rubies):\n";
    for (const Player &p : finalStandings) {
        cout << p;
    }

    cout << "\n-------- " << finalStandings.front().getName() << " WINS THE GAME!!! --------\n";

    return 0;
}