/*
 * This file describes the Enemy
 */

#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

#include <string>
#include <vector>

// Forward declaration
class Room;

class Enemy : public Character {
public:
	Enemy(string nameIn, string vocationIn, int healthIn, int strengthIn, int magicIn);
 	~Enemy();
 	virtual void Attack(vector<Character*> attackVector);
    void EnemyMoveRooms();
private:
    Room * enemyRoom;

};

#endif