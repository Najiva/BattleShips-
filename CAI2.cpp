#include "CAI2.h"
#include "CPlayer.h"
#include <cstdlib>
#include <iostream>
#include <stack>

CAI2::CAI2() {
}

void CAI2::shoot(int temp[]) {
    if (zas.empty()) { // kdyz je zasobnik prazdny striela nahodne
        srand(time(NULL));
        do {
            temp[0] = rand() % 10;
            temp[1] = rand() % 10;
        } while (this->eBatt[temp[1]][temp[0]] == 'X' || this->eBatt[temp[1]][temp[0]] == '.');
    } else { // ako nieje prazny striela podla zasobniku
        std::vector<int> vect;
        vect = zas.top();
        temp[0] = vect[0];
        temp[1] = vect[1];
        zas.pop();
    }


}

void CAI2::markMyShot(int coor[], bool hit) {
    if (hit == true) {
        eBatt[coor[1]][coor[0]] = 'X';
        std::vector<int> temp;
        if ((coor[1]-1) >= 0 && eBatt[(coor[1]-1)][coor[0]]!='X' && 
                eBatt[(coor[1]-1)][coor[0]]!='.') {
            temp.push_back(coor[0]);
            temp.push_back(coor[1]-1);
            zas.push(temp);
            temp.clear();
        }
        if ((coor[1]+1) <= 9 && eBatt[(coor[1]+1)][coor[0]]!='X' && 
                eBatt[(coor[1]+1)][coor[0]]!='.') {
            temp.push_back(coor[0]);
            temp.push_back(coor[1]+1);
            zas.push(temp);
            temp.clear();
        }
        if ((coor[0]-1) >= 0 && eBatt[coor[1]][(coor[0]-1)]!='X' && 
                eBatt[coor[1]][(coor[0]-1)]!='.') {
            temp.push_back(coor[0]-1);
            temp.push_back(coor[1]);
            zas.push(temp);
            temp.clear();
        }
    } else {
        eBatt[coor[1]][coor[0]] = '.';
    }
}

