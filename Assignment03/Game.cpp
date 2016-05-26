#include "Game.h"
#include "Player.h"
#include "Event.h"
#include "Vocation.h"
#include "BadGuy.h"
#include "BadWizard.h"
#include "Room.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

Game::Game() {}
Game::~Game() {}

/*
// This could potentially hold the method calls that are currently in main
void Game::RunGame() {
}
 */

// GameLoop()
// Responsible for running the main game loop
void Game::GameLoop() {
    
    // This loop runs while the player still has health and wants to continue playing
    do {
        
        // Initialises the playerQuit bool to false
        playerQuit = false;
        
        // Loops while the player wants to keep playing, the player has health and there are still enemies in the maze
        do {
            GetPlayerMove();
            if (!playerQuit) {
                MoveEnemies();
                UpdateVisualMap();
                PrintVisualMap();
                ExecuteRoom();
            }
        } while (!playerQuit && enemyVector.size() > 0 && player.GetHealth() > 0);
        
        // Checks if the player killed all the enemies in the maze and survived or just wants to quit
        // If the player killed all the enemies then the player has the option to quit por continue playing
        if (enemyVector.size() == 0 && player.GetHealth() > 0) {
            round++;
            player.SetHealth(player.GetHealth() + 50 + round * 10);
            GenerateNewGameMap();
            cout << "Congrats! You made it to the next level. Do you want to quit? (y/n) " << endl;
            cin >> playerChoice;
        }
        // If the player chose to quit then they are given a chance to continue playing
        else {
            cout << "Are you sure you want to quit? (y/n) " << endl;
            cin >> playerChoice;
        }
    } while (playerChoice == 'n' && player.GetHealth() > 0);
    
    // Executes the EndGame() method
    EndGame();
    
}

// GenerateNewGameMap()
// Responsible for generating a new game map
// This method is called when the player starts a new game or the player starts a new level
void Game::GenerateNewGameMap() {
    GenerateVisualMap();
    ResetRoomMap();
    GenerateRoomMap();
    StartPlayerPosition();
    InitRoomEvents();
    GenerateEnemyVector();
    StartEnemyPosition();
}

// InitialiseGame()
// Responsible for starting a new game or loading an existing game
void Game::InitialiseGame() {
    // Asks the player if they want to start a new game or load an existing
	cout << "Welcome to TxtQuest. Would you like to load an existing player? (y/n) " << endl;
	cin >> playerChoice;

    // Load an existing player and game
	if (playerChoice == 'y') {
		player = LoadExistingPlayer();
        GenerateSavedGame();
	}
    // Create a new player and new game
	else {
        round = 1;
		player = CreateNewPlayer();
        GenerateNewGameMap();
	}
    
    // Asks the player if they want to play with the fog of war cheat
    char playerCheatChoice;
    cout << "Welcome " << player.GetName() << ", would you like to play with fog of war (y/n)" << endl;
    cin >> playerCheatChoice;
    // Generate fog of war
    if (playerCheatChoice == 'y') {
        cheatMode= false;
        GenerateFogOfWar();
    }
    else {
        cheatMode = true;
    }
    
    // Executes the UpdateVisualMap() method
    UpdateVisualMap();
    // Executes the PrintVisualMap() method
    PrintVisualMap();
}

// SetEventArray()
// Responsible for uploading the events from a text file and populating eventArray
void Game::SetEventArray() {
    string event;
    int healthModifier;
    int count = 0;
    myFile.open("/Users/matthewskelley/University/FIT2071/Assignment03/Assignment03/events.txt");
    while (getline(myFile, line)) {
        stringstream ss(line);
        getline(ss, event, ',');
        ss>>healthModifier;
        eventArray[count + 1].setDescription(event);
        eventArray[count + 1].setHealthMod(healthModifier);
        eventArray[count + 1].setEventID(count + 1);
        count++;
    }
}

