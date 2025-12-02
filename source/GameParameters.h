#ifndef GAMEPARAMETERS_H
#define GAMEPARAMETERS_H

#include <unordered_map>
#include <tuple>
#include <cmath>

namespace Game {
    enum class Side {top, bottom, left, right};
    enum class Status {active, inactive};
    inline int numOneRubis = 3;
    inline int numTwoRubis = 2;
    inline int numThreeRubis = 1;
    inline int numFourRubis = 1;
    inline std::unordered_map<int, int> rubisValues = {
        {1, numOneRubis},
        {2, numTwoRubis},
        {3, numThreeRubis},
        {4, numFourRubis}
    };
    const int boardSize = 5;
    std::tuple<int, int> emptyCardPosition(std::floor(boardSize/2), std::floor(boardSize/2));
    
}

template<typename Enum>
constexpr int enumCount() {
    return static_cast<int>(Enum::COUNT);
}

#endif