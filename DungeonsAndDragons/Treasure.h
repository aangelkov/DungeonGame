#pragma once


enum Item {
	SWORD, ARMOR, SPELL
};

class Treasure {

private:
	bool taken;
	int level;
	size_t rowCoord;
	size_t colCoord;
	Item type;
	int percent;
	void readFromFile(int);
	Item getType();
	void setRow(int);
	void setCol(int);
	void setTaken(bool);
	void setPercent(int);
	void setLevel(int);
	void printInfo();

public:
	Treasure();
	friend class Game;
	friend class Map;
	int getLevel();
	bool getTaken();
	size_t getRowCoord();
	size_t getColCoord();
	int getPercent();

};