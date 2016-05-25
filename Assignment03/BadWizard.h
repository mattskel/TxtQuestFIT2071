#ifndef BADWIZARD_H
#define BADWIZARD_H

#include "Enemy.h"

#include <string>
#include <vector>

class BadWizard : public Enemy {
public:
	BadWizard(int roundMod);
	~BadWizard();

	virtual void Attack(vector<Character*> attackVector);

};

#endif