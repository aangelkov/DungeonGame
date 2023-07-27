#include"Map.h"
#include"Treasure.h"
#include<fstream>
#include<iomanip>
#include"conio.h"
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<assert.h>


Map::Map() {

	level = treasureCount = monsterCount = width = length = 0;
	treasures = nullptr;
	map = nullptr;
}
Map::~Map() {

	for (size_t i = 0; i < width; ++i) {
		delete[] map[i];
	}
	delete[]map;
	delete[]treasures;
}

Map::Map(const Map& other)
{
	this->level = other.level;
	this->width = other.width;
	this->length = other.length;
	this->treasureCount = other.treasureCount;
	this->monsterCount = other.monsterCount;
	for (size_t i = 0; i < this->width; ++i) {
		delete[] map[i];
	}
	delete[]map;
	this->map = new char*[other.width];
	for (int i = 0; i < other.width; ++i) {
		map[i] = new char[other.length];
	}
	for (int i = 0; i < other.width; ++i) {
		for (int j = 0; j < other.length; ++j) {
			this->map[i][j] = other.map[i][j];
		}
	}
	delete[]treasures;
	treasures = new Treasure[other.treasureCount];
	for (int i = 0; i < other.treasureCount; ++i) {
		treasures[i] = other.treasures[i];
	}
}

void Map::deleteMap() {   // метод който трие само матрицата от обекта карта
	if (map != nullptr) {

		for (size_t i = 0; i < width; ++i) {
			delete[] map[i];
		}
		delete[]map;
	}
}

size_t Map::getLevel() {

	return level;
}

size_t Map::getWidth() {

	return width;
}

size_t Map::getLength() {

	return length;
}

size_t Map::getTreasureCount() {

	return treasureCount;
}

size_t Map::getMonsterCount() {

	return monsterCount;
}

Treasure& Map::getTreasure(int i) {

	assert(i >= 0 && i < getTreasureCount());
	return treasures[i];
}

void Map::setLevel(size_t lvl) {
	assert(lvl > 0 && lvl < 20);
	level = lvl;
}

void Map::setLength(size_t len) {
	assert(len > 0 && len < 200);
	length = len;
}

void Map::setWidth(size_t wdth) {
	assert(wdth > 0 && wdth < 150);
	width = wdth;
}

void Map::setMonsterCount(size_t monsters) {
	assert(monsters > 0 && monsters < 30);
	monsterCount = monsters;
}
void Map::setTreasureCount(size_t treasures) {
	assert(treasures > 0 && treasures < 30);
	treasureCount = treasures;
}

void Map::readFile() {  // картата прочита информацията от файл

	char newLine[256];
	std::ifstream in;
	in.open("maps.txt"); // отваряме файла
	if (in) {

		in.getline(newLine, 255); // игнорираме първия ред
		in >> *this;              // записваме информацията от втория. 
	}
	else {
		std::cout << "Maps file didn't open.";
	}
	in.close();  // затваряме файла
}

void Map::updateMapsFile() { // обновяване на информацията на файла, който съдържа данни за картата

	size_t level1, level2, width1, width2, length1, length2, treasureCount1, treasureCount2, monsterCount1, monsterCount2;
	std::ifstream in;
	in.open("maps.txt");  // отваряме файла
	char newLine[256];     
	if (in) {

		in.getline(newLine,255); // игнорираме първия ред
		in >> level1 >> width1 >> length1 >> treasureCount1 >> monsterCount1; // записваме втория ред, той пази информация за n-level карта
		in >> level2 >> width2 >> length2 >> treasureCount2 >> monsterCount2; // записваме третия ред, той пази информация за (n+1)-level карта
	}
	else {
		std::cout << "Maps file didn't open.";
	}
	in.close(); // затваряме файла

	std::ofstream out;
	out.open("maps.txt");
	if (out) {  // отваряме файла

		out << "Level: Width: Length: Treasures: Monsters:" << '\n'; // записваме първия ред
		out << std::setw(5) << level2 << std::setw(7) << width2 << std::setw(8) << length2 << std::setw(11) << treasureCount2 << std::setw(10) << monsterCount2 << '\n'; // информацията за (n+1)-level карта пишем на втори ред
		level1 += 2;
		width1 += width2;
		length1 += length2;
		treasureCount1 += treasureCount2;  // пресмятаме информацията за (n+2)-level карта
		monsterCount1 += monsterCount2;
		out << std::setw(5) << level1 << std::setw(7) << width1 << std::setw(8) << length1 << std::setw(11) << treasureCount1 << std::setw(10) << monsterCount1 << '\n'; // информацията за (n+2)-level карта пишем на трети ред
	}
	else {

		std::cout << "Maps file didn't open.";
	}
	out.close();  // затваряме файла
}

