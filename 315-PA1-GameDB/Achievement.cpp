/* 
	Patrick Sheehan
	CSCE 315 - PA1
	27 January 2013
*/
#include "Achievement.h"

Achievement::Achievement(int gameID, int ID, string name, int points)
{ // Constructor for a new Achievement
	_gameID = gameID;
	_selfID = ID;
	_name = name;
	_points = points;
}
bool Achievement::isAchievedBy(int playerID)
{ // Return true if this achievement has been attained by the given Player
	for (unsigned int i = 0; i < _players.size(); i++)
		if (_players.at(i) == playerID) return true;
	
	return false;
}
string Achievement::toString()
{ // Return a string representation of this Achievement
	string s = "Achievement #" + intToString(_selfID) 
				+ " of game #" + intToString(_gameID) + ": \"" 
				+ _name + "\" - " + intToString(_points) + "pts.\n";
	return s;
}
void Achievement::print()
{ // Print the string representation of this achievement to standard output
	cout << toString();
}