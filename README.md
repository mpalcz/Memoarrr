Memoarrr!
=====================================
Full implementation of the Memoarrr! memory card game (base + expert display + expert rules additional functionality)
using modern C++17 features, polymorphism for expert card effects, singleton decks, and template functions for
reusibility and code maintainability.

Requirements (to run):
---------------------
    • C++17-compliant compiler (g++ 8+, clang++ 6+, MSVC 2019+, Apple clang 11+)
    • No external libraries
    • Works on Windows, Linux, macOS
    • Runs in any terminal

Features
--------
- Base game fully functional
- Expert display mode (only face-up cards shown in a row)
- Expert rules mode with additional card side-effects depending
    on the animal on the flipped card
- All required classes with exact public interfaces
- Proper memory management, const-correctness, RAII

Base Game
---------
The base game is a console adaptation of the Memoarrr! memory card game for 2-4 players. It uses 24 cards (out of 25 possible combinations) 
arranged in a 5x5 grid with the center position empty. Cards combine one of five animals (Crab, Penguin, Octopus, Turtle, Walrus) with one 
of five background colors (Red, Green, Purple, Blue, Yellow), represented by uppercase letters for animals and lowercase for colors 
(e.g., "yWy" for Walrus on Yellow).

Unrevealed cards show as "zzz". The board is displayed as a 19x19 character grid with row letters (A-E) and column numbers (1-5).

Gameplay:
- Players start by secretly peeking at the three cards in front of their respecitve side (top, bottom, left, right).
- Turns involve flipping a face-down card that must match the previous card's animal or color.
- Mismatch eliminates the player from the round.
- Last player standing wins 1-4 rubies (randomly drawn from a deck with distribution: 3x1, 2x2, 1x3, 1x4).
- If no face-down cards remain, active players lose turns until one remains.
- After a round, all cards are turned face-down (but positions remain unchanged).
- Game ends after 7 rounds; player with most rubies wins.

Expert Display Mode
-------------------
This mode follows base rules but replaces the full grid display with a compact row of only face-up cards, each shown below its original position 
(e.g., "A1 D1 B4 D3"). Useful for advanced play focusing on revealed information without the full board visual.

Example output:
```
yyy yyy bbb bbb
yWy yPy bPb bTb
yyy yyy bbb bbb
A1  D1  B4  D3
```

Expert Rules Mode
-----------------
This mode adds special effects when cards are turned over (can combine with expert display):
- **Octopus**: Swap position with an adjacent card (same row/column, 4-neighbors; adjacent can be face-up/down).
- **Penguin**: Turn a face-up card face-down (not the current one; no effect if first card).
- **Walrus**: Block a face-down card for the next player (they must choose another).
- **Crab**: Immediately flip another card (lose round if it mismatches).
- **Turtle**: Skip the next player's turn.

Effects trigger polymorphically via virtual `applyEffect` on Card subclasses.

Files
-----
main.cpp - game loop and input handling
Game.h / Game.cpp - central game state
Board.h / Board.cpp - 5×5 board management and display
Card.h / Card.cpp - base card with printing
Behaviours.h - polymorphic expert card effects
CardDeck.h / CardDeck.cpp - singleton card deck (supports expert cards)
RubisDeck.h / RubisDeck.cpp - singleton rubis deck
Rubis.h - rubis reward class
Player.h / Player.cpp - player information and status
Rules.h / Rules.cpp - game rule validation
DeckFactory.h - template base for decks
GameParameters.h - all constants
Exceptions.h - custom exceptions
UserInput.h / UserInput.cpp - utility functions for cleaning and handling user input (e.g., card selection, name capitalization)

Compilation (command):
---------------------
Note: -Wall -Wextra -pedantic are optional flags for compilation
1. (Windows g++):
g++ -std=c++17 -Wall -Wextra -pedantic *.cpp -o memoarrr.exe
2. (macOs/Linux)
g++ -std=c++17 -Wall -Wextra -pedantic *.cpp -o memoarrr

Run (command):
-------------
Windows: .\memoarrr.exe
Linux/macOS: ./memoarrr.exe

Project Contributors (2):
1. Megan Palczak
2. Akash Prasad