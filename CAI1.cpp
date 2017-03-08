#include "CAI1.h"
#include "CPlayer.h"
#include <cstdlib>
#include <iostream>

using namespace std;

CAI1::CAI1(){
}

void CAI1::shoot(int temp[]){
    srand(time(NULL));
    do {    
    temp[0] = rand() % 10;
    temp[1] = rand() % 10;
    } while (this->eBatt[temp[1]][temp[0]] == 'X' || this->eBatt[temp[1]][temp[0]] == '.');
}


