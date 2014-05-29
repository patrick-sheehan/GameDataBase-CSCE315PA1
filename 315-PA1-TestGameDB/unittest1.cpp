#include "stdafx.h"

#include "Database.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace My315PA1TestGameDB
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		Database db;
		TEST_METHOD(TestResourceFunctions)
		{
			string s = "123";
			int i = 789;
			Assert::AreEqual(123, stringToInt(s));
			Assert::AreEqual((string)"789", intToString(i));
			Assert::AreEqual((string)"hello", toLower("HeLlO"));
		}
		TEST_METHOD(TestAchievement)
		{
			Achievement* a = new Achievement(1,22,"AchieveName",44);
			Assert::AreEqual(1, a->getGameID());
			Assert::AreEqual(22, a->getID());
			Assert::AreEqual((string)"AchieveName",  a->getName());
			Assert::AreEqual(44, a->getPoints());

			Assert::AreNotEqual(765, a->getGameID());
			Assert::AreNotEqual(987, a->getID());
			Assert::AreNotEqual((string)"WrongName",  a->getName());
			Assert::AreNotEqual(678, a->getPoints());
		}
		TEST_METHOD(TestGame)
		{
			Game* g = new Game(34, "GameName");
			Assert::AreEqual(34, g->getID());
			Assert::AreEqual((string)"GameName", g->getName());

			Assert::AreNotEqual(3, g->getID());
			Assert::AreNotEqual((string)"WrongGame", g->getName());
		}
		TEST_METHOD(TestGameAddAchievement)
		{
			Game* g = new Game(34, "GameName");
			g->addAchievement(56, "a123", 99);
			g->addAchievement(78, "b456", 777);
			g->addAchievement(90, "c789", 12345);

			Achievement* a1 = g->getAchievement(56);
			Achievement* a2 = g->getAchievement(78);
			Achievement* a3 = g->getAchievement(90);

			Assert::AreEqual(a1->getPoints(), 99);
		}
		TEST_METHOD(TestAddPlayer)
		{
			db.AddPlayer(123, "Patrick");
			Player* p = db.getPlayer(123);
			Assert::AreEqual(123, p->getID());
			Assert::AreEqual((string)"Patrick", p->getName());			
		}
		TEST_METHOD(TestAddGame)
		{
			db.AddGame(456, "tetris");
			Game* g = db.getGame(456);
			Assert::AreEqual(456, g->getID());
			Assert::AreEqual((string)"tetris", g->getName());
		}
		TEST_METHOD(TestPlays)
		{
			db.AddPlayer(123, "Patrick");
			db.AddGame(789, "tetris");
			db.Plays(123, 789, "tetris_master");
			Game* g = db.getGame(789);

			string IGN = g->getIGN(123);
			Assert::AreEqual((string)"tetris_master", IGN);
		}
		TEST_METHOD(TestAddFriends)
		{
			db.AddPlayer(123, "patrick");
			db.AddPlayer(456, "tyge");
			db.AddPlayer(789, "evan");
			db.AddFriends(123, 456);
			
			Player* p = db.getPlayer(123);
			Player* t = db.getPlayer(456);
			Player* e = db.getPlayer(789);

			Assert::IsTrue(p->isFriendsWith(456));
			Assert::IsFalse(p->isFriendsWith(789));
		}
		TEST_METHOD(TestAchieve)
		{
			db.AddPlayer(1, "patrick");
			db.AddGame(2, "tetris");
			db.AddAchievement(2, 3, "all lines", 30);
			db.AddAchievement(2, 4, "t-spin", 100);
			db.Achieve(1, 2, 3);
			
			Player* p = db.getPlayer(1);
			Game* g = db.getGame(2);
			Achievement* a1 = g->getAchievement(3);
			Achievement* a2 = g->getAchievement(4);

			Assert::IsTrue(a1->isAchievedBy(1));
			Assert::IsFalse(a2->isAchievedBy(1));
		}
	};
}