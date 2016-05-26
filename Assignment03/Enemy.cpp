#include "Enemy.h"
#include "Room.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

Enemy::Enemy(string nameIn, string vocationIn, int healthIn, int strengthIn, int magicIn) : Character(nameIn, vocationIn, healthIn, strengthIn, magicIn) {}
Enemy::~Enemy() {
    GetRoom()->SetRoomEnemy(NULL);
}

void Enemy::Attack(vector<Character*> attackVector) {}

void Enemy::EnemyMoveRooms() {
}