#include"Treasure.h"
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<cassert>

Treasure::Treasure() {

	
	level=percent=rowCoord = colCoord = taken=0;
	type = SWORD;
}

void Treasure::printInfo() {  // изкарва информацията за предмета който се намира в съкровището

	switch (type) {

	case SWORD:
		std::cout << " Sword level " << getLevel() << '\n';
		std::cout << " Physical attack + " << getPercent() << "%" << '\n';
		break;
	case ARMOR:
		std::cout << " Armor level " << getLevel() << '\n';
		std::cout << " Enemy attack - " << getPercent() << "%" << '\n';
		break;
	case SPELL:
		std::cout << " Spell level " << getLevel() << '\n';
		std::cout << " Spell attack + " << getPercent() << "%" << '\n';
		break;
	}
}

bool Treasure::getTaken() {

	return taken;
}


int Treasure::getLevel() {

	return level;
}

int Treasure::getPercent() {

	return percent;
}

size_t Treasure::getRowCoord() {

	return rowCoord;
}

size_t Treasure::getColCoord() {

	return colCoord;
}

Item Treasure::getType() {

	return type;
}

void Treasure::setPercent(int prcnt) {

	assert(prcnt > 0 && prcnt < 100);
	percent = prcnt;
}

void Treasure::setTaken(bool tkn) {

	taken = tkn;
}

void Treasure::setLevel(int lvl) {

	assert(lvl > 0 && lvl < 10);
	level = lvl;
}

void Treasure::setRow(int row) {

	assert(row >= 0 && row < 150);
	rowCoord = row;
}

void Treasure::setCol(int col) {

	assert(col >= 0 && col < 200);
	colCoord = col;
}

void Treasure::readFromFile(int i) { // съкровището прочита информация за предмета който съдържа от файл

	std::ifstream in;
	int itemlevel, spellpercent,swordpercent,armorpercent;
	char newline[256];
	in.open("items.txt");
	if (in) {   // отваряме файла
		
		in.getline(newline, 255); // игнорираме първия ред
		in >> itemlevel >> swordpercent >> spellpercent >> armorpercent; // запазваме информацията от втория
	}
	else {
		std::cout << "Items file didn't open. ";
	}
	in.close();
	setLevel(itemlevel);
	srand((unsigned)time(0)+i);  // използваме променливата i защото без нея всички съкровища се инициализират с еднакви предмети
	int itemtype = (rand() % 3) + 1; // избираме произволен предмет
	switch (itemtype) {
		case 1: // съкровишето съдържа меч, който добавя % към физическата атака на героя
			this->type = SWORD;
			setPercent(swordpercent);
			break;
		case 2:  // броня, която намалява чуждата атака с определен процент
			this->type = ARMOR;
			setPercent(armorpercent);
			break;
		case 3: // заклинание, което добавя % кум магическата атака на героя
			this->type = SPELL;
			setPercent(spellpercent);
			break;
		}
}

