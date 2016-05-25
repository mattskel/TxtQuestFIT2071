#ifndef BADGUY_H
#define BADGUY_H

#include "Enemy.h"

#include <string>
#include <vector>

class BadGuy : public Enemy {
public:
	BadGuy();
 	~BadGuy();

 	virtual void Attack(vector<Character*> attackVector);

};

#endif