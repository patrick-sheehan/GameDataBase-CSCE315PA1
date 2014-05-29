/* 
	Patrick Sheehan
	CSCE 315 - PA1
	27 January 2013
*/
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "Achievement.h"
#include "ResourceFunctions.h"

using namespace std;
using namespace ResourceFunctions;

class Game{

private:
	int _ID;
	string _name;
	vector<Achievement*> _achievements;
	map<int, string> _IGNs;

public:
	Game(int ID, string name);
	
	int getID() { return _ID; }
	string getName()  { return _name; }
	vector<Achievement*> getAchievements() { return _achievements; }
	map<int, string> getIGNs() { return _IGNs; }
	string getIGN(int playerID);
	int getTotalNumAchievements() { return _achievements.size(); }
	int getNumEarnedAchievements(int playerID);
	int getGamerscoreFor(int playerID);
	int getNumPlayers() { return _IGNs.size(); }

	void addAchievement(int achieveID, string achieveName, int achievePoints);
	void addIGN(int playerID, string IGN);
	Achievement* getAchievement(int ID);

	void print();
	string toString();
};

#endif