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
#include <array>
#include <string>

using namespace std;

// Function to clean up name from user input, getting rid of leading and trailing whitespace
// and replacing multiple spaces with one in between names
string cleanInput(const string& input) {
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

// Checks if there are any facedown cards to flip (ignoring a Walrus-blocked card)
bool hasFaceDownCards(const Game& game) {
    // walrus might block one card, so we dont count that one as a valid choice
    auto blocked = game.getBlockedPosition();

    for (int i = 0; i < GameParameters::BoardSize; ++i) {
        for (int j = 0; j < GameParameters::BoardSize; ++j) {
            if (i == GameParameters::CenterRow && j == GameParameters::CenterCol) continue;

            Board::Letter l = Board::getEnumAt<Board::Letter>(i);
            Board::Number n = Board::getEnumAt<Board::Number>(j);

            // if walrus blocked this spot, skip it (player cant pick it anyway)
            if (blocked && l == blocked->first && n == blocked->second) {
                continue;
            }

            if (!game.isFaceUp(l, n)) return true;
        }
    }
    return false;
}

int main() {
    cout << "WELCOME TO MEMOARRR!\n\n";

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

    // Create card deck first (must exist before Board constructor in Game)
    CardDeck::make_CardDeck(expertRules);

    // Get number of players from user 
    int num_players;
    string num_players_string;
    bool numPlayersAttempted = false;

    do {
        if (numPlayersAttempted) cout << "Invalid input. Please try again." << endl;
        cout << "Enter the number of Players [2-4]: ";
        getline(cin, num_players_string);
        num_players_string = cleanInput(num_players_string);
        numPlayersAttempted = true;
    } while (num_players_string.size() != 1 || !(num_players_string == "2" || num_players_string == "3" || num_players_string == "4"));

    num_players = stoi(num_players_string);

    // Initialize game instances to run Memoarrr
    Game game(expertDisplay, expertRules);
    Rules rules;
    RubisDeck& rubisDeck = RubisDeck::make_RubisDeck();

    vector<string> playerNames;
    string name;
    for (int i = 0; i < num_players; ++i) {
        bool playerNameAttempted = false;
        name.clear();
        while (name.empty() || find(playerNames.begin(), playerNames.end(), name) != playerNames.end()) {
            if (playerNameAttempted && name.empty()) cout << "Invalid input, please enter a name." << endl;
            else if (playerNameAttempted) cout << "Player name already exists. Please enter a new player name." << endl;
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

    // MAIN LOOP
    while (!rules.gameOver(game)) {
        cout << "\n-------- BEGINNING OF ROUND " << game.getRound() + 1 << " --------\n";

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

            for (auto [l, n] : peekCards) game.turnFaceUp(l, n);
            cout << '\n' << game << '\n';

            cout << "(press Enter when done)...";
            string dummy;
            getline(cin, dummy);

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

            // if there is nothing left to flip (except maybe a blocked card), player is just out this turn
            if (!hasFaceDownCards(game)) {
                cout << "No more cards to flip - you lose this turn!\n";
                currentPlayer.setActive(false);
                // walrus still moves along even if they didnt flip anything
                game.advanceWalrusEffect();
                game.nextPlayer();
                continue;
            }

            string userInput;
            bool userInputInvalid = true;
            Board::Letter l;
            Board::Number n;
            while (userInputInvalid) {
                cout << "Enter card - letter then number (ex. \"a1\" or \"B2\"): ";
                getline(cin, userInput);
                userInput = cleanInput(userInput);
                if (userInput.size() != 2 || !(isalpha(userInput[0]) && isdigit(userInput[1]))) {
                    cout << "Invalid input. Please try again." << endl; 
                    continue;
                }
                try {
                    char card_letter = toupper(userInput[0]);
                    int letter_index = card_letter - 'A';

                    int card_number = userInput[1] - '0';
                    int number_index = card_number - 1; 

                    l = Board::getEnumAt<Board::Letter>(letter_index);
                    n = Board::getEnumAt<Board::Number>(number_index);
                } catch (const out_of_range& e) {
                    cout << "Input must be a number and letter in valid board range: Letter = [A-";
                    cout << static_cast<char>('A' + GameParameters::BoardSize - 1) << "], Number = [1-";
                    cout << GameParameters::BoardSize << "]. Please try again." << endl;
                    continue;
                }
                userInputInvalid = false;
            }

            // Check if blocked by Walrus
            auto blocked = game.getBlockedPosition();
            if (blocked && l == blocked->first && n == blocked->second) {
                cout << "Blocked position - choose another!\n";
                // dont advance walrus here, this is still same turn
                continue;
            }

            try {
                // Flip the card
                if (!game.turnFaceUp(l, n)) {
                    cout << "Card already face up - you are out this round!\n";
                    currentPlayer.setActive(false);
                    // this was still a "turn" for walrus purposes
                    game.advanceWalrusEffect();
                    game.nextPlayer();
                    continue;
                }

                game.setCurrentPosition(l, n);
                game.setCurrentCard(game.getCard(l, n));

                cout << '\n' << game << '\n';

                // Check match
                if (game.getPreviousCard() == nullptr) {
                    cout << "First card flipped!\n";
                } else if (!rules.isValid(game)) {
                    cout << "No match! " << currentPlayer.getName() << " is out this round.\n";
                    game.turnFaceDown(l, n);
                    currentPlayer.setActive(false);
                } else {
                    cout << "Match!\n";
                    // apply expert effects only after a succesful match
                    if (game.isExpertRules()) {
                        game.getCurrentCard()->applyEffect(game);
                    }
                }

                // walrus effect advances once at the end of each player's turn
                game.advanceWalrusEffect();

                if (!game.getExtraTurn()) game.nextPlayer();
                game.setExtraTurn(false); // Reset after potential extra turn

            } catch (const OutOfRange&) {                    
                cout << "Invalid position - you are out this round!\n";
                currentPlayer.setActive(false);
                // still counts as a turn for walrus
                game.advanceWalrusEffect();
                game.nextPlayer();
            }
        }

        // Round over - give rubies to the winner ===
        cout << "\n-------- ROUND " << game.getRound() << " OVER --------\n";

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
        cout << "------------------------------\n";
    }

    // === Game over - final results ===
    cout << "\n#########################################################\n";
    cout << "##################### GAME OVER #########################\n";
    cout << "#########################################################\n\n";

    // Show scores sorted from most to least rubies
    // (we keep this as copy, only for printing at the end)
    vector<Player> finalStandings = game.getPlayers();
    sort(finalStandings.begin(), finalStandings.end(),
         [](const Player& a, const Player& b) { return a.getNRubies() > b.getNRubies(); });

    for (Player& p : finalStandings) p.setDisplayMode(true);

    cout << "Final scores (most to least rubies):\n";
    for (const Player& p : finalStandings) {
        cout << p;
    }

    if (!finalStandings.empty()) {
        cout << "\n-------- " << finalStandings.front().getName() << " WINS THE GAME!!! --------\n";
    }

    return 0;
}