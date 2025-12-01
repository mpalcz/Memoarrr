#include "Rubis.h"
#include <stdexcept>
using namespace std;

// constructor
Rubis::Rubis(int val) {
    // should never happen since we will handle before to allow retries but just in case
    if (val > 4 || val < 1) {
        throw invalid_argument("Rubis value must be between 1 and 4");
    }
    numRubis = val;
}

// Operator<< definition
ostream &operator<<(ostream &os, const Rubis &obj) {
    os << obj.numRubis << (obj.numRubis > 1 ? " rubies" : " ruby");
    return os;
}