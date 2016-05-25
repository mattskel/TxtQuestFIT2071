#include "Event.h"
#include <string>
#include <iostream>

using namespace std;

Event::Event() {
    description = "";
    healthMod = 0;
    eventID = -1;
}

//Event::Event(string descriptionIn, int healthModIn, int eventIDIn) {
//	description = descriptionIn;
//	healthMod = healthModIn;
//    eventID = eventIDIn;
//}

Event::~Event() {}

void Event::setDescription(string descriptionIn) {
	description = descriptionIn;
}

void Event::setHealthMod(int healthModIn) {
	healthMod = healthModIn;
}

void Event::setEventID(int eventIDIn) {
    eventID = eventIDIn;
}

string Event::getDescription() {
	return description;
}

int Event::getHealthMod() {
	return healthMod;
}

int Event::getEventID() {
    return eventID;
}