void Map::updateItemsFile() { // обновяване на файла който пази информацията за предметите от съкровища

	size_t currentLevel, currentSword, currentSpell, currentArmor;
	std::ifstream in;
	in.open("items.txt");  // отваряме файла
	if (in) {

		char newLine[256];
		in.getline(newLine,255); // игнорираме първия ред
		in >> currentLevel >> currentSword >> currentSpell >> currentArmor; // прочитаме втория
	}
	else {

		std::cout << "Items file didn't open.";
	}
	in.close(); // затваряме файла

	currentLevel++;
	currentArmor += 5;
	currentSword += 5;  // обновяваме данните прочетени от втория ред
	currentSpell += 5;

	std::ofstream out; 
	out.open("items.txt"); // отваряме файла
	if (out) {

		out << "Item Level: Sword: Spell: Armor:" << '\n'; // въвеждаме първия ред
		out << std::setw(10) << currentLevel << std::setw(7) << currentSword << std::setw(7) << currentSpell << std::setw(7) << currentArmor << '\n'; // въвеждаме обновените данни на втори ред
	}
	else {

		std::cout << "Items file didn't open.";
	}
	out.close(); // затваряме файла
}

std::istream& operator>>(std::istream& in, Map& map) { // оператор за прочитане на ред от файла за карта

	size_t leveltemp, widthtemp, lengthtemp, treasuretemp, monstertemp;
	in >> leveltemp >> widthtemp >> lengthtemp >> treasuretemp >> monstertemp;
	map.setLevel(leveltemp);
	map.setWidth(widthtemp);
	map.setLength(lengthtemp);
	map.setTreasureCount(treasuretemp);
	map.setMonsterCount(monstertemp);
	return in;
}

std::ostream& operator<<(std::ostream& out, Map& map) {

	out << std::setw(5) << map.getLevel() << std::setw(7) << map.getWidth() << std::setw(8) << map.getLength() << std::setw(11) << map.getTreasureCount() << std::setw(10) << map.getMonsterCount() << '\n';
	return out;
}

void Map::createPaths() {  // създаване на пътища в картата

	int direction, previousDirection = 6;
	srand((unsigned)time(0));

	for (int i = 0; i < level + 1; ++i) {  // правим толкова пътища, колкото е нивото на картата плюс едно

		int currentRow = 0, currentCollum = 0;  // всеки път започва от началото на картата

		while (map[width - 1][length - 1] == '#') {  // докато краят на картата не е празно поле


			do {
				direction = (rand() % 3) + 1;  // избираме произволна посока(нагоре,надолу,надясно) в която да се движи пътя 
			} 			while (abs(direction - previousDirection) == 2); // избраната посока не може да е срещуположна на предишната

			previousDirection = direction;

			int distance = (rand() % (width / 4)) + 1; // произволно избираме дистанция която да извървим в избраната посока, дистанцията зависи от големината на картата

			switch (direction) {

			case 1: // посока нагоре
				if (currentRow - distance >= 0) { // проверка дали можем да извървим съответната дистанция в съответната посока спрямо границите на картата
					                                                                                                  // и края на пътя
					for (int j = 0; j < distance; ++j) {

						map[currentRow][currentCollum] = '.';  // ако можем, там откъдето минава пътя отбелязваме на картата като празно поле
						currentRow--;                          // и обновяваме къде свършва пътя
					}
				}
				break;
			case 2:   // посока надясно
				if (currentCollum + distance <= length - 1) {

					for (int j = 0; j < distance; ++j) {

						map[currentRow][currentCollum] = '.';
						currentCollum++;
					}
				}
				break;
			case 3:   // посока надолу
				if (currentRow + distance <= width - 1) {

					for (int j = 0; j < distance; ++j) {

						map[currentRow][currentCollum] = '.';
						currentRow++;
					}
				}
				break;
			}
		}
		map[width - 1][length - 1] = '#'; // след като пътя е стигнал до края на картата, отбелязваме долния десен ъгъл(края) като стена, за да можем да пуснем 
	}                                                                          // следващ път
	map[width - 1][length - 1] = '.';       // след като сме пуснали всички пътища отбелязваме края на картата като празно поле
	map[0][0] = 'X';                        // отбелязваме началото на картата като позция на героя
}

void Map::populateMapMonsters() {   // поставяне на чудовища по картата

	int monstersLeft = monsterCount;
	srand((unsigned)time(0));

	do {

		int randomRow = (rand() % width) ;
		int randomCol = (rand() % length) ;    
		int randomDirection = (rand() % 4) + 1; // избираме произволна позиция на картата и произволна посока 
		
		switch (randomDirection) {

		case 1: // ако посоката е надясно
		{
			int goRight = randomCol;
			while (goRight < length) {  // движим се надясно  докато не стигнем ръба на картата или празно поле

				if (map[randomRow][goRight] == '.') {
					map[randomRow][goRight] = 'M'; // първото празно поле отбелязваме като поле с чудовище
					monstersLeft--;    // намаляме броя чудовища след като сме поставили на картата
					break;
				}
				goRight++;
			}
			break;
		}
		case 2:    // посока наляво
		{
			int goLeft = randomCol;
			while (goLeft >= 0) {

				if (map[randomRow][goLeft] == '.') {
					map[randomRow][goLeft] = 'M';
					monstersLeft--;
					break;
				}
				goLeft--;
			}
			break;
		}
		case 3:    // посока нагоре
		{
			int goUp = randomRow;
			while (goUp >= 0) {

				if (map[goUp][randomCol] == '.') {
					map[goUp][randomCol] = 'M';
					monstersLeft--;
					break;
				}
				goUp--;
			}
			break;
		}
		case 4:    // посока надолу
		{
			int goDown = randomRow;
			while (goDown < width) {

				if (map[goDown][randomCol] == '.') {
					map[goDown][randomCol] = 'M';
					monstersLeft--;
					break;
				}
				goDown++;
			}
			break;
		}
		}		
	} 	
	while (monstersLeft > 0);  // докато не поставим всички чудовища на картата
}

