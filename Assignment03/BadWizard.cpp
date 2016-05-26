/*
* BadWizard is an enemy character
* BadWizard has low health and but high magic
* BadWizard will affect the players helath based on the difference between their magic levels
* The BadWizard has a round modifier that make them more powerful the higher the round
*/

#include "BadWizard.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

BadWizard::BadWizard(int roundMod) : Enemy("", "", 5*roundMod, 5*roundMod, 10*roundMod) {}
BadWizard::~BadWizard() {}

void BadWizard::Attack(vector<Character*> attackVector) {

	// Select someone to fight randomly
	Character* opponent;
	opponent = attackVector[rand() % attackVector.size()];

	// Need to make sure the character wont be fighting himself
	while (opponent == this) {
		opponent = attackVector[rand() % attackVector.size()];
	}

	// The Enemy class loses half of opponents health
	// The enemy class only inflicts half of its own magic
	health -= opponent->GetMagic() / 2;
	opponent->SetHealth(opponent->GetHealth() - magic / 2);

}