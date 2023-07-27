#pragma once
#include"Map.h"
#include"Hero.h"
#include"Monster.h"
#include"Treasure.h"

class Game {

private:

	void play(Hero& hero, Map& map);
	bool fightMonster(Hero&,int);
	void newGame();
	void loadGame();
	void printFightScreen(Hero& hero, Monster& monster);
	void printTreasureScreen(Hero& hero, Treasure& treasure);
	void stepOnMonster(Hero& hero,Map& map,int,int);
	void stepOnEmptyField(Hero& hero,Map& map,int,int);
	void stepOnTreasure(Hero& hero,Map& map,int,int);
	void printLevelUpScreen(Hero& hero);
	void nextMove(Hero& hero,Map& map, int,int);
	bool monsterAttacksFirst(Hero& hero,Monster monster);
	bool heroAttacksFirst(Hero& hero,Monster monster);
public:

	void menu();
};
