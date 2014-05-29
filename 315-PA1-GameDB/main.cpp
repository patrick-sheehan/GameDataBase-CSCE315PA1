#include "Database.h"

#include <iostream>

int main()
{
	Database db;
	db.AddPlayer(1, "patrick");
	db.AddPlayer(2, "tyge");
	db.AddPlayer(3, "evan");

	db.AddGame(11, "Rainbow Six");
	db.AddGame(22, "Gears of War");
	db.AddGame(33, "NBA");

	db.AddAchievement(11, 999, "r6a1", 50);

	db.getPlayer(1)->print();


}