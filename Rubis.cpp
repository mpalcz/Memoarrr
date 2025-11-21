#include "Rubis.h"
using namespace std;

int Rubis::possibleNumberOfRubis[4] = {1, 2, 3, 4};

// Operator<< definition
ostream& operator<<(ostream& os, const Rubis& obj) {
    os << obj.numRubis;
    return os;
}