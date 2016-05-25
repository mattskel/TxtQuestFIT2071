#ifndef EVENT_H
#define EVENT_H

#include <string>

using namespace std;

class Event {
public:
    Event();
//	Event(string descriptionIn, int healthModIn, int eventID);
	~Event();
	void setDescription(string descriptionIn);
	void setHealthMod(int healthModIn);
    void setEventID(int eventIDIn);
	string getDescription();
	int getHealthMod();
    int getEventID();
private:
	string description;
	int healthMod;
    int eventID;
};

#endif