// CreateNewPlayer()
// Responsible for creating and returning a new player for the game
Player Game::CreateNewPlayer() {
	fstream myFile;
	string nameIn;
	string vocation;
	string vocationIn;
	int vocationChoice;
	int healthIn;
	int strengthIn;
	int magicIn;
	char tmp;

	// Get the player name from the user
	cout << "Enter your name: ";
	cin >> nameIn;

	// Upload the character types to an array
	Vocation vocationArray[3];
	myFile.open("/Users/matthewskelley/University/FIT2071/Assignment03/Assignment03/vocations.txt");
	int count = 0;
	string line;
	while (getline(myFile, line)) {
		stringstream ss(line);
		getline(ss, vocationIn, ',');
		ss >> healthIn >> tmp >> strengthIn >> tmp >> magicIn;
		vocationArray[count] = Vocation(vocationIn, healthIn, strengthIn, magicIn);
		count++;
	}
	myFile.close();

	cout << "Please select a vocation by entering a number below: " << endl;

	// Display the character types to the player
	for (int i = 0; i < 3; i++) {
		cout << i << ": " << vocationArray[i].GetVocation() << endl;
	}

	// Set the player stats to the vocation selected
	cin >> vocationChoice;
	Vocation playerVocation = vocationArray[vocationChoice];
	Player player = Player(nameIn, playerVocation.GetVocation(), playerVocation.GetHealth(), playerVocation.GetStrength(), playerVocation.GetMagic());

	return player;
}

// LoadExistingPlayer()
// Creates and returns the saved player in the saves.txt file
Player Game::LoadExistingPlayer() {

	fstream myFile;
	string nameIn;
	string vocationIn;
	int healthIn;
	int strengthIn;
	int magicIn;
	char tmp;

	// Open the existing file
	// upload the existing statistics to the player object
	myFile.open("/Users/matthewskelley/University/FIT2071/Assignment03/Assignment03/saves.txt");
	getline(myFile, nameIn, ',');
	getline(myFile, vocationIn, ',');
	myFile >> healthIn >> tmp >> strengthIn >> tmp >> magicIn;
	myFile.close();

	Player player = Player(nameIn, vocationIn, healthIn, strengthIn, magicIn);

	return player;
}

// EndGame()
// Responsible for saving the player and the game if the player has health
// If the player has no health then a message is displayed notifying the player they are dead
// Gets called at the end of a gam
void Game::EndGame() {
    // If the player quits and still has health remaining,  give them the option to save the game
    if (player.GetHealth() > 0) {
        cout << "Would you like to save your game? (y/n)" << endl;
        cin >> playerChoice;
        if (playerChoice == 'y') {
            // Writes character stats to file
            cout << "Your game is being saved..." << endl;
            myOutFile.open("/Users/matthewskelley/University/FIT2071/Assignment03/Assignment03/saves.txt");
            myOutFile << player.GetName() << "," << player.GetVocation() << "," << player.GetHealth() << "," << player.GetStrength() << "," << player.GetMagic();
            myOutFile.close();
            SaveMap();
            cout << "Your game has been saved." << endl;
        }
    }
    else {
        cout << "You are dead :(" << endl;
    }
}


void Game::GenerateVisualMap () {

    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            if (i % 2 == 0 && j % 2 == 0) {
                visualMap[i][j] = '+';
            }
            else if (j == 0 || j == 20) {
                visualMap[i][j] = '|';
            }
            else if (i == 0 || i == 20) {
                visualMap[i][j] = '-';
            }
            else /*(i % 2 == 1 && j % 2 == 1)*/ {
                visualMap[i][j] = ' ';
            }
        }
    }
    RecursiveMap(visualMap, 1, 9, 1, 9);
}

void Game::RecursiveMap(char mapIn[21][21], int xStart, int xFinish, int yStart, int yFinish) {
    int x;
    int y;
    x = xStart + rand() % ((xFinish - xStart + 1));
    y = yStart + rand() % ((yFinish - yStart + 1));
    for (int i = 2 * xStart + 1; i < 2 * xFinish + 3; i += 2) {
        mapIn[2 * y][i] = '-';
    }
    mapIn[2 * y][2 * x - 2 * ((x - xStart) / 2) - 1 ] = ' ';
    mapIn[2 * y][2 * x + 2 * ((xFinish - x) / 2) + 1] = ' ';
    for (int i = 2 * yStart + 1; i < 2 * yFinish + 3; i += 2) {
        mapIn[i][2 * x] = '|';
    }
    mapIn[2 * y - 2 * ((y - yStart) / 2) - 1][2 * x] = ' ';
    mapIn[2 * y + 2 * ((yFinish - y) / 2) + 1][2 * x] = ' ';
    
    if (yFinish - (y + 1) >= 0 && xFinish - (x + 1) >= 0) {
        RecursiveMap(mapIn, x + 1, xFinish, y + 1, yFinish);
    }
    if (yFinish - (y + 1) >= 0 && (x - 1) - xStart >= 0) {
        RecursiveMap(mapIn, xStart, x - 1, y + 1, yFinish);
    }
    if ((y - 1) - yStart >= 0 && (x - 1) - xStart >= 0) {
        RecursiveMap(mapIn, xStart, x - 1, yStart, y - 1);
    }
    if ((y - 1) - yStart >= 0 && xFinish - (x + 1) >= 0) {
        RecursiveMap(mapIn, x + 1, xFinish, yStart, y - 1);
    }
}

void Game::PrintVisualMap() {
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            cout << visualMap[i][j];
        }
        cout << "\n";
    }
}

void Game::GenerateRoomMap() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            
            int row;
            int col;
            row = (2 * i) + 1;
            col = (2 * j) + 1;
            
            if (visualMap[row - 1][col] != '-') {
                roomMap[i][j].SetTopRoom(& roomMap[i - 1][j]);
            }
            if (visualMap[row + 1][col] != '-') {
                roomMap[i][j].SetBottomRoom(& roomMap[i + 1][j]);
            }
            if (visualMap[row][col - 1] != '|') {
                roomMap[i][j].SetLeftRoom(& roomMap[i][j - 1]);
            }
            if (visualMap[row][col + 1] != '|') {
                roomMap[i][j].SetRightRoom(& roomMap[i][j + 1]);
            }
        }
    }
}

void Game::ResetRoomMap() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            roomMap[i][j].visited = false;
            roomMap[i][j].SetRoomEnemy(NULL);
            roomMap[i][j].SetEvent(-1);
            roomMap[i][j].SetTopRoom(NULL);
            roomMap[i][j].SetRightRoom(NULL);
            roomMap[i][j].SetBottomRoom(NULL);
            roomMap[i][j].SetLeftRoom(NULL);
        }
    }
}

void Game::StartPlayerPosition() {
    
    player.GetRoom()->SetPlayer(NULL);
    player.SetRoom(NULL);
    
    playerRow = rand() % 10;
    playerCol = rand() % 10;
    player.SetRoom(& roomMap[playerRow][playerCol]);
    roomMap[playerRow][playerCol].SetPlayer(& player);
    roomMap[playerRow][playerCol].visited = true;
}

void Game::GetPlayerMove() {
    char playerMove;
    bool validMove;
    validMove = false;
    cout<<"What's your next move (n,s,e,w)? Or quit (q)?"<<endl;
    cin>>playerMove;
    while (!validMove) {
        if (playerMove == 'n') {
            if (player.GetRoom()->GetTopRoom() != NULL) {
                validMove = true;
            }
        }
        else if (playerMove == 's') {
            if (player.GetRoom()->GetBottomRoom() != NULL) {
                validMove = true;
            }
        }
        else if (playerMove == 'e') {
            if (player.GetRoom()->GetRightRoom() != NULL) {
                validMove = true;
            }
        }
        else if (playerMove == 'w') {
            if (player.GetRoom()->GetLeftRoom() != NULL) {
                validMove = true;
            }
        }
        else if (playerMove == 'q') {
            playerQuit = true;
            validMove = true;
        }
        if (!validMove) {
            cout<<"Incorrect move, try again. What's your next move (n,s,e,w)? Or quit (q)?"<<endl;
            cin>>playerMove;
        }
    }
    
    if (playerMove != 'q') {
        player.GetRoom()->SetPlayer(NULL);
        player.PlayerMoveRooms(playerMove);
        player.GetRoom()->SetPlayer(& player);
        player.GetRoom()->visited = true;
    }
}

void Game::MoveEnemies() {
    for (Character * enemy : enemyVector) {
        Room * currentRoom = enemy->GetRoom();
        Room * nextRoom = NULL;
        if (currentRoom->GetPlayer() == NULL) {
            bool validRoom = false;
            while (!validRoom) {
                switch (rand() % 4) {
                    case 0:
                        nextRoom = currentRoom->GetTopRoom();
                        break;
                    case 1:
                        nextRoom = currentRoom->GetRightRoom();
                        break;
                    case 2:
                        nextRoom = currentRoom->GetBottomRoom();
                        break;
                    case 3:
                        nextRoom = currentRoom->GetLeftRoom();
                        break;
                    default:
                        break;
                }
                validRoom = true;
            }
            if (nextRoom != NULL && nextRoom->GetPlayer() == NULL && nextRoom->GetRoomEnemy() == NULL) {
                currentRoom->SetRoomEnemy(NULL);
                enemy->SetRoom(nextRoom);
                nextRoom->SetRoomEnemy(dynamic_cast<Enemy *>(enemy));
                validRoom = true;
            }
        }
        
    }
}

void Game::InitRoomEvents() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int tmpRand;
            tmpRand = rand() % 20 + 1;
            if (tmpRand < 5) {
                roomMap[i][j].SetEvent(tmpRand);
            }
        }
    }
}

void Game::ExecuteRoom() {
    
    Room * currentRoom = player.GetRoom();
    
    // First check if there is an enemy in the room
    if (currentRoom->GetRoomEnemy() != NULL) {
        cout << "You just got into a fight!" <<endl;
        Attack(currentRoom);
    }
    
    int eventID = player.GetRoom()->GetEvent();
    
    if (eventID != -1) {
        
        cout<<eventID<<endl;
    
        string description;
        description = eventArray[eventID].getDescription();
        int healthMod = eventArray[eventID].getHealthMod();
        
        cout << description << endl;
        cout << "Your health will be modified " << healthMod << endl;
        int newHealth = player.GetHealth() + healthMod;
        player.SetHealth(newHealth);
        
        // This ensures an event will only be executed once
        player.GetRoom()->SetEvent(-1);
        
    }
    
    cout<<"Player Health: "<<player.GetHealth()<<endl;
}

void Game::GenerateFogOfWar() {
    cout<<"HERE"<<endl;
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            visualMap[i][j] = '*';
        }
    }
}

void Game::GenerateEnemyVector() {
    
    for (int i = 0; i < round + 1; i++) {
        // A "BadGuy" or a "BadWizard" is randomly added to the enemy vector
        // More likely a "BadGuy" as they are easier to fight
        myRandom = rand() % (round + 1);
        // As the round increases, the probability of getting a BadWizard becomes higher
        // Thus making it harder as the rounds increase
        if (myRandom <= 5) {
            enemyVector.push_back(new BadGuy());
        }
        else {
            enemyVector.push_back(new BadWizard(round));
        }
    }
}

void Game::StartEnemyPosition() {
    for (Character * enemy : enemyVector) {
        int i = rand() % 10;
        int j = rand() % 10;
        dynamic_cast<Enemy *>(enemy)->SetRoom(& roomMap[i][j]);
        roomMap[i][j].SetRoomEnemy(dynamic_cast<Enemy *>(enemy));
        visualMap[(2 * i + 1)][(2 * j + 1)] = 'e';
    }
}
// UpdateVisualMap
// Updates the visual map with the fog of war
// The map is only exposed if the player has visited it
void Game::UpdateVisualMap() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            
            if (roomMap[i][j].GetEvent() == 3 && roomMap[i][j].GetPlayer() == NULL) {
                visualMap[(2 * i + 1)][(2 * j + 1)] = 'H';
            }
            if (cheatMode || roomMap[i][j].visited == true){
                if (roomMap[i][j].GetTopRoom() == NULL) {
                    visualMap[(2 * i + 1) - 1][(2 * j + 1)] = '-';
                }
                else {
                    visualMap[(2 * i + 1) - 1][(2 * j + 1)] = ' ';
                }
                if (roomMap[i][j].GetRightRoom() == NULL) {
                    visualMap[(2 * i + 1)][(2 * j + 1) + 1] = '|';
                }
                else {
                    visualMap[(2 * i + 1)][(2 * j + 1) + 1] = ' ';
                }
                if (roomMap[i][j].GetBottomRoom() == NULL) {
                    visualMap[(2 * i + 1) + 1][(2 * j + 1)] = '-';
                }
                else {
                    visualMap[(2 * i + 1) + 1][(2 * j + 1)] = ' ';
                }
                if (roomMap[i][j].GetLeftRoom() == NULL) {
                    visualMap[(2 * i + 1)][(2 * j + 1) - 1] = '|';
                }
                else {
                    visualMap[(2 * i + 1)][(2 * j + 1) - 1] = ' ';
                }
                if (roomMap[i][j].GetPlayer() != NULL) {
                    visualMap[(2 * i + 1)][(2 * j + 1)] = 'P';
                }
                else if (roomMap[i][j].GetRoomEnemy() != NULL) {
                    visualMap[(2 * i + 1)][(2 * j + 1)] = 'e';
                }
                else {
                    visualMap[(2 * i + 1)][(2 * j + 1)] = ' ';
                }
                visualMap[(2 * i + 1) - 1][(2 * j + 1) - 1] = '+';
                visualMap[(2 * i + 1) - 1][(2 * j + 1) + 1] = '+';
                visualMap[(2 * i + 1) + 1][(2 * j + 1) + 1] = '+';
                visualMap[(2 * i + 1) + 1][(2 * j + 1) - 1] = '+';
            }
        }
    }
}

void Game::Attack(Room * currentRoom) {
    // Create a vector of pointers to Character objects
    vector<Character*> attackVector;
    
    // Add the player to the vector
    attackVector.push_back(&player);
    attackVector.push_back(currentRoom->GetRoomEnemy());
    
    // Get the position of an enemy in the enemy vector
    int j = 0;
    while (enemyVector[j] != currentRoom->GetRoomEnemy()) {
        j++;
    }
    
    // Now we want the elements in the vector to fight each other
    // The idea is they keep fighting until there is only one left
    while (attackVector.size() > 1) {
        
        // Everyone in the vector gets to make an attack
        for (int i = 0; i < attackVector.size(); i++) {
            // You can't attack if you are already dead
            if (attackVector[i]->GetHealth() > 0) {
                attackVector[i]->Attack(attackVector);
            }
        }
        
        // We have to remove any of the dead from the vector
        for (int i = 0; i < attackVector.size(); i++) {
            if (attackVector[i]->GetHealth() <= 0) {
                // First delete the object from memory
                // Don't want to delete the player object,  only the enemy objects
                if (i != 0) {
                    delete dynamic_cast<Enemy *>(attackVector[i]);
                }
                // Then delete the reference from the vector
                attackVector.erase(attackVector.begin() + i);
                enemyVector.erase(enemyVector.begin() + j);
            }
        }
    }
}

// UpdateVisualMapWithoutFog()
// Updates the map without fog of war
// Can be used as a cheat to play without fog of war on map
//void Game::UpdateVisualMapWithoutFog() {
//    for (int i = 0; i < 10; i++) {
//        for (int j = 0; j < 10; j++) {
//            if (cheatMode || roomMap[i][j].visited == true) {
//                if (roomMap[i][j].GetPlayer() != NULL) {
//                    visualMap[(2 * i + 1)][(2 * j + 1)] = 'P';
//                }
//                else if (roomMap[i][j].GetEvent() == 3) {
//                    visualMap[(2 * i + 1)][(2 * j + 1)] = 'H';
//                }
//                else if (roomMap[i][j].GetRoomEnemy() != NULL) {
//                    visualMap[(2 * i + 1)][(2 * j + 1)] = 'e';
//                }
//                else {
//                    visualMap[(2 * i + 1)][(2 * j + 1)] = ' ';
//                }
//                
//                if (roomMap[i][j].GetTopRoom() == NULL) {
//                    visualMap[(2 * i + 1) - 1][(2 * j + 1)] = '-';
//                }
//                else {
//                    visualMap[(2 * i + 1) - 1][(2 * j + 1)] = ' ';
//                }
//                if (roomMap[i][j].GetRightRoom() == NULL) {
//                    visualMap[(2 * i + 1)][(2 * j + 1) + 1] = '|';
//                }
//                else {
//                    visualMap[(2 * i + 1)][(2 * j + 1) + 1] = ' ';
//                }
//                if (roomMap[i][j].GetBottomRoom() == NULL) {
//                    visualMap[(2 * i + 1) + 1][(2 * j + 1)] = '-';
//                }
//                else {
//                    visualMap[(2 * i + 1) + 1][(2 * j + 1)] = ' ';
//                }
//                if (roomMap[i][j].GetLeftRoom() == NULL) {
//                    visualMap[(2 * i + 1)][(2 * j + 1) - 1] = '|';
//                }
//                else {
//                    visualMap[(2 * i + 1)][(2 * j + 1) - 1] = ' ';
//                }
//                visualMap[(2 * i + 1) - 1][(2 * j + 1) - 1] = '+';
//                visualMap[(2 * i + 1) - 1][(2 * j + 1) + 1] = '+';
//                visualMap[(2 * i + 1) + 1][(2 * j + 1) + 1] = '+';
//                visualMap[(2 * i + 1) + 1][(2 * j + 1) - 1] = '+';
//            }
//        }
//    }
//}

void Game::SaveMap() {
    
    myGameOutFile.open("/Users/matthewskelley/University/FIT2071/Assignment03/Assignment03/GameSave.txt");
    myGameOutFile << round << endl;
    
    /*
     * Enemy Vector
     * Store the enemy vector first
     */
    
    myGameOutFile << enemyVector.size() << endl;
    
    for (Character * enemy : enemyVector) {
        
        string enemyString;
        
        if (dynamic_cast<BadGuy *>(enemy)) {
            enemyString += "0 ";
        }
        else {
            enemyString += "1 ";
        }
        
        enemyString += to_string(enemy->GetHealth()) + " " + to_string(enemy->GetStrength()) + " " + to_string(enemy->GetMagic());
        
        myGameOutFile << enemyString << endl;
        
    }
    
    /*
     * Room
     * top, right, bottom, left, enemy, eventid, visited
     */
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            string roomSaveString;
        
            Room * room;
            room = & roomMap[i][j];
            
            if (room->GetTopRoom() == NULL) {
                roomSaveString += "0 ";
            }
            else {
                roomSaveString += "1 ";
            }
            
            if (room->GetRightRoom() == NULL) {
                roomSaveString += "0 ";
            }
            else {
                roomSaveString += "1 ";
            }
            
            if (room->GetBottomRoom() == NULL) {
                roomSaveString += "0 ";
            }
            else {
                roomSaveString += "1 ";
            }
            
            if (room->GetLeftRoom() == NULL) {
                roomSaveString += "0 ";
            }
            else {
                roomSaveString += "1 ";
            }
            
            // Set the enemy
            int i = 0;
            while (i < enemyVector.size() && room->GetRoomEnemy() != enemyVector[i]) {
                i++;
            }
            if (i < enemyVector.size()) {
                roomSaveString += to_string(i) + " ";
            }
            else {
                roomSaveString += "-1 ";
            }
            
            // Set the event
            roomSaveString += to_string(room->GetEvent()) + " ";
            
            // Set visited
            if (room->GetPlayer() != NULL) {
                roomSaveString += "1 ";
            }
            else if (room->visited) {
                roomSaveString += "0 ";
            }
            else {
                roomSaveString += "-1 ";
            }
            
            myGameOutFile << roomSaveString << endl;
        }
    }
    
    myOutFile.close();
    
}

void Game::GenerateSavedGame() {
    
    myGameFile.open("/Users/matthewskelley/University/FIT2071/Assignment03/Assignment03/GameSave.txt");
    
    int numberOfEnemies;
    
    myGameFile >> round;
    myGameFile >> numberOfEnemies;
    
    for (int i = 0; i < numberOfEnemies; i++) {
        int type, healthIn, strenghtIn, magicIn;
        myGameFile >> type >> healthIn >> strenghtIn >> magicIn;
        
        if (type == 0) {
            enemyVector.push_back(new BadGuy());
        }
        else {
            enemyVector.push_back(new BadWizard(round));
        }
        enemyVector[enemyVector.size() - 1]->SetHealth(healthIn);
        enemyVector[enemyVector.size() - 1]->SetStrength(strenghtIn);
        enemyVector[enemyVector.size() - 1]->SetMagic(magicIn);
    }
    
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int topRoom, rightRoom, bottomRoom, leftRoom, enemyPos, event, visited;
            myGameFile >> topRoom >> rightRoom >> bottomRoom >> leftRoom >> enemyPos >> event >> visited;
            if (topRoom == 1) {
                roomMap[i][j].SetTopRoom(& roomMap[i - 1][j]);
            }
            if (rightRoom == 1) {
                roomMap[i][j].SetRightRoom(& roomMap[i][j + 1]);
            }
            if (bottomRoom == 1) {
                roomMap[i][j].SetBottomRoom(& roomMap[i + 1][j]);
            }
            if (leftRoom == 1) {
                roomMap[i][j].SetLeftRoom(& roomMap[i][j - 1]);
            }
            
            if (enemyPos != -1) {
                dynamic_cast<Enemy *>(enemyVector[enemyPos])->SetRoom(& roomMap[i][j]);
                roomMap[i][j].SetRoomEnemy(dynamic_cast<Enemy *>(enemyVector[enemyPos]));
            }
            
            if (event != -1) {
                roomMap[i][j].SetEvent(event);
            }
            if (visited == 1) {
                roomMap[i][j].SetPlayer(& player);
                player.SetRoom(& roomMap[i][j]);
                roomMap[i][j].visited = true;
            }
            else if (visited == 0) {
                roomMap[i][j].visited = true;
            }
        }
    }
    
    myGameFile.close();
}