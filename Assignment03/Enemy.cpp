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

// Note to self: Make sure you are prefixing everything with the correct Player::
void Enemy::Attack(vector<Character*> attackVector) {}

//void Enemy::SetRoom(Room * roomIn) {
//    enemyRoom = roomIn;
//}
//
//Room * Enemy::GetRoom() {
//    return enemyRoom;
//}

void Enemy::EnemyMoveRooms() {
}