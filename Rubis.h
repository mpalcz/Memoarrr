#ifndef RUBIS_H
#define RUBIS_H

#include <iostream>


class RubisDeck;

class Rubis {
    private:
        // friend classes
        friend class RubisDeck;

        // Constructor
        Rubis(int);
        int numRubis;
    
    public:
        static int possibleNumberOfRubis[4];

        // Friend functions
        friend std::ostream& operator<<(std::ostream& os, const Rubis& obj);
};

#endif