#include "CShip.h"
#include <cstdlib>
#include <iostream>

using namespace std;

CShip::CShip(int typ) {
    coor[0] = -1;
    coor[1] = -1;
    switch (typ) {
        case 1: name = "patrol boat";
            length = 2;
            width = 1;
            break;
        case 2: name = "submarine";
            length = 3;
            width = 1;
            break;
        case 3: name = "tanker";
            length = 4;
            width = 1;
            break;
        case 4: name = "destroyer";
            length = 2;
            width = 2;
            break;
        case 5: name = "aircraft carrier";
            length = 5;
            width = 1;
    }
}

