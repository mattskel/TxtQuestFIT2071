#include "Vocation.h"
#include <string>

using namespace std;

Vocation::Vocation(string vocationIn, int healthIn, int strengthIn, int magicIn) {
	vocation = vocationIn;
	health = healthIn;
	strength = strengthIn;
	magic = magicIn;
}

Vocation::~Vocation() {}

string Vocation::GetVocation() {
	return vocation;
}

int Vocation::GetHealth() {
	return health;
}

int Vocation::GetStrength() {
	return strength;
}

int Vocation::GetMagic() {
	return magic;
}