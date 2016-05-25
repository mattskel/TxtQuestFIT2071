//
//  Room.cpp
//  Assignment03
//
//  Created by Matthew Skelley on 17/05/2016.
//  Copyright © 2016 Matthew Skelley. All rights reserved.
//

#include "Room.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"


Room::Room() {
    topRoom = NULL;
    bottomRoom = NULL;
    leftRoom = NULL;
    rightRoom = NULL;
    roomEventID = -1;
    roomEnemy = NULL;
    roomPlayer = NULL;
    visited = false;
}
Room::~Room() {}

void Room::SetTopRoom(Room * topRoomIn) {
    topRoom = topRoomIn;
}
void Room::SetBottomRoom(Room * bottomRoomIn) {
    bottomRoom = bottomRoomIn;
}
void Room::SetLeftRoom(Room * leftRoomIn) {
    leftRoom = leftRoomIn;
}
void Room::SetRightRoom(Room * rightRoomIn) {
    rightRoom = rightRoomIn;
}
void Room::SetEvent(int eventIDIn) {
    roomEventID = eventIDIn;
}

Room * Room::GetTopRoom() {
    return topRoom;
}
Room * Room::GetBottomRoom() {
    return bottomRoom;
}
Room *  Room::GetLeftRoom() {
    return leftRoom;
}
Room * Room::GetRightRoom() {
    return rightRoom;
}
int Room::GetEvent() {
    return roomEventID;
}
void Room::SetRoomEnemy(Enemy * roomEnemyIn) {
    roomEnemy = roomEnemyIn;
}
Enemy * Room::GetRoomEnemy() {
    return roomEnemy;
}
void Room::SetPlayer(Player * roomPlayerIn) {
    roomPlayer = roomPlayerIn;
}
Player * Room::GetPlayer() {
    return roomPlayer;
}
