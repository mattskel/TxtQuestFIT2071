/*
* Player character
* Player character has his own attack function that depends on the strenght and magic levels
*/

#include "Player.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

Player::Player() {}
Player::Player(string nameIn, string vocationIn, int healthIn, int strengthIn, int magicIn) : Character(nameIn, vocationIn, healthIn, strengthIn, magicIn) {}
Player::~Player() {}

void Player::Attack(vector<Character*> attackVector) {

	// Select someone to fight randomly
	Character* opponent;
	opponent = attackVector[rand() % attackVector.size()];

	// Need to make sure the character wont be fighting himself
	while (opponent == this) {
		opponent = attackVector[rand() % attackVector.size()];
	}

	// Player health is modified based on the opponent strength and the opponent magic
	health -= opponent->GetStrength() / 4;
	health += (magic - opponent->GetMagic()) / 4;
	opponent->SetHealth(opponent->GetHealth() - strength/2 + (opponent->GetMagic() - magic) / 2);

}
void Player::PlayerMoveRooms(char playerMove) {
    if (playerMove == 'n') {
        characterRoom = characterRoom->GetTopRoom();
    }
    else if (playerMove == 's') {
        characterRoom = characterRoom->GetBottomRoom();
    }
    else if (playerMove == 'e') {
        characterRoom = characterRoom->GetRightRoom();
    }
    else if (playerMove == 'w') {
        characterRoom = characterRoom->GetLeftRoom();
    }
}
