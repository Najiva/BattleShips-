#include "CShip.h"
#include <cstdlib>
#include <iostream>

#ifndef CPLAYER_H
#define	CPLAYER_H

/**
 * Virtual class that represents a player object. 
 */

class CPlayer {
public:
    /**
     * Constructor of the CPlayer iniciates 10x10 grids and fills then with '~'. 
     */
    CPlayer();
    /**
     * Method prints both grids.
     */
    void printmBatt() const ;
    /**
     * Method adds a ship to the player battleground
     * @param parameter of the method is reference to a ship
     */
    void addBoat(CShip &);
    /**
     * Method evaluates if a ship overlaps with already added ship
     * @param reference to the ship being added
     * @return true if boats does <b>not</b> overlap
     */
    bool boatOverlap(CShip &) const;
    /**
     * Method marks to the grid HIT/MISS of players shot
     * @param coor coordinates to mark the shot at
     * @param hit decides if its hit or miss
     */
    virtual void markMyShot(int coor[], bool hit);
    /**
     * Method to get a random coordinates of a ship to be added
     * @param reference to a ship
     * @return true if such coordinates are found, never returns false
     */
    virtual bool getCoord(CShip &);
    /**
     * Method to prepare the game. Places all the ships to the grid.
     */
    virtual void prepareGame();
    /**
     * Method to decide what coordinates to shoot at.
     * @param coor coordinates to shoot at
     */
    virtual void shoot(int coor[]) = 0;
    /**
     * Pure virtual method to decide if a player is hit or not at certain coordinates. 
     * @param coor coordinates to check for hit/miss
     * @return true if the player is hit to a ship or to a shipwreck
     */
    virtual bool amIHitted(int coor[]);
    /**
     * Getter method for how many times a player has been hit
     * @return number of sunk boxes
     */
    int getHits() const;
    /**
     * Method to increment number of sunk boxes of a player
     */
    void incHits();
    
    
private:
    int n_hits; //!< Number of sunk boxes of a player
protected:
    char mBatt[10][10]; //!< Players grid of ships
    char eBatt[10][10]; //!< Enemy's grid of ships
    
};



#endif	/* CPLAYER_H */

