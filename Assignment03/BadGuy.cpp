/*
 * BadGuy is an enemy character
 * BadGuy has low health and strenght
 * BadGuy will only affect the players health based on its low strength
 */

#include "BadGuy.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

BadGuy::BadGuy() : Enemy("", "", 10, 10, 10) {}
BadGuy::~BadGuy() {}

// Note to self: Make sure you are prefixing everything with the correct Player::
void BadGuy::Attack(vector<Character*> attackVector) {

	// Select someone to fight randomly
	Character* opponent;
	opponent = attackVector[rand() % attackVector.size()];

	// Need to make sure the character wont be fighting himself
	while (opponent == this) {
		opponent = attackVector[rand() % attackVector.size()];
	}

	// The Enemy class loses half of opponents health
	// The enemy class only inflicts half of its own strength
	health -= opponent->GetStrength()/2;
	opponent->SetHealth(opponent->GetHealth() - strength/4);

}