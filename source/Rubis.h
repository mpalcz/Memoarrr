// Rubis.h (fixed plural)
#ifndef RUBIS_H
#define RUBIS_H

#include <iostream>
#include <stdexcept>
#include "GameParameters.h"

class RubisDeck;

class Rubis {
  friend class RubisDeck;

private:
    int numRubies;

    Rubis(int val) {
      if (val == 0 || val >= static_cast<int>(GameParameters::RubisDistribution.size())) throw std::invalid_argument("Rubies value must be between 1 and 4");
      numRubies = val;
    }

public:
    operator int() const { return numRubies; }
    friend std::ostream& operator<<(std::ostream& os, const Rubis& r) {
        os << r.numRubies << " rub" << (r.numRubies == 1 ? "y" : "ies");
        return os;
    }
};

#endif