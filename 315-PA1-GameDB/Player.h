/* 
	Patrick Sheehan
	CSCE 315 - PA1
	27 January 2013
*/
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>

#include "ResourceFunctions.h"

using namespace std;
using namespace ResourceFunctions;

class Player{

private:
	int _ID;
	int _gamerscore;
	string _name;
	vector<int> _games;
	vector<int> _friends;

public:
	Player(int ID, string name);

	void addFriend(int ID) { _friends.push_back(ID); }
	void addGame(int ID) { _games.push_back(ID); }
	void increaseGamerScore(int diff) { _gamerscore += diff; } 

	int getID() { return _ID; }
	string getName() { return _name; }
	vector<int> getFriends() { return _friends; }
	vector<int> getGames() { return _games; }
	bool doesPlay(int gameID);
	bool isFriendsWith(int playerID);
	int getGamerscore() { return _gamerscore; }

	void print();
	string toString();
	bool operator<(Player p2) { return _gamerscore < p2.getGamerscore(); }
};

#endif