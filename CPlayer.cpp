#include "CPlayer.h"
#include "CShip.h"
#include <time.h>
#include <cstdlib>
#include <iostream>


using namespace std;

CPlayer::CPlayer() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            mBatt[i][j] = '~';
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            eBatt[i][j] = '~';
        }
    }

    n_hits = 0;
}

void CPlayer::printmBatt() const {

    cout << "MY BATTLEFIELD:          " << "ENEMY BATTLEFIELD:       " << endl;
    cout << "----------------------   " << "----------------------   " << endl;

    cout << "   ";
    for (int i = 0; i < 10; i++)
        cout << (char) (i + 65) << " ";
    cout << "     ";
    for (int i = 0; i < 10; i++)
        cout << (char) (i + 65) << " ";
    cout << endl;

    for (int i = 0; i < 10; i++) {
        cout << (i + 1) << ":";
        for (int j = 0; j < 10; j++) {
            if (i != 9 || j != 0) cout << " " << mBatt[i][j];
            else cout << mBatt[i][j];

        }
        cout << "   " << (i + 1) << ":";
        for (int j = 0; j < 10; j++) {
            if (i != 9) cout << " " << eBatt[i][j];
            else cout << eBatt[i][j] << " ";

        }

        cout << endl;
    }
}

void CPlayer::addBoat(CShip & ship) {
    if (ship.name == "patrol boat") {
        mBatt[ship.coor[0] + 1][ship.coor[1]] = 'o';
        mBatt[ship.coor[0]][ship.coor[1]] = 'o';
    }
    if (ship.name == "submarine") {
        mBatt[ship.coor[0] + 2][ship.coor[1]] = 'o';
        mBatt[ship.coor[0] + 1][ship.coor[1]] = 'o';
        mBatt[ship.coor[0]][ship.coor[1]] = 'o';
    }
    if (ship.name == "tanker") {
        mBatt[ship.coor[0] + 3][ship.coor[1]] = 'o';
        mBatt[ship.coor[0] + 2][ship.coor[1]] = 'o';
        mBatt[ship.coor[0] + 1][ship.coor[1]] = 'o';
        mBatt[ship.coor[0]][ship.coor[1]] = 'o';
    }
    if (ship.name == "destroyer") {
        mBatt[ship.coor[0]][ship.coor[1] + 1] = 'o';
        mBatt[ship.coor[0] + 1][ship.coor[1]] = 'o';
        mBatt[ship.coor[0]][ship.coor[1]] = 'o';
    }
    if (ship.name == "aircraft carrier") {
        mBatt[ship.coor[0] + 4][ship.coor[1]] = 'o';
        mBatt[ship.coor[0] + 3][ship.coor[1]] = 'o';
        mBatt[ship.coor[0] + 2][ship.coor[1]] = 'o';
        mBatt[ship.coor[0] + 1][ship.coor[1]] = 'o';
        mBatt[ship.coor[0]][ship.coor[1]] = 'o';
    }

}

bool CPlayer::boatOverlap(CShip & ship) const {
    if (ship.name == "patrol boat") {
        if (mBatt[ship.coor[0] + 1][ship.coor[1]] == 'o' ||
                mBatt[ship.coor[0]][ship.coor[1]] == 'o')return false;
    }
    if (ship.name == "submarine") {
        if (mBatt[ship.coor[0] + 2][ship.coor[1]] == 'o' ||
                mBatt[ship.coor[0] + 1][ship.coor[1]] == 'o' ||
                mBatt[ship.coor[0]][ship.coor[1]] == 'o') return false;
    }
    if (ship.name == "tanker") {
        if (mBatt[ship.coor[0] + 3][ship.coor[1]] == 'o' ||
                mBatt[ship.coor[0] + 2][ship.coor[1]] == 'o' ||
                mBatt[ship.coor[0] + 1][ship.coor[1]] == 'o' ||
                mBatt[ship.coor[0]][ship.coor[1]] == 'o') return false;
    }
    if (ship.name == "destroyer") {
        if (mBatt[ship.coor[0]][ship.coor[1] + 1] == 'o' ||
                mBatt[ship.coor[0] + 1][ship.coor[1]] == 'o' ||
                mBatt[ship.coor[0]][ship.coor[1]] == 'o') return false;
    }
    if (ship.name == "aircraft carrier") {
        if (mBatt[ship.coor[0] + 4][ship.coor[1]] == 'o' ||
                mBatt[ship.coor[0] + 3][ship.coor[1]] == 'o' ||
                mBatt[ship.coor[0] + 2][ship.coor[1]] == 'o' ||
                mBatt[ship.coor[0] + 1][ship.coor[1]] == 'o' ||
                mBatt[ship.coor[0]][ship.coor[1]] == 'o') return false;
    }
    return true;

}

bool CPlayer::amIHitted(int coor[]) {
    if (mBatt[coor[1]][coor[0]] == 'o') {
        mBatt[coor[1]][coor[0]] = 'X'; // hit
        n_hits++;
        return true;
    } else if (mBatt[coor[1]][coor[0]] == 'X') {
        return true;
    } else {
        mBatt[coor[1]][coor[0]] = '.'; // miss
        return false;
    }
}

void CPlayer::markMyShot(int coor[], bool hit) {
    if (hit == true) {
        eBatt[coor[1]][coor[0]] = 'X';
        //cout << "hit!" << endl;

    } else {
        eBatt[coor[1]][coor[0]] = '.';
        //cout << "miss" << endl;

    }
}

bool CPlayer::getCoord(CShip& ship) {
    srand(time(NULL));
    do {

        ship.coor[0] = rand() % 10;
        ship.coor[1] = rand() % 10;
    } while ((ship.coor[0] + ship.length) >= 10 || (ship.coor[1] + ship.width) >= 10 || !boatOverlap(ship));
    return true;
}

void CPlayer::prepareGame() {
    bool temp = false;
    for (int i = 1; i < 6; i++) {
        CShip boat(i);
        do {
            temp = getCoord(boat);
        } while (!temp);
        addBoat(boat);
    }
}

int CPlayer::getHits() const {
    return n_hits;
}

void CPlayer::incHits() {
    n_hits++;
}




