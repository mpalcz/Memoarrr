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
#include "UserInput.h"        
#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <limits>
#include <sstream>

using namespace std;

/*
* Function that checks if there are any facedown cards left to flip in the game
*/ 
bool hasFaceDownCards(const Game& game) {
    for (int i = 0; i < GameParameters::BoardSize; ++i) {
        for (int j = 0; j < GameParameters::BoardSize; ++j) {
            if (i == GameParameters::CenterRow && j == GameParameters::CenterCol) continue;
            Board::Letter l = Board::getEnumAt<Board::Letter>(i);
            Board::Number n = Board::getEnumAt<Board::Number>(j);
            if (!game.isFaceUp(l, n)) return true;
        }
    }
    return false;
}

/*
* Main loop starting console gameplay
*/ 
int main() {
    cout << "\nWELCOME TO MEMOARRR!\n\n";

    // ------ Get game version from user ------
    string gameVersion;
    const array<string, 4> validVersions = {"base", "expert display", "expert rules", "both"};
    bool gameVersionAttempted = false;

    do {
        if (gameVersionAttempted) cout << "Invalid input. Please try again." << endl;
        cout << "Choose game version (base/expert display/expert rules/both): ";
        getline(cin, gameVersion);
        gameVersion = cleanInput(gameVersion);
        transform(gameVersion.begin(), gameVersion.end(), gameVersion.begin(), [](unsigned char c){ return tolower(c); });
        gameVersionAttempted = true;
    } while (find(validVersions.begin(), validVersions.end(), gameVersion) == validVersions.end());

    bool expertDisplay = (gameVersion == "expert display" || gameVersion == "both");
    bool expertRules = (gameVersion == "expert rules" || gameVersion == "both");
    // ------------------------------------------

    // ------ Get number of players from user ------
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
    // ---------------------------------------------

    // Initialize game and related instances
    Game game(expertDisplay, expertRules);
    Rules rules;
    RubisDeck& rubisDeck = RubisDeck::make_RubisDeck();

    // ------ Get names of players from user ------
    vector<string> playerNames(num_players);
    string name;
    for (int i = 0; i < num_players; ++i) {
        bool playerNameAttempted = false;
        do {
            if (playerNameAttempted && name.empty()) cout << "Invalid input, please enter a non-empty name." << endl;
            else if (playerNameAttempted) cout << "Player name already exists. Please enter a new player name." << endl;
            cout << "Enter Player " << i+1 << " name: ";
            getline(cin, name);
            name = capitalizeName(cleanInput(name));
            playerNameAttempted = true;
        } while (name.empty() || find(playerNames.begin(), playerNames.end(), name) != playerNames.end());
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

            // Skip inactive players
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

            auto [l, n] = getUserInputCard(game);

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

                cout << '\n' << game << '\n';
                
                // Check match
                if (!rules.isValid(game)) {
                    cout << "No match! " << currentPlayer.getName() << " is out this round.\n";
                    currentPlayer.setActive(false);
                    game.nextPlayer();
                    continue;
                } else {
                    if (game.getPreviousCard() == nullptr) cout << "First card flipped!\n";
                    if (game.isExpertRules()) {
                        string resultEffect = game.getCurrentCard()->applyEffect(game);
                        cout << '\n' << game << '\n' << resultEffect << endl;
                    }
                }
                
                if (!game.getExtraTurn()) game.nextPlayer();
                game.setExtraTurn(false); // Reset after potential extra turn (if flipped a crab)

            } catch (const OutOfRange&) {                    
                cout << "Invalid position - you are out this round!\n";
                currentPlayer.setActive(false);
                game.nextPlayer();
            }
        }

        // Round over - give rubies to the winner
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

    // Game over - final results
    
    cout << "\n#########################################################\n";
    cout << "##################### GAME OVER #########################\n";
    cout << "#########################################################\n\n";

    // Show scores sorted from most to least rubies
    vector<Player> finalStandings = game.getPlayers();        
    sort(finalStandings.begin(), finalStandings.end(),
         [](const Player& a, const Player& b) { return a.getNRubies() > b.getNRubies(); });

    for (Player& p : finalStandings) p.setDisplayMode(true);

    cout << "Final scores (most to least rubies):\n";
    for (const Player& p : finalStandings) {
        cout << p;
    }

    cout << "\n-------- " << finalStandings.front().getName() << " WINS THE GAME!!! --------\n";

    return 0;
}