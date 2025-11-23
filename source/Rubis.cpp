#include "Rubis.h"
#include <stdexcept>
using namespace std;

// constructor
Rubis::Rubis(int val) : numRubis(val) {
    // should never happen since we will handle before to allow retries but just in case
    if (val > 4 || val < 1) {
        throw invalid_argument("Rubi value must be between 1 and 4");
    }
}

// Operator<< definition
ostream &operator<<(ostream &os, const Rubis &obj) {
    os << obj.numRubis << " Rubis";
    return os;
}