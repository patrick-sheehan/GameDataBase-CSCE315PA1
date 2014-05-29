/* 
	Patrick Sheehan
	CSCE 315 - PA1
	27 January 2013
*/
#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <iostream>
#include <vector>
#include <string>

#include "ResourceFunctions.h"

using namespace std;
using namespace ResourceFunctions;

class Achievement{

private:
	int _gameID;
	int _selfID;
	int _points;
	string _name;
	vector<int> _players;

public:
	Achievement(int gameID, int ID, string name, int points);
	
	int getID() { return _selfID; }
	int getGameID() { return _gameID; }
	int getPoints() { return _points; }
	string getName() { return _name; }
	bool isAchievedBy(int playerID);
	int getNumAchievers() { return _players.size(); }
	vector<int> getAchievers() { return _players; }

	void addPlayer(int playerID) { _players.push_back(playerID); }

	void print();
	string toString();
};

#endif