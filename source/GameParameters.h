#ifndef GAMEPARAMETERS_H
#define GAMEPARAMETERS_H

#include <array>
#include <tuple>

namespace GameParameters {

    // Board dimension parameters
    inline constexpr int BoardSize = 5;
    inline constexpr int CenterRow = BoardSize / 2; // 2
    inline constexpr int CenterCol = BoardSize / 2; // 2
    inline constexpr std::tuple<int, int> CenterPosition(CenterRow, CenterCol);
    inline constexpr int BoardPadding = 3; // Spacing between each row of cards and between the Margins

    // Game play parameters
    inline constexpr int NumberOfRounds = 7;
    inline constexpr int PeekCardsPerPlayer = 3;

    // Card parameters
    inline constexpr int NumRowsCard = 3;
    inline constexpr int NumAnimals = 5;
    inline constexpr int NumBackgrounds = 5;
    inline constexpr int TotalCards = NumAnimals * NumBackgrounds;     // 25
    inline constexpr int CardsOnBoard = TotalCards - 1;                  // 24

    // Rubis parameters
    inline constexpr std::array<int, 5> RubisDistribution = {0, 3, 2, 1, 1}; // index = rubis value

}

#endif