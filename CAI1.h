#include "CPlayer.h"

#ifndef CAI1_H
#define	CAI1_H

/**
 * Class represnets computer player which shoots randomly. 
 */

class CAI1 : public CPlayer {
public:
    CAI1();
    /**
     * Method chooses where to shoot randomly. It doesnt shoot at previously 
     * hit/missed positions.
     * @param temp coorditantes to shoot at
     */
    virtual void shoot(int temp[]);
private:

};

#endif	/* CAI1_H */

