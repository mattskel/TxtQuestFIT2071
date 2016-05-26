//
//  Room.hpp
//  Assignment03
//
//  Created by Matthew Skelley on 17/05/2016.
//  Copyright © 2016 Matthew Skelley. All rights reserved.
//

#ifndef ROOM_H
#define ROOM_H

#include "Event.h"
#include <stdio.h>

class Character;
class Player;
class Enemy;

class Room {
public:
    Room();
    ~Room();
    void SetTopRoom(Room * topRoomIn);
    void SetBottomRoom(Room * bottomRoomIn);
    void SetLeftRoom(Room * leftRoomIn);
    void SetRightRoom(Room * rightRoomIn);
    void SetEvent(int eventIDIn);
    Room * GetTopRoom();
    Room * GetBottomRoom();
    Room * GetLeftRoom();
    Room * GetRightRoom();
    int GetEvent();
    void SetRoomEnemy(Enemy * roomEnemyIn);
    Enemy * GetRoomEnemy();
    void SetPlayer(Player * roomPlayerIn);
    Player * GetPlayer();
    bool visited;
private:
    Room * topRoom;
    Room * bottomRoom;
    Room * leftRoom;
    Room * rightRoom;
    int roomEventID;
    Enemy * roomEnemy;
    Player * roomPlayer;
};

#endif /* ROOM_H */
