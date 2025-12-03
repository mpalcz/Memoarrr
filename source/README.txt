Memoarrr! - CSI2372A Fall 2025 Project
=====================================

Full implementation of the Memoarrr! memory card game (base + expert display + expert rules)
using modern C++17, polymorphism for expert card effects, singleton decks, and clean separation
of concerns as required by the specification.

Features
--------
- Base game fully functional
- Expert display mode (only face-up cards shown in a row)
- Expert rules mode with polymorphic card effects (Crab, Penguin, Octopus, Turtle, Walrus)
- All required classes with exact public interfaces
- Proper memory management, const-correctness, RAII

Files
-----
main.cpp            - game loop and input handling
Game.h / Game.cpp   - central game state
Board.h / Board.cpp - 5×5 board management and display
Card.h / Card.cpp   - base card with printing
Behaviours.h        - polymorphic expert card effects
CardDeck.h / CardDeck.cpp - singleton card deck (supports expert cards)
RubisDeck.h / RubisDeck.cpp - singleton rubis deck
Rubis.h             - rubis reward class
Player.h / Player.cpp - player information and status
Rules.h / Rules.cpp - game rule validation
DeckFactory.h       - template base for decks
GameParameters.h    - all constants
Exceptions.h        - custom exceptions

Requirements to compile and run code:
ADDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD

Compilation (Linux/macOS/Windows g++)
------------------------------------
g++ -std=c++17 -Wall -Wextra -pedantic *.cpp -o memoarrr.exe

Run
---
Windows:  .\memoarrr.exe
Linux/macOS: ./memoarrr.exe

Project Contributors (2):

Student Name: Megan Palczak
Student Number: 300301072

Student Name: Akash Prasad
Student Number: 300290405