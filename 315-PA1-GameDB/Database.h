/* 
	Patrick Sheehan
	CSCE 315 - PA1
	27 January 2013
*/
#include "Player.h"
#include "Game.h"
#include "ResourceFunctions.h"

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace ResourceFunctions;

class Database{

private:
	vector<Player*> _players;
	vector<Game*> _games;

public:
	Database(){}
	
	Player* getPlayer(int playerID);
	Game* getGame(int gameID);

	void listenForInput();
	void interpretInput(string input);

	void AddPlayer(int playerID, string playerName);
	void AddGame(int gameID, string gameName);
	void AddAchievement (int gameID, int achievementID, string achievementName, int achievementPts);
	void Plays (int playerID, int gameID, string playerIGN);
	void AddFriends (int playerID1, int playerID2);
	void Achieve (int playerID, int gameID, int achievementID);
	void FriendsWhoPlay (int playerID, int gameID);
	
	void ComparePlayers (int playerID1, int playerID2, int gameID);
	void SummarizePlayer (int playerID);
	void SummarizeGame (int gameID);
	void SummarizeAchievement (int gameID, int achievementID);
	void AchievementRanking();

	void sortPlayers();
};