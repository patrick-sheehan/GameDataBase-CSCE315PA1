/* 
	Patrick Sheehan
	CSCE 315 - PA1
	27 January 2013
*/
#include "Player.h"

Player::Player(int ID, string name)
{ // Constructor for a new Player
	_ID = ID;
	_name = name;
	_gamerscore = 0;
}
bool Player::doesPlay(int gameID)
{ // Return true if this player plays the game specified by gameID
	for (unsigned int i = 0; i < _games.size(); i++)
		if (_games.at(i) == gameID)
			return true;

	return false;
}
bool Player::isFriendsWith(int playerID)
{ // Return true if this player if friends with the Player specified by playerID
	for (unsigned int i = 0; i < _friends.size(); i++)
		if (_friends.at(i) == playerID)
			return true;

	return false;
}
string Player::toString()
{ // Return a string representation of this Player
	string s = "Player #" + intToString(_ID) + ": " + _name + "\n";
	return s;
}
void Player::print()
{ // Print the string representation of this Player to standard output
	cout << toString();
}