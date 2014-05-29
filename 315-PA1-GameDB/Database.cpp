/* 
	Patrick Sheehan
	CSCE 315 - PA1
	27 January 2013
*/
#include "Database.h"

void Database::listenForInput()
{ // Start command prompt; infinite loop that waits for commands
	string input;
	for ( ; ; )
	{
		cout << "Sheehan's Game Database > ";
		getline(cin, input);
	
		if (input == "quit") return;
		else interpretInput(input);
	}
}
void Database::interpretInput(string input)
{ // Interpret the input from the command line and call the appropriate function
	string name;
	stringstream stream(input);
	string function, arg1, arg2, arg3, arg4;
	int arg1int, arg2int, arg3int, arg4int;

	getline(stream, function, ' ');
	function = toLower(function);
	getline(stream, arg1, ' ');
	arg1int = stringToInt(arg1);
	

	if (function == "addplayer" || function == "addgame")
	{ // 1st argument is int, 2nd is a quote-enclosed string
		size_t first = input.find("\"") + 1;
		size_t last = input.find("\"", first);
		name = input.substr(first, last - first);
		if (function == "addplayer") AddPlayer(arg1int, name);
		else if (function == "addgame") AddGame(arg1int, name);
		return;
	}
	else if (function == "addachievement" || function == "plays")
	{ // 1st and 2nd args are ints, 3rd is a quote-enclosed string
		getline(stream, arg2, ' ');
		arg2int = stringToInt(arg2);

		size_t first = input.find("\"") + 1;
		size_t last = input.find("\"", first);
		name = input.substr(first, last - first);
		
		arg4 = input.substr(last + 1);
		arg4int = stringToInt(arg4);
		
		if (function == "addachievement") AddAchievement(arg1int, arg2int, name, arg4int);
		else if (function == "plays") Plays(arg1int, arg2int, name);
		return;
	}
	else
	{ // all arguments are ints
		getline(stream, arg2, ' ');
		getline(stream, arg3, ' ');
		getline(stream, arg4, ' ');

		arg2int = stringToInt(arg2);
		arg3int = stringToInt(arg3);
		arg4int = stringToInt(arg4);

		if (function == "addfriends") AddFriends(arg1int, arg2int);
		else if (function == "achieve") Achieve(arg1int, arg2int, arg3int);
		else if (function == "friendswhoplay") FriendsWhoPlay(arg1int, arg2int);
		else if (function == "compareplayers") ComparePlayers(arg1int, arg2int, arg3int);
		else if (function == "summarizeplayer") SummarizePlayer(arg1int);
		else if (function == "summarizegame") SummarizeGame(arg1int);
		else if (function == "summarizeachievement") SummarizeAchievement(arg1int, arg2int);
		else if (function == "achievementranking") AchievementRanking();
		return;
	}
}
Player* Database::getPlayer(int playerID)
{ // Return pointer to a Player in the database if it exists, NULL otherwise
	for (vector<Player*>::iterator it = _players.begin(); it != _players.end(); it++)
		if ((*it)->getID() == playerID)
			return (*it);

	return NULL;
}
Game* Database::getGame(int gameID)
{ // Return pointer to a Game in the database if it exists, NULL otherwise
	for (vector<Game*>::iterator it = _games.begin(); it != _games.end(); it++)
		if ((*it)->getID() == gameID)
			return (*it);

	return NULL;
}
void Database::AddPlayer(int playerID, string playerName)
{ // Add player to the database
	Player *p = new Player(playerID, playerName);
	_players.push_back(p);
}
void Database::AddGame(int gameID, string gameName)
{ // Add game to the database
	Game *g = new Game(gameID, gameName);
	_games.push_back(g);
}
void Database::AddAchievement (int gameID, int achievementID, string achievementName, int achievementPts)
{ // Add achievement to the game denoted by <Game ID>
	Game* g = getGame(gameID);
	g->addAchievement(achievementID, achievementName, achievementPts);
}
void Database::Plays (int playerID, int gameID, string playerIGN)
{ // Add entry for player playing a specific game
	Game* g = getGame(gameID);
	g->addIGN(playerID, playerIGN);

	Player* p = getPlayer(playerID);
	p->addGame(gameID);
}
void Database::AddFriends (int playerID1, int playerID2)
{ // Makes players 1 & 2 friends. Friends are mutual.
	Player* p1 = getPlayer(playerID1);
	Player* p2 = getPlayer(playerID2);

	p1->addFriend(playerID2);
	p2->addFriend(playerID1);
}
void Database::Achieve (int playerID, int gameID, int achievementID)
{ // Adds achievement indicated to <Player ID>'s record.
	Game* g = getGame(gameID);
	Achievement* a = g->getAchievement(achievementID);
	a->addPlayer(playerID);
	Player* p = getPlayer(playerID);
	p->increaseGamerScore(a->getPoints());
}
void Database::FriendsWhoPlay (int playerID, int gameID)
{ // Report which of player's friends play the specified game.
	Player* p = getPlayer(playerID);
	Game* g = getGame(gameID);

	cout << p->getName() << " has the following friends that play " << g->getName() << ":\n\n";

	vector<int> friends = p->getFriends();
	for (unsigned int i = 0; i < friends.size(); i++)
	{
		int friendID = friends.at(i);
		Player* pFriend = getPlayer(friendID);
		
		if (pFriend != NULL)
			if (pFriend->doesPlay(gameID))
				pFriend->print();
	}
}
void Database::ComparePlayers (int playerID1, int playerID2, int gameID)
{ // Print report comparing player 1 and player 2's achievement records.
	Player* p1 = getPlayer(playerID1);
	Player* p2 = getPlayer(playerID2);
	Game* g = getGame(gameID);

	if (p1 == NULL || p2 == NULL) 
	{ 
		cout << "One or both players don't exist in the database\n"; 
		return;
	}
	else if (g == NULL) 
	{
		cout << "The specified game doesn't exist in the database\n";
		return;
	}
	else if (g->getTotalNumAchievements() < 1) 
	{
		cout << "No achievements found for this game" << endl;
		return;
	}
	else
	{
		cout << setw(16) << "Achievement Name" << setw(16) << p1->getName() << setw(16) << p2->getName() << endl;
		cout << setw(48) << "------------------------------------------------" << endl;
		vector<Achievement*> achievements = g->getAchievements();
		for (vector<Achievement*>::iterator it = achievements.begin(); it < achievements.end(); it++)
		{
			Achievement* a = *it;
			cout << setw(16) << a->getName() << setw(16);
			if (a->isAchievedBy(playerID1)) cout << "achieved";
			if (a->isAchievedBy(playerID2)) cout << setw(16) << "achieved";
			cout << endl;
		}
		cout << endl;
	}
}
void Database::SummarizePlayer (int playerID)
{ // Print record of all of the player's friends, games, and gamer point totals.
	Player* p = getPlayer(playerID);
	vector<int> games = p->getGames();
	vector<int> friends = p->getFriends();
	
	cout << "\nPlayer: " << p->getName() << "    Gamerscore: " << p->getGamerscore() << endl;
		
	if (games.size() < 1) cout << "No games found for this player" << endl;
	else
	{
		cout << "\n\n" <<setw(16) << "Game" << setw(14) << "Achievements" << setw(12) << "Gamerscore" << setw(24) << "IGN" << endl;
		cout << setw(66) << "------------------------------------------------------------------" << endl;
	
		for (unsigned int i = 0; i < games.size(); i++)
		{
			Game* g = getGame(games.at(i));
			int numEarned = g->getNumEarnedAchievements(playerID);
			int totalNum = g->getTotalNumAchievements();
			string achievementFraction = intToString(numEarned) + "/" + intToString(totalNum);
			cout << setw(16) << g->getName() << setw(14) << achievementFraction << setw(12) 
				 << g->getGamerscoreFor(playerID) << "pts" << setw(24) << g->getIGN(playerID) << "\n\n";
		}
	}

	if (friends.size() < 1) cout << "No friends found for this player" << endl;
	else
	{
		cout << "\n\n" << setw(16) << "Friend" << setw(17) << "Gamerscore" << endl;
		cout << setw(33) << "---------------------------------" << endl;
	
		for (unsigned int i = 0; i < friends.size(); i++)
		{
			Player* f = getPlayer(friends.at(i));
			cout << setw(16) << f->getName() << setw(14) << f->getGamerscore() << "pts" << endl;				 
		}
	}
	cout << endl;

}
void Database::SummarizeGame (int gameID)
{ // Print a record of all players who play the specified game and the number of times each of its achievements have been accomplished.
	Game* g = getGame(gameID);

	if (g != NULL)
	{
		cout << "\n\n";
		g->print();
		map<int, string> gameIGNs = g->getIGNs();
		if (gameIGNs.size() < 1) cout << "No players found for this game\n";
		else
		{
			cout << "\n\nPlayers for this game\n" << "---------------------\n";
			for (map<int, string>::iterator it = gameIGNs.begin(); it != gameIGNs.end(); it++)
			{
				Player* p = getPlayer(((*it).first));
				p->print();
			}
		}

		vector<Achievement*> achievements = g->getAchievements();
		if (achievements.size() < 1) cout << "\nNo achievements found for this game\n";
		else
		{
			cout << "\n\n" << setw(20) << "Achievement" << setw(14) << "# Achievers\n";
			cout << setw(34) << "----------------------------------\n";
			
			for (vector<Achievement*>::iterator it = achievements.begin(); it != achievements.end(); it++)
				cout << setw(20) << (*it)->getName() << setw(14) << (*it)->getNumAchievers() << endl;
	
		}
	}
	cout << "\n\n";
}
void Database::SummarizeAchievement (int gameID, int achievementID)
{ // Print a list of all players who have achieved an achievement, and the percentage of players who play that game who have the achievement.
	Game* g = getGame(gameID);
	if (g != NULL)
	{
		Achievement* a = g->getAchievement(achievementID);
		if (a != NULL)
		{
			cout << "\n\n";
			a->print();
			int numAchievers = a->getNumAchievers();
			int numGamePlayers = g->getNumPlayers();
			float percentage = 100.0f * numAchievers / numGamePlayers;
			cout << setprecision(3) << percentage << "% of players have earned this";

			cout << "\n\nPlayers that have earned this\n-----------------------------\n";
			vector<int> players = a->getAchievers();
			for (int i = 0; i < numAchievers; i++)
			{
				Player* p = getPlayer(players.at(i));
				p->print();
			}
		}
		cout << endl;
	}
}
void Database::AchievementRanking()
{ // Print a summary ranking all players by their total number of gamer points.
	cout << "Ranking of Gamerscores:\n\n" << setw(20) << "Player" << setw(15) << "Score" << endl;
	sortPlayers();

	for (vector<Player*>::iterator it = _players.begin(); it != _players.end(); it++)
		cout << setw(20) << (*it)->getName() << setw(15) << (*it)->getGamerscore() << endl;
}
void Database::sortPlayers()
{ // sort the array of player ID's by their gamerscores (high to low)
	for (unsigned int i = 1; i < _players.size(); i++)
	{
		int j = i;
	    while (j > 0 && _players.at(j - 1)->getGamerscore() < _players.at(j)->getGamerscore())
		{
			Player* temp = _players.at(j);
			_players[j] = _players[j - 1];
			_players[j - 1] = temp;
			j--;
		}
	}
}