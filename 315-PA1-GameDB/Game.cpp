/* 
	Patrick Sheehan
	CSCE 315 - PA1
	27 January 2013
*/
#include "Game.h"

Game::Game(int ID, string name)
{ // Constructor for a new Game 
	_ID = ID;
	_name = name;
}
int Game::getNumEarnedAchievements(int playerID)
{ // Return the number of achievements in this game that have been earned by the given player
	int count = 0;
	for (vector<Achievement*>::iterator it = _achievements.begin(); it != _achievements.end(); it++)
		if ((*it)->isAchievedBy(playerID)) count++;

	return count;
}
int Game::getGamerscoreFor(int playerID)
{ // Return the gamerscore in this game for the given player
	int score = 0;
	for (vector<Achievement*>::iterator it = _achievements.begin(); it != _achievements.end(); it++)
		if ((*it)->isAchievedBy(playerID)) score += (*it)->getPoints();
	
	return score;
}
void Game::addAchievement(int achievementID, string achieveName, int achievePoints)
{ // Add a new achievement to this game
	_achievements.push_back(new Achievement(_ID, achievementID, achieveName, achievePoints));
}
void Game::addIGN(int playerID, string IGN)
{ // Add a new (playerID, playerIGN) pair to the map of IGNs
	_IGNs.insert(*new pair<int, string>(playerID, IGN));
}
Achievement* Game::getAchievement(int ID) 
{ // Return a pointer to the achievement in this game specified by ID
	for (vector<Achievement*>::iterator it = _achievements.begin(); it != _achievements.end(); it++)
		if ( (*it)->getID() == ID) return (*it);
	
	return NULL;
}
string Game::getIGN(int playerID)
{ // Return the IGN of the given player for this game
	map<int, string>::iterator it = _IGNs.find(playerID);
	if (it != _IGNs.end()) return it->second;
	
	return NULL;
}
string Game::toString()
{ // Return a string representation of this game
	return "Game #" + intToString(_ID) + ": " + _name + "\n";
}
void Game::print()
{ // Print the string representation of this game to standard output
	cout << toString();
}