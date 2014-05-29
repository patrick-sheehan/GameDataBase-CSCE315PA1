/* 
	Patrick Sheehan
	CSCE 315 - PA1
	27 January 2013
*/
#include <iostream>
#include "Database.h"

void populate(Database*);

int main()
{
	Database* db = new Database();
	populate(db);
	db->listenForInput();
	return 0;
}
void populate(Database* db)
{
	db->AddPlayer(1, "patrick");
	db->AddPlayer(4, "tyge");
	db->AddPlayer(6, "evan");
	db->AddPlayer(23, "jake");
	db->AddPlayer(12, "drew");
	db->AddPlayer(9, "hank");

	db->AddGame(4, "tetris");
	db->AddGame(7, "pacman");
	db->AddGame(32, "chess");
	db->AddGame(11, "monopoly");
	db->AddGame(98, "catan");

	db->AddAchievement(4, 12, "four lines", 10);
	db->AddAchievement(4, 5, "t-spin", 100);
	db->AddAchievement(32, 45, "check mate", 250);
	db->AddAchievement(32, 87, "castle", 15);
	db->AddAchievement(11, 178, "boardwalk", 90);
	db->AddAchievement(11, 567, "free parking", 215);

	db->Plays(1, 4, "ign for tetris, patrick");
	db->Plays(4, 4, "tetris, tyge");
	db->Plays(6, 4, "evan ign for tetris");
	db->Plays(1, 98, "patrick_catan_ign");
	db->Plays(6, 98, "catanTyge");

	db->AddFriends(1, 4);
	db->AddFriends(1, 6);
	db->AddFriends(1, 23);
	db->AddFriends(6, 4);

	db->Achieve(1, 4, 12);
	db->Achieve(4, 4, 12);
	db->Achieve(4, 4, 5);
	db->Achieve(1, 32, 45);
	db->Achieve(4, 32, 45);
}