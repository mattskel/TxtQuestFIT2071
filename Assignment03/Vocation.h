

#ifndef VOCATION_H
#define VOCATION_H

#include <string>

using namespace std;

class Vocation {
public:
	Vocation() {};
	Vocation(string vocationIn, int healthIn, int strengthIn, int magicIn);
	~Vocation();
	string GetVocation();
	int GetHealth();
	int GetStrength();
	int GetMagic();
private:
	string vocation;
	int health;
	int strength;
	int magic;
};

#endif
