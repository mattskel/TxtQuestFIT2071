#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include "Character.h"
#include "Event.h"
#include "Vocation.h"
#include "Player.h"
#include "Enemy.h"
#include "BadGuy.h"
#include "BadWizard.h"
#include "Game.h"

using namespace std;

void playGame();
Player existingPlayer();
Player newPlayer();


int main () {

//	playGame();
    
    Game game;
    game.InitialiseGame();
    game.SetEventArray();
    
    game.SaveMap();
    
//    game.GenerateNewGameMap();
    
    game.GameLoop();
    
    //	system("pause");
	return 0;
}

/*
// playGame() is responsible for uploading information from files and running the game loop
void playGame() {

	fstream myFile;
    ofstream myOutFile;
	string line;
	int myRandom;
	int round;
	char playerChoice;

	cout<<"Welcome to TxtQuest. Would you like to load an existing player? (y/n) "<<endl;
	cin>>playerChoice;

	Player player;

	if (playerChoice == 'y') {
		player = existingPlayer();
	}
	else {
		player = newPlayer();
	}
	
	// Get the event descriptions
	// Set the eventArray to the events from the .txt file
	string event;
	int healthModifier;

	Event eventArray[5];

	myFile.open("/Users/matthewskelley/University/FIT2071/Assignment03/Assignment03/events.txt");
	int count = 0;
	while (getline(myFile, line)) {
		stringstream ss(line);
		getline(ss, event, ',');
		ss>>healthModifier;
		eventArray[count] = Event(event, healthModifier);
		count++;
	}

	// The main game loop
	// The main game loop runs while the player still has health and wants to continue playing
	// each loop,  the player is faced with a randomly generated event or attack
	round = 0;
	do {
		// Generate a random number
		// This random number will determine what event or attack occurs
		myRandom = rand() % 10;

		if (myRandom >= 5) {

			// Fight event
			cout << "You just got into a fight. I hope you can handle it!" << endl;

			// Create a vector of pointers to Character objects
			vector<Character*> attackVector;

			// Add the player to the vector
			attackVector.push_back(&player);

			// Create multiple enemies and add them to the vector
			// The number of enemies is dependent on the round number
			// The higher the round, the more enemies
			for (int i = 0; i < round + 1; i++) {
				// A "BadGuy" or a "BadWizard" is randomly added to the enemy vector
				// More likely a BadGuy as they are easier to fight
				myRandom = rand() % (round + 1);
				// As the round increases, the probability of getting a BadWizard becomes higher
				// Thus making it harder as the rounds increase
				if (myRandom <= 5) {
					attackVector.push_back(new BadGuy());
				}
				else {
					attackVector.push_back(new BadWizard(round));
				}
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
							delete attackVector[i];
						}
						// Then delete the reference from the vector
						attackVector.erase(attackVector.begin() + i);
					}
				}
			}
			// After the while loop,  there is only one character left in the fight
			// The players health will be automatically updated

			// If the player survives the fight he will be rewarded with more health, magic and strength
			if (player.GetHealth() > 0) {
				cout << "You won the fight!" << endl;
				player.SetHealth(player.GetHealth() + round*5);
				player.SetStrength(player.GetStrength() + round);
				player.SetMagic(player.GetMagic() + round);
			}

		}
		else {

			// Standard event from event array
			// An event will be selected using the previously generated random number
			
			string description = eventArray[myRandom].getDescription();
			int healthMod = eventArray[myRandom].getHealthMod();

			cout << description << endl;
			cout << "Your health will be modified " << healthMod << endl;
			int newHealth = player.GetHealth() + healthMod;
			player.SetHealth(newHealth);

		}

		// Only give the player the option to play again if they have enough health
		// The following if condition checks the player has enough health to keep playing
		if (player.GetHealth() > 0) {
			cout << "Your health is " << player.GetHealth() << endl;
			cout << "Do you want to continue playing? (y/n) " << endl;
			cin >> playerChoice;
		}

		// After every round the round increases
		round++;

	} while (playerChoice == 'y' && player.GetHealth() > 0);

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
			cout << "Your game has been saved." << endl;
		}
	}
	else {
		cout << "You are dead :(" << endl;
	}
	
}

// existingPlayer() uploads an existing player profile
Player existingPlayer() {

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
    
    cout<<nameIn<<endl;
    cout<<vocationIn<<endl;

	Player player = Player(nameIn, vocationIn, healthIn, strengthIn, magicIn);

	return player;

}

// newPlayer() creates a new player
Player newPlayer() {

	fstream myFile;
	string nameIn;
	string vocation;
	string vocationIn;
	int vocationChoice;
	int healthIn;
	int strengthIn;
	int magicIn;
	char tmp;

	// Get the player name
	cout<<"Enter your name: ";
	cin>>nameIn;

	// Upload the character types to an array
	Vocation vocationArray[3];
//	myFile.open("vocations.txt");
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
*/
