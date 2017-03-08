#include "CShip.h"
#include "CPlayer.h"

#ifndef CPERSON_H
#define	CPERSON_H

/**
 * Class to represent a human player. 
 */

class CPerson : public CPlayer {
public:
    /**
     * Iniciates player settings i.e. weather to set automatic random positioning of the 
     * ships and automatic MISS/HIT resolving
     * @param ar true for automatic resolving of the hit/miss
     * @param ap true for automatic positioning of the ships
     */
    CPerson(bool ar, bool ap);
    /**
     * Method to get coordinates of the new ship from the person
     * @param ship to be positioned
     * @return true if valid position is found, false if position is invalid
     */
    virtual bool getCoord(CShip&);
    /**
     * Method to prepare the grid of the person 
     */
    virtual void prepareGame();
    /**
     * Method to ask the person for coordinates to shoot at
     * @param temp coordinates to shoot at
     */
    virtual void shoot(int temp[]);
    /**
     * Method to ask the person if his ship is hit
     * @param coor coordinates to check
     * @return true if its hit, false if its not
     */
    virtual bool amIHitted(int coor[]);
    
private:
    bool autoResponse; //!< true if automatic resolving of the "amIHitted" method is desired
    bool autoPrepare; //!< true if automatic positioning of the ships is desired
};

#endif	/* CPERSON_H */

