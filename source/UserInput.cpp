#include "UserInput.h"

using namespace std;

/*
* Function to clean up console user input, getting rid of leading and trailing whitespace 
* and replacing multiple spaces with single spaces in between words
*/ 
string cleanInput(const string& input) {
    string s = input;

    // Trim any leading spaces
    size_t start = s.find_first_not_of(' ');
    if (start == string::npos) // string was all spaces
        return ""; 
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

/*
* Helper function to get user input for a card on the board
*/ 
pair<Board::Letter, Board::Number> getUserInputCard(Game& game) {
    string userInput;
    bool userInputInvalid = true;
    Board::Letter l;
    Board::Number n;
    while (userInputInvalid) {
        cout << "Enter card - letter then number (ex. \"a1\" or \"B2\"): ";
        getline(cin, userInput);
        userInput = cleanInput(userInput);
        if (userInput.size() !=2 || !(isalpha(userInput[0]) && isdigit(userInput[1]))) {
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

            if (game.isCenterCard(l, n)) {
                cout << "Cannot choose empty center slot - choose another!\n";
                continue;
            }

            auto blocked = game.getBlockedPosition();
            if (blocked && l == blocked->first && n == blocked->second) {
                cout << "Blocked position - choose another!\n";
                continue;
            }

        } catch (const out_of_range& e) {
            cout << "Input must be a number and letter in valid board range: Letter = [A-";
            cout << static_cast<char>('A' + GameParameters::BoardSize - 1) << "], Number = [1-";
            cout << GameParameters::BoardSize << "]. Please try again." << endl;
            continue;
        }
        userInputInvalid = false;
    }
    return {l, n};

}

/*
* Function to capitalize player name
*/

string capitalizeName(const string& name) {
    ostringstream capitalizedName;
    bool firstCharacterOfWord = true;

    for (char c : name) {
        if (firstCharacterOfWord) {
            capitalizedName << static_cast<char>(toupper(static_cast<unsigned char>(c)));
            firstCharacterOfWord = false;
        } else {
            if (c == ' ') firstCharacterOfWord = true;
            capitalizedName << c;
        }
    }

    return capitalizedName.str();
}