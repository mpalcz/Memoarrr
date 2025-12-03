// main.cpp: Entry point for the Memoarrr game.
#include "Board.h"
#include "Card.h"
#include "CardDeck.h"
#include "Game.h"
#include "Player.h"
#include "Rubis.h"
#include "RubisDeck.h"
#include "Rules.h"
#include "Exceptions.h"        
#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <limits>
#include <sstream>

using namespace std;

// Function to clean up name from user input, getting rid of leading and trailing whitespace and replacing multiple spaces with one in between names
string cleanInput(const string& input) {
    string s = input;

    // 1. Trim leading spaces
    size_t start = s.find_first_not_of(' ');
    if (start == string::npos)
        return ""; // string was all spaces
    s = s.substr(start);

    // 2. Trim trailing spaces
    size_t end = s.find_last_not_of(' ');
    s = s.substr(0, end + 1);

    // 3. Replace multiple internal spaces with single spaces
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


bool hasFaceDownCards(const Game& game) {
    for (int i = 0; i < GameParameters::BoardSize; ++i) {
        for (int j = 0; j < GameParameters::BoardSize; ++j) {
            if (i == GameParameters::CenterRow && j == GameParameters::CenterCol) continue;
            Board::Letter l = static_cast<Board::Letter>(i);
            Board::Number n = static_cast<Board::Number>(j);
            if (!game.isFaceUp(l, n)) return true;
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
        if (gameVersionAttempted) cout << "Invalid input. Please try again." << endl;
        cout << "Choose game version (base/expert display/expert rules/both): ";
        getline(cin, gameVersion);
        gameVersion = cleanInput(gameVersion);
        gameVersionAttempted = true;
    } while (find(validVersions.begin(), validVersions.end(), gameVersion) == validVersions.end());

    bool expertDisplay = (gameVersion == "expert display" || gameVersion == "both");
    bool expertRules = (gameVersion == "expert rules" || gameVersion == "both");

    // get number of players /// may need to edit so that it continuously reprompts 
    int num_players;
    cout << "Enter the number of Players [2-4]: ";
    cin >> num_players;
    while (num_players < 2 || num_players > 4) {
        cout << "Invalid, please enter 2-4 players: ";
        cin >> num_players;
    }

    // clear leftover newline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Initialize game instances to run Memoarrr
    Game game(expertDisplay, expertRules);
    Rules rules;
    RubisDeck& rubisDeck = RubisDeck::make_RubisDeck();

    vector<string> playerNames;
    string name;
    for (int i = 0; i < num_players; ++i) {
        bool playerNameAttempted = false;
        while (name.empty() || find(playerNames.begin(), playerNames.end(), name) != playerNames.end()) {
            if (playerNameAttempted && name.empty()) cout << "Invalid input, please enter a name." << endl;
            else if (playerNameAttempted) cout << "Player name already exists. Please enter a new player name." << endl;
            cout << "Enter Player " << i + 1 << " name: ";
            getline(cin, name);
            name = cleanInput(name);
            playerNameAttempted = true;
        }
        /*
        cout << "Enter Player " << i + 1 << " name: ";
        getline(cin, name);
        string cleanPlayerName = cleanInput(rawName);
        */

        //Player player(name, static_cast<Player::Side>(i));
        playerNames.push_back(name);
        Player player(name, Board::getEnumAt<Player::Side>(i));

        game.addPlayer(player);
    }

    cout << '\n' << game << endl; // print the starting board

    // MAIN LOOP
    while (!rules.gameOver(game)) {
        cout << "-------- BEGINNING OF ROUND " << game.getRound() + 1 << " --------\n";

        game.startNewRound(); // face down all cards + activate all players + reset current/previous

        //  Temporarily reveal 3 cards directly in front of each player
        for (const Player& p : game.getPlayers()) {                    
            cout << "\n" << p.getName() << ", look at your 3 secret cards:\n";

            vector<pair<Board::Letter, Board::Number>> peekCards;
            Player::Side playerSide = p.getSide();
            int middlepos = GameParameters::BoardSize / 2;

            switch (playerSide) {
                case Player::Side::top: {
                    Board::Letter row = Board::getEnumAt<Board::Letter>(0);
                    peekCards = {
                        {row, Board::getEnumAt<Board::Number>(middlepos-1)}, 
                        {row, Board::getEnumAt<Board::Number>(middlepos)}, 
                        {row, Board::getEnumAt<Board::Number>(middlepos+1)}
                    };
                    break;
                } 
                case Player::Side::bottom: {
                    Board::Letter row = Board::getEnumAt<Board::Letter>(GameParameters::BoardSize - 1);
                    peekCards = {
                        {row, Board::getEnumAt<Board::Number>(middlepos-1)}, 
                        {row, Board::getEnumAt<Board::Number>(middlepos)}, 
                        {row, Board::getEnumAt<Board::Number>(middlepos+1)}
                    };
                    break;
                } 
                case Player::Side::left: {
                    Board::Number col = Board::getEnumAt<Board::Number>(0);
                    peekCards = {
                        {Board::getEnumAt<Board::Letter>(middlepos-1), col}, 
                        {Board::getEnumAt<Board::Letter>(middlepos), col}, 
                        {Board::getEnumAt<Board::Letter>(middlepos+1), col}
                    };
                    break;
                }
                case Player::Side::right: {
                    Board::Number col = Board::getEnumAt<Board::Number>(GameParameters::BoardSize - 1);
                    peekCards = {
                        {Board::getEnumAt<Board::Letter>(middlepos-1), col}, 
                        {Board::getEnumAt<Board::Letter>(middlepos), col}, 
                        {Board::getEnumAt<Board::Letter>(middlepos+1), col}
                    };
                    break;
                }
            }
            
            /*
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
            */

            for (auto [l, n] : peekCards) game.turnFaceUp(l, n);
            cout << '\n' << game << '\n';

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "(press Enter when done)...";
            cin.get();


            /*
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();   // Wait exactly once for Enter
            */

            for (auto [l, n] : peekCards) game.turnFaceDown(l, n);
        }

        // Round play
        while (!rules.roundOver(game)) {
            Player& currentPlayer = game.getCurrentPlayer();

            // skip inactive players
            while (!currentPlayer.isActive()) {
                game.nextPlayer();
                currentPlayer = game.getCurrentPlayer();
            }

            cout << "\nTurn: " << currentPlayer.getName() << "\n";
            if (!hasFaceDownCards(game)) {
                cout << "No more cards to flip - you lose this turn!\n";
                currentPlayer.setActive(false);
                game.nextPlayer();
                continue;
            }

            cout << "Enter card (letter then number): ";

            char card_letter;
            int card_number;
            cin >> card_letter >> card_number;

            card_letter = toupper(card_letter);
            Board::Letter l = static_cast<Board::Letter>(card_letter - 'A');          
            Board::Number n = static_cast<Board::Number>(card_number - 1);            

            auto blocked = game.getBlockedPosition();
            if (blocked && l == blocked->first && n == blocked->second) {
                cout << "Blocked position - choose another!\n";
                continue;
            }

            try {
                // Flip the card
                if (!game.turnFaceUp(l, n)) {
                    cout << "Card already face up - you are out this round!\n";
                    currentPlayer.setActive(false);
                    game.nextPlayer();
                    continue;
                }

                game.setCurrentPosition(l, n);
                game.setCurrentCard(game.getCard(l, n));

                cout << game << "\n";

                // Check match
                if (game.getPreviousCard() == nullptr) {
                    cout << "First card flipped!\n";
                } else if (!rules.isValid(game)) {
                    cout << "No match! " << currentPlayer.getName() << " is out this round.\n";
                    game.turnFaceDown(l, n);
                    currentPlayer.setActive(false);
                } else {
                    cout << "Match!\n";
                    if (game.isExpertRules()) {
                        game.getCurrentCard()->applyEffect(game);
                    }
                }

                if (!game.getExtraTurn()) game.nextPlayer();
                game.setExtraTurn(false); // Reset after potential extra turn

            } catch (const OutOfRange&) {                    
                cout << "Invalid position - you are out this round!\n";
                currentPlayer.setActive(false);
                game.nextPlayer();
            }
        }

        // === Round over - give rubies to the winner ===
        cout << "\n################ ROUND " << game.getRound() << " OVER ################\n";

        for (Player& p : game.getPlayers()) {                    
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
    vector<Player> finalStandings = game.getPlayers();        
    sort(finalStandings.begin(), finalStandings.end(),
         [](const Player& a, const Player& b) { return a.getNRubies() < b.getNRubies(); });

    for (Player& p : finalStandings) p.setDisplayMode(true);

    cout << "Final scores (least to most rubies):\n";
    for (const Player& p : finalStandings) {
        cout << p;
    }

    cout << "\n*** " << finalStandings.back().getName() << " WINS THE GAME!!! ***\n";

    return 0;
}