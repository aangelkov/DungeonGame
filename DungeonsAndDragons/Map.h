#pragma once
#include"Treasure.h"
#include<iostream>

class Map {

private:

	size_t level;
	size_t length; // == map collums
	size_t width;  // == map rows
	size_t treasureCount;
	size_t monsterCount;
	char** map;
	Treasure* treasures;
	void readFile();
	void updateMapsFile();
	void updateItemsFile();
	void createPaths();
	void populateMapMonsters();
	void populateMapTreasures();

	void setLevel(size_t);
	void setWidth(size_t);
	void setLength(size_t);
	void setMonsterCount(size_t);
	void setTreasureCount(size_t);
	friend std::istream& operator>>(std::istream& in, Map& map);
	friend std::ostream& operator<<(std::ostream& out, Map& map);
	void createMap();
	void printMap();
	void resetMapsFile();
	void resetItemsFile();
	void setPosition(int, int, char);
	Treasure& getTreasure(int);
public:
	Map();
	~Map();
	Map(const Map& other);
	void deleteMap();
	friend class Game;
	size_t getLevel();
	size_t getLength();
	size_t getWidth();
	size_t getTreasureCount();
	size_t getMonsterCount();
	char getPosition(int, int);

};


