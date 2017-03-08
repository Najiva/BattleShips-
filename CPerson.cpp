#include "CPlayer.h"
#include "CPerson.h"
#include <cstdlib>
#include <iostream>

using namespace std;

CPerson::CPerson(bool ar, bool ap) : autoResponse(ar), autoPrepare(ap) {

}

bool CPerson::getCoord(CShip& ship) {
    switch (autoPrepare) {
        case true:
            srand(time(NULL) + 1);
            do {

                ship.coor[0] = rand() % 10;
                ship.coor[1] = rand() % 10;
            } while ((ship.coor[0] + ship.length) >= 10 || 
                    (ship.coor[1] + ship.width) >= 10 || !boatOverlap(ship));
            return true;
        case false:
            cout << "Location of the new boat? (A1-J10)" << endl;
            string vstup, tmp;
            cin >> vstup;
            // parses string to two
            ship.coor[1] = ((int) vstup[0] - 65); 
            tmp = vstup.substr(1, 2);
            ship.coor[0] = atoi(tmp.c_str()) - 1;

            if (ship.coor[0] >= 0 && ship.coor[0] <= 9 && ship.coor[1] >= 0 && ship.coor[1] <= 9
                    && (ship.coor[0] + ship.length) <= 10 && (ship.coor[1] + ship.width) <= 10 &&
                    boatOverlap(ship))
                return true;
            else {
                cout << "Wrong coordinates, try again. " << endl;
                return false;
            }
    }
}

void CPerson::prepareGame() {
    bool temp = false;
    for (int i = 1; i < 6; i++) {
        CShip boat(i);
        // only for manual preparation
        do {
            temp = getCoord(boat);
        } while (!temp);
        addBoat(boat);
        if (!autoPrepare) printmBatt();
    }
}

void CPerson::shoot(int temp[]) {
    string vstup;
    string tmp;
    bool ok;
    do {
        cout << "Its your turn, what coordinates to shoot at? (A1-J10)" << endl;
        cin >> vstup;
        // parses string to two
        temp[0] = ((int) vstup[0] - 65); 
        tmp = vstup.substr(1, 2);
        temp[1] = atoi(tmp.c_str()) - 1;
        if (temp[0] <= 9 && temp[0] >= 0 && temp[1] <= 9 && temp[1] >= 0) ok = true;
        else cout << "Wrong coordinates, please try again. (A1-J10)" << endl;
    } while (!ok);
}

bool CPerson::amIHitted(int coor[]) {
    string decision;
    char x;
    int y;
    bool ok = false;
    x = (char) (coor[0] + 65);
    y = coor[1] + 1;
    if (!autoResponse) {
        cout << "Are you hit at " << x << y << "?" << endl;
        do {
            cout << "yes/no" << endl;

            cin >> decision;
            if (decision == "yes" || decision == "no")
                ok = true;
            else cout << "Wrong choice, please try again" << endl;
        } while (!ok);

        if (decision == "yes") {
            mBatt[coor[1]][coor[0]] = 'X';
            incHits();
            return true;
        } else {
            mBatt[coor[1]][coor[0]] = '.';
            return false;
        }
    } else {
        // automatic response of the player
        if (mBatt[coor[1]][coor[0]] == 'o') {
            mBatt[coor[1]][coor[0]] = 'X';
            incHits();
            return true;
        } else if (mBatt[coor[1]][coor[0]] == 'X') {
            return true;
        } else {
            mBatt[coor[1]][coor[0]] = '.';
            return false;
        }
    }
}




