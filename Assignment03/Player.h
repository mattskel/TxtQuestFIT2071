/*
 * This will be the header file for the Player class
 * The Player class will inherit from the Character Class 
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <string>
#include <vector>

class Player : public Character {
public:
	Player();
	Player(string nameIn, string vocationIn, int healthIn, int strengthIn, int magicIn);
 	~Player();

 	virtual void Attack(vector<Character*> attackVector);
    void PlayerMoveRooms(char playerMove);

};

#endif