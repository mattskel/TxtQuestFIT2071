#include "Character.h"
#include "Room.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

Character::Character(string nameIn, string vocationIn, int healthIn, int strengthIn, int magicIn) {
	name = nameIn;
	vocation = vocationIn;
	health = healthIn;
	strength = strengthIn;
	magic = magicIn;
}

Character::~Character() {}

void Character::SetName(string nameIn) {
	name = nameIn;
}

string Character::GetName() {
	return name;
}

string Character::GetVocation() {
	return vocation;
}

void Character::SetHealth(int healthIn) {
	health = healthIn;
}

int Character::GetHealth() {
	return health;
}

void Character::SetStrength(int strengthIn) {
	strength = strengthIn;
}

int Character::GetStrength() {
	return strength;
}

void Character::SetMagic(int magicIn) {
	magic = magicIn;
}

int Character::GetMagic() {
	return magic;
}

void Character::Attack(vector<Character*> attackVector) {}

void Character::SetRoom(Room * roomIn) {
    characterRoom = roomIn;
}
Room * Character::GetRoom() {
    return characterRoom;
}