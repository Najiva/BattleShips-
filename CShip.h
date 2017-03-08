#include <string>

#ifndef CSHIP_H
#define	CSHIP_H



class CShip {
public:
    CShip(int typ);
    std::string name;
    int width;
    int length;
    int coor[2];
    int hits, size;
    bool alive;
private:
    
    
};

#endif	/* CSHIP_H */