void Map::populateMapTreasures() {  // поставяне на съкровища по картата

	delete[]treasures; // трием предишния масив със съкровища
	treasures = new Treasure[treasureCount]; // създаваме нов, броя съкровища зависи от нивото на картата
	int treasuresLeft = treasureCount;
	for (int i = 0; i < treasureCount; i++) {
		treasures[i].readFromFile(i);  // всяко едно съкровище прочита информацията за предмета който съдържа от съответния файл
	}
	srand((unsigned)time(0));
	
	do {                                 // алгоритъмът за поставяне на съкровища по картата е аналогичен с този за чудовища
		int randomRow = (rand() % width);
		int randomCol = (rand() % length);
		int randomDirection = (rand() % 4) + 1;

		switch (randomDirection) {

		case 1:
		{
			int goRight = randomCol;
			while (goRight < length) {

				if (map[randomRow][goRight] == '.') {
					map[randomRow][goRight] = 'T';    // след като отбележим празно поле от картата като поле със съкровище
					treasuresLeft--;
					treasures[treasuresLeft].setRow(randomRow);
					treasures[treasuresLeft].setCol(goRight); // задаваме координати на съответното съкровище от масива, така всяко съкровище от масива отговаря на
					break;                                     // (Т) поле от картата 
				}
				goRight++;
			}
			break;
		}
		case 2:
		{
			int goLeft = randomCol;
			while (goLeft >= 0) {

				if (map[randomRow][goLeft] == '.') {
					map[randomRow][goLeft] = 'T';
					treasuresLeft--;
					treasures[treasuresLeft].setRow(randomRow);
					treasures[treasuresLeft].setCol(goLeft);
					break;
				}
				goLeft--;
			}
			break;
		}
		case 3:
		{
			int goUp = randomRow;
			while (goUp >= 0) {

				if (map[goUp][randomCol] == '.') {
					map[goUp][randomCol] = 'T';
					treasuresLeft--;
					treasures[treasuresLeft].setRow(goUp);
					treasures[treasuresLeft].setCol(randomCol);
					break;
				}
				goUp--;
			}
			break;
		}
		case 4:
		{
			int goDown = randomRow;
			while (goDown < width) {

				if (map[goDown][randomCol] == '.') {
					map[goDown][randomCol] = 'T';
					treasuresLeft--;
					treasures[treasuresLeft].setRow(goDown);
					treasures[treasuresLeft].setCol(randomCol);
					break;
				}
				goDown++;
			}
			break;
		}
		}
	} 	
	while (treasuresLeft > 0);
}

void Map::createMap(){

	map = new char* [width];
	for (int i = 0; i < width; ++i) {

		map[i] = new char[length];     // създаваме масив от символи
	}
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < length; ++j) {    // инициализираме всички полета от картата като стени (#)
			map[i][j] = '#';
		}
	}
    
	createPaths();  // създаваме пътеки от празни полета по които героят може да се движи
	populateMapMonsters(); // поставяме чудовища по празните полета
	populateMapTreasures(); // поставяме съкровища по празните полета
}

void Map::printMap(){

	std::cout << '\n';
	for (int i = 0; i < length + 2; ++i) {
		std::cout << '_';
	}
	std::cout << '\n';
	for (size_t i = 0; i < width; ++i) {

		std::cout << '|';
		for (size_t j = 0; j < length; ++j) {
			
			std::cout << map[i][j];
		}
		std::cout << '|'<<'\n';
	}
	for (int i = 0; i < length + 2; ++i) {
		std::cout << '_';
	}
	std::cout << '\n';
}

void Map::resetMapsFile() {  // Задаваме начални стойности във файла с информация за картата

	std::ofstream out;
	out.open("maps.txt");
	if (out) {

		out << "Level: Width: Length: Treasures: Monsters:" << '\n';
		out << std::setw(5) << 1 << std::setw(7) << 10 << std::setw(8) << 10 << std::setw(11) << 2 << std::setw(10) << 2 << '\n'; // втория ред съдържа информация за карта първо ниво
		out << std::setw(5) << 2 << std::setw(7) << 10 << std::setw(8) << 15 << std::setw(11) << 2 << std::setw(10) << 3 << '\n'; // третия - за карта второ ниво

	}
	out.close();
}

void Map::resetItemsFile() { // Задаваме начални стойности във файла с информация за предметите от съкровища

	std::ofstream out;
	out.open("items.txt");
	if (out) {

		out << "Item Level: Sword: Spell: Armor:" << '\n';
		out << std::setw(10) << 1 << std::setw(7) << 25 << std::setw(7) << 25 << std::setw(7) << 20 << '\n'; // втория ред съдържа информация за предмети
	}                                                                                    // които могат да се вземат от съкровище от първо ниво карта
	else {

		std::cout << "Items file didn't open.";
	}
	out.close();
}

char Map::getPosition(int row, int col) {  // връща какво се намира на съответните координати върху картата

	assert(row >= 0 && row < width && col >= 0 && col < length); 

	return map[row][col];

}

void Map::setPosition(int row, int col, char element) {  // задава какво да се намира на съответните координати върху картата

	assert (row >= 0 && row < width && col >= 0 && col < length);
	map[row][col] = element;
}