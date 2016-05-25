#ifndef CHARACTER_H
#define CHARACTER_H

#include "Room.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Character {
public:
	Character() {};
	Character(string nameIn, string vocationIn, int healthIn, int strengthIn, int magicIn);
	~Character();
	void SetName(string nameIn);
	void SetHealth(int healthIn);
	void SetStrength(int strengthIn);
	void SetMagic(int magicIn);
	string GetName();
	string GetVocation();
	int GetHealth();
	int GetStrength();
	int GetMagic();
	virtual void Attack(vector<Character*> attackVector);
    void SetRoom(Room * roomIn);
    Room * GetRoom();
protected:
	string name;
	string vocation;
	int health;
	int strength;
	int magic;
    Room * characterRoom;
};

#endif