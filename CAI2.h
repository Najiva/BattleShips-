#include "CPlayer.h"
#include <stack>
#include <vector>

#ifndef CAI2_H
#define	CAI2_H

/**
 * Class represents computer player who's shoots based on previous hits. It saves 
 * all the positions that are below, above and left to a box that has been hit 
 * onto a stack. If the stack is empty, it shoots random. 
 */

class CAI2 : public CPlayer {
public:
    CAI2();
    /**
     * Method chooses where to shoot
     * @param temp coordinates to shoot at
     */
    virtual void shoot(int temp[]);
    /**
     * Method marks if computer hit or not, if yes pushes next shots to the stack
     * @param coor coordinates where to mark the shot
     * @param hit true if computer hit, false if missed
     */
    virtual void markMyShot(int coor[], bool hit);
private:
    std::stack<std::vector<int> > zas; //!< stack of coordinates to shoot at
};

#endif	/* CAI2_H */

