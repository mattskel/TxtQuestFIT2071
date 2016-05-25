#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Event.h"
#include "Room.h"
#include "Vocation.h"
#include "BadGuy.h"
#include "BadWizard.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

class Game {
public:
	Game();
	~Game();
	void RunGame();
    void GameLoop();
	void InitialiseGame();
    void SetEventArray();
	Player CreateNewPlayer();
	Player LoadExistingPlayer();
    void EndGame();
    void GenerateVisualMap();
    void RecursiveMap(char mapIn[21][21], int xStart, int xFinish, int yStart, int yFinish);
    void PrintVisualMap();
    void GenerateRoomMap();
    void StartPlayerPosition();
    void GetPlayerMove();
//    void MovePlayer(char playerMove);
    void MoveEnemies();
    void InitRoomEvents();
    void ExecuteRoom();
    void GenerateFogOfWar();
    void GenerateEnemyVector();
    void StartEnemyPosition();
    void UpdateVisualMap();
    void Attack(Room * currentRoom);
    void UpdateVisualMapWithoutFog();
    void ResetRoomMap();
    void GenerateNewGameMap();
    void SaveMap();
    void GenerateSavedGame();
private:
	fstream myFile;
    fstream myGameFile;
    ofstream myOutFile;
    ofstream myGameOutFile;
	string line;
	int myRandom;
	int round;
	char playerChoice;
	Event eventArray[6];
    Player player;
    char visualMap[21][21];
    Room roomMap[10][10];
    Room * currentRoom;
    int playerRow;
    int playerCol;
    char fogOfWarMap[21][21];
    vector<Character*> enemyVector;
};

#endif