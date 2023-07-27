#include"Game.h"
#include"conio.h"
#include<iostream>
#include<iomanip>


void Game::menu() {

	std::cout << " ~DUNGEONS AND DRAGONS~ " << '\n';  // Изкарваме главното меню на екрана с опция за нова игра, зареждане на предишната игра и изход. 
	std::cout << '\n';
	std::cout << " Press 'N' to start New Game " << '\n';  
	std::cout << " Press 'L' to Load previous game " << '\n';
	std::cout << " Press 'X' to Exit " << '\n';
	std::cout << '\n';
	std::cout << " Use the WASD keys to move." << '\n';
	std::cout << " Make sure your keyboard is set to English/United States and Caps Lock is turned off" << '\n';
    
	char command;
	do {
		command = _getch();
	}     while (command != 'n' && command != 'l' && command != 'x'); // Взимаме избора на потребителя

	switch (command) {

	case 'n': newGame(); // n - стартиране на нова игра
		break;

	case 'l': loadGame(); // l - зареждане на предишна игра
		break;

	case 'x': // x - изход от приложението
		return;
	}
}

void Game::newGame() { // нова игра

    Hero hero;  
 	Map map;        // инициализираме картата и героят
	system("CLS");
	hero.chooseRace();      // потребителят избира расата на героя - човек, войн или магьосник.  
	hero.updateStatsFile();  // обновяваме файлът който съхранява характеристиките на героя с текущите му параметри
	system("CLS");
	map.resetMapsFile();   // въвеждаме началните стойности във файлът, който съхранява информацията за картата
	map.resetItemsFile();  // въвеждаме началните стойности във файлът, който съхранява информацията за предметите които се падат от съкровища
	map.readFile();        // картата прочита информацията от файлът
	map.createMap();       // картата се създава с данните прочетени от файла
	map.printMap();        
	play(hero, map);    // игра с новосъздаденият герой на новосъздадената карта

}

void Game::loadGame() {

	Hero hero;  
	Map map;      // инициализиране на героят и картата
	system("CLS");
	hero.loadPrevious();  // героят прочита информацията от файла, който съхранява параметрите на героя от предишната игра
	system("CLS");
	map.readFile();  // картата прочита информацията от файла, който съхранява параметрите на картата от последната игра
	map.createMap();  // картата се създава с тези параметри
	map.printMap();
	play(hero, map);  // игра с новосъздадените герой и карта, които имат същите параметри като тези от предишната игра
}

void Game::play(Hero& hero, Map& map) {
	while (hero.getHealth() > 0) {   // докато героят има живот, взимаме команда от потребителя с която го движим по картата

		char command = _getch();
		switch (command) {

		case 'w': // команда за местене на героя едно поле нагоре
		{
			if (hero.getRow() - 1 >= 0) {  // проверка за границите на картата

				if (map.getPosition(hero.getRow() - 1, hero.getCollum()) == '.') {

					stepOnEmptyField(hero, map, -1, 0);  // стъпване на празно поле
				}
				else if (map.getPosition(hero.getRow() - 1, hero.getCollum()) == 'M') {

					stepOnMonster(hero, map, -1, 0);   // стъпване на поле с чудовище
				}
				else if (map.getPosition(hero.getRow() - 1, hero.getCollum()) == 'T') {

					stepOnTreasure(hero, map, -1, 0);  // стъпване на поле със съкровище
				}
			}
			break;
		}

		case 'a':  // команда за местене едно поле наляво
		{
			if (hero.getCollum() - 1 >= 0) {  // проверка за границите на картата

				if (map.getPosition(hero.getRow(), hero.getCollum() - 1) == '.') {

					stepOnEmptyField(hero, map, 0, -1);
				}
				else if (map.getPosition(hero.getRow(), hero.getCollum() - 1) == 'M') {

					stepOnMonster(hero, map, 0, -1);
				}
				else if (map.getPosition(hero.getRow() , hero.getCollum() -1) == 'T') {

					stepOnTreasure(hero, map, 0, -1);
				}
			}
			break;
		}

		case 's':  // команда за местене едно поле надолу
		{
			if (hero.getRow() + 1 < map.getWidth()) {  // проверка за границите на картата

				if (map.getPosition(hero.getRow() + 1, hero.getCollum()) == '.') {

					stepOnEmptyField(hero, map, 1, 0);
				}
				else if (map.getPosition(hero.getRow() + 1, hero.getCollum()) == 'M') {

					stepOnMonster(hero, map, 1, 0);
				}
				else if (map.getPosition(hero.getRow() + 1, hero.getCollum()) == 'T') {

					stepOnTreasure(hero, map, 1, 0);
				}
			}
			break;
		}

		case 'd':  // команда за местене едно поле надясно
		{
			if (hero.getCollum() + 1 < map.getLength()) { // проверка за границите на картата

				if (map.getPosition(hero.getRow(), hero.getCollum() + 1) == '.') {

					stepOnEmptyField(hero, map, 0, 1);
				}
				else if (map.getPosition(hero.getRow(), hero.getCollum() + 1) == 'M') {

					stepOnMonster(hero, map, 0, 1);
				}
				else if (map.getPosition(hero.getRow() , hero.getCollum() + 1) == 'T') {

					stepOnTreasure(hero, map, 0, 1);
				}
			}
			break;
		}
	  }
		if (hero.getRow() == map.getWidth() - 1 && hero.getCollum() == map.getLength() - 1) { // ако героят е достигнал края на картата (долен десен ъгъл)
			
			
			printLevelUpScreen(hero);  // героят вдига ниво
			hero.updateStatsFile();    // обновяваме файлът който съхранява параметрите на героя с новите величини 
			map.deleteMap();           // трием картата
			map.updateItemsFile();    // обновяваме файлът който съдържа информация за предметите които се взимат от съкровища
			map.updateMapsFile();     // обновяваме файлът който съдържа информация за картата
			map.readFile();           // картата прочита информацията от файла
			map.createMap();          // картата се създава с обновената информация
			hero.setRow(0);
			hero.setCollum(0);        // преместваме героя на начална позиция (горен ляв ъгъл)
			map.printMap();
		}
	}

}

bool Game::fightMonster(Hero& hero, int monsterLevel) { // битка с чудовище, метода връща true при победа и false при загуба

	char command;
	system("CLS");
	Monster monster(monsterLevel);  // инициализираме чудовище със съответното ниво
	srand((unsigned)time(0));
	size_t first = rand() % 2;      // избираме кой атакува първи
	printFightScreen(hero,monster);
	std::cout << '\n' << " Press any key to begin fight." << '\n';
	command = _getch();
	if (first == 0) {
		return heroAttacksFirst(hero, monster);  // героят атакува първи
}
	else {
		return monsterAttacksFirst(hero, monster); // чудовището атакува първо
	}	
}

bool Game::heroAttacksFirst(Hero& hero, Monster monster) {  // битка в случай че героят е първи
	
	char command;
	int heroWeaponAttack = hero.getStrength() + ((hero.getStrength() * hero.getWeapon()) / 100);
	int heroSpellAttack = hero.getMana() + ((hero.getMana() * hero.getSpell()) / 100);         // изчисляваме силата на двата типа атака на героя
	while (hero.getHealth() > 0 && monster.getHealth() > 0) {                            // докато героят и чудовището имат живот

		system("CLS");
		printFightScreen(hero, monster);
		std::cout << '\n' << " Press 'A' to use physical attack, press 'S' to use spell." << '\n';  
		do {
			command = _getch();
		} while (command != 's' && command != 'a'); // потребителят избира как да атакува
		if (command == 'a') {
			monster.setHealth(monster.getHealth() - heroWeaponAttack + (heroWeaponAttack * monster.getArmorPercent() / 100)); // физическа атака
		}
		else {
			monster.setHealth(monster.getHealth() - heroSpellAttack + (heroSpellAttack * monster.getArmorPercent() / 100));  // атака с магия
		}
		system("CLS");
		if (monster.getHealth() <= 0) {   
			system("CLS");
			return true;     // ако чудовището няма живот сме победили и връщаме true
		}
		printFightScreen(hero, monster);
		std::cout << '\n' << " Monster's turn, press any key. " << '\n';
		command = _getch();
		int monsterAttack = rand() % 2;   // избор за атаката на чудовището
		if (monsterAttack == 0) {
			hero.setHealth(hero.getHealth() - monster.getStrength() + (monster.getStrength() * hero.getArmor() / 100)); // физическа атака
		}
		else {
			hero.setHealth(hero.getHealth() - monster.getMana() + (monster.getMana() * hero.getArmor() / 100));   // атака с магия
		}
		if (hero.getHealth() <= 0) {  // ако героят няма живот сме загубили и връщаме false
			system("CLS");
			return false;
		}
	}
}

bool Game::monsterAttacksFirst(Hero& hero, Monster monster) {  // битка в случай че чудовището атакува първо

	char command;
	int heroWeaponAttack = hero.getStrength() + ((hero.getStrength() * hero.getWeapon()) / 100);
	int heroSpellAttack = hero.getMana() + ((hero.getMana() * hero.getSpell()) / 100);           // изчисляваме двата типа атака на героя
	while (hero.getHealth() > 0 && monster.getHealth() > 0) {                                // докато героят и чудовището имат живот

		system("CLS");
		printFightScreen(hero, monster);
		std::cout << '\n' << " Monster's turn, press any key. " << '\n';
		command = _getch();
		int monsterAttack = rand() % 2;       // избираме типа атака на чудовището
		if (monsterAttack == 0) {
			hero.setHealth(hero.getHealth() - monster.getStrength() + (monster.getStrength() * hero.getArmor() / 100));  // физическа атака
		}
		else {
			hero.setHealth(hero.getHealth() - monster.getMana() + (monster.getMana() * hero.getArmor() / 100)); // атака с магия
		}
		system("CLS");
		if (hero.getHealth() <= 0) {
			system("CLS");           // ако героят няма живот сме загубили и връщаме false
			return false;
		}
		printFightScreen(hero, monster);
		std::cout << '\n' << " Press 'A' to use physical attack, press 'S' to use spell." << '\n';
		do {
			command = _getch();
		} while (command != 's' && command != 'a');  // избор на потребителя за вида на атака която да осъществи
		if (command == 'a') {
			monster.setHealth(monster.getHealth() - heroWeaponAttack + (heroWeaponAttack * monster.getArmorPercent() / 100)); // физическа атака
		}
		else {
			monster.setHealth(monster.getHealth() - heroSpellAttack + (heroSpellAttack * monster.getArmorPercent() / 100));  // атака с магия
		}
		if (monster.getHealth() <= 0) {
			system("CLS");                // ако чудовището няма живот сме победили и връщаме true
			return true;
		}
	}
}


void Game::printFightScreen(Hero& hero, Monster& monster) {  // екран за битка с чудовише

	int heroWeaponAttack = hero.getStrength() + ((hero.getStrength() * hero.getWeapon()) / 100);
	int heroSpellAttack = hero.getMana() + ((hero.getMana() * hero.getSpell()) / 100);           // пресмятаме стойностите на двата вида атака на героя 
	std::cout << "     Your Hero  |  Monster level " << monster.getLevel() << '\n';           // принтираме екрана за битка с чудовище
	std::cout << " -----------------------------------" << '\n';
	std::cout << " Health: " << std::setw(5) << hero.getHealth() << "  |" << std::setw(10) << monster.getHealth() << '\n';
	std::cout << " Attack: " << std::setw(5) << heroWeaponAttack << "  |" << std::setw(10) << monster.getStrength() << '\n';
	std::cout << " Mana: " << std::setw(7) << heroSpellAttack << "  |" << std::setw(10) << monster.getMana() << '\n';
	std::cout << " Armor: " << std::setw(5) << hero.getArmor() << '%' << "  |" << std::setw(10) << monster.getArmorPercent() << '%' << '\n';
}

void Game::stepOnEmptyField(Hero& hero,Map&map,int updateRow,int updateCol) {  // стъпване на празно поле

	map.setPosition(hero.getRow(), hero.getCollum(), '.');  // старата позиция на героя отбелязваме на картата като празно поле
	hero.setRow(hero.getRow() + updateRow);
	hero.setCollum(hero.getCollum() + updateCol);     // обновяваме позицията на героя
	map.setPosition(hero.getRow(), hero.getCollum(), 'X');  // отбелязваме на картата новата позиция на героя
	system("CLS");
	map.printMap();
}

void Game::stepOnMonster(Hero& hero,Map& map,int updateRow,int updateCol) { // стъпване на поле с чудовище

	if (fightMonster(hero, map.getLevel())) {   // битка с чудовище, при победа
		map.setPosition(hero.getRow(), hero.getCollum(), '.');  // старата позиция на героя отбелязваме на картата като празно поле
		hero.setRow(hero.getRow() + updateRow);
		hero.setCollum(hero.getCollum() + updateCol);  // обновяваме позицията на героя
		map.setPosition(hero.getRow(), hero.getCollum(), 'X'); // отбелязваме на картата новата позиция на героя
		map.printMap();
		if (hero.getHealth() < hero.getFullHealth() / 2) {
			hero.setHealth(hero.getFullHealth() / 2);   // ако животът на героя е под половината, го възстановяваме наполовина
		}
	}
	else {
		std::cout << '\n' << " ~ G A M E  O V E R ~" << '\n';  // при загуба, изписваме надписа и приложението приключва, защото живота на героя е под нула и 
	}                                                          // while цикъла в  play() метода приключва 
}

void Game::stepOnTreasure(Hero& hero,Map& map,int updateRow,int updateCol) { // стъпване на поле със съковище

	for (int i = 0; i < map.getTreasureCount(); ++i) { // обхождаме масива със съкровища за да намерим това на което сме стъпили по координатите
		
		if (map.getTreasure(i).getRowCoord() == hero.getRow() + updateRow && map.getTreasure(i).getColCoord() == hero.getCollum() + updateCol) {

			printTreasureScreen(hero,map.getTreasure(i));  // изкарваме екрана за взимане на предмет от съкровище
			map.setPosition(hero.getRow(), hero.getCollum(), '.'); // отбелязваме предишната позиция на героя като празно поле на картата
			hero.setRow(hero.getRow() + updateRow);
			hero.setCollum(hero.getCollum() + updateCol);  // обновяваме позицията на героя
			map.setPosition(hero.getRow(), hero.getCollum(), 'X'); // отбелязваме на картата новата позиция на героя
			map.printMap();
			if (map.getTreasure(i).getTaken() == false) { // ако не сме взели предмета от съкровището, изпълняваме следващия ход на героя 
				                                           // чрез метода nextMove така, че старата му позиция да бъде отново (Т), а не (.)
				nextMove(hero, map, hero.getRow(),hero.getCollum());
			}
			break;
		}
	}
}

void Game::printTreasureScreen(Hero& hero, Treasure& treasure) { // изкарване на екран за стъпване върху съкровище

	char command='_';
	system("CLS");
	
	std::cout << " You found a Treasure! "<<'\n';
	std::cout << "----------------------- "<<'\n';
	treasure.printInfo();  // изкарване на характеристиките на предмета който се намира в съкровището
	std::cout << '\n';
	std::cout << " Your Inventory: " << '\n'; // изкарване на характеристиките на героя
	std::cout << " Armor: " << hero.getArmor()<<" %" << '\n';
	std::cout << " Sword: "<<hero.getWeapon()<<" %"<<'\n';
	std::cout << " Spell: " << hero.getSpell() <<" %"<< '\n';
	std::cout << " Press 'T' to take Item, press 'L' to leave item.";
	while (command != 't' && command != 'l') {
		command = _getch();          // избор на потребителя дали да вземе предмета или не
	}
	system("CLS");
	if (command == 't') {   // ако вземе предмета обновяваме характеристиките на героя спрямо взетия предмет
       
		switch (treasure.getType()) {
		case SWORD:
			hero.setWeapon(treasure.getPercent()); break;
		case ARMOR:
			hero.setArmor(treasure.getPercent()); break;
		case SPELL: 
			hero.setSpell(treasure.getPercent()); break;
		}
		treasure.setTaken(true);  // отбелязваме съкровището като взето
	}
}

void Game::nextMove(Hero& hero, Map& map, int currentRow, int currentCol) { // метод който реализира само едно преместване на героя и който изпълняваме
	                                                                   // само след като сме стъпили на съкровище и сме избрали да не вземем предмета от него
	char command = '_';
	while (hero.getRow() == currentRow && hero.getCollum() == currentCol) { // цикълът се върти докато не се променят координатите на героя

		command = _getch();
		switch (command) {

		case 'w':
		{
			if (hero.getRow() - 1 >= 0) {

				if (map.getPosition(hero.getRow() - 1, hero.getCollum()) == '.') {

					stepOnEmptyField(hero, map, -1, 0);
					map.setPosition(currentRow, currentCol, 'T'); // след успешно преместване на героя, старото поле на което е бил се отбелязва на картата
					system("CLS");                               // с (Т) защото не сме взели съкровището, но то не трябва да изчезва от картата и трябва 
					map.printMap();                               // отново да имаме възможност да стъпим на него
				}
				else if (map.getPosition(hero.getRow() - 1, hero.getCollum()) == 'M') {

					stepOnMonster(hero, map, -1, 0);
					map.setPosition(currentRow, currentCol, 'T');
					system("CLS");
					map.printMap();
				}
				else if (map.getPosition(hero.getRow() - 1, hero.getCollum()) == 'T') {

					stepOnTreasure(hero, map, -1, 0);
					map.setPosition(currentRow, currentCol, 'T');
					system("CLS");
					map.printMap();
				}
			}
			break;
		}

		case 'a':
		{
			if (hero.getCollum() - 1 >= 0) {

				if (map.getPosition(hero.getRow(), hero.getCollum() - 1) == '.') {

					stepOnEmptyField(hero, map, 0, -1);
					map.setPosition(currentRow, currentCol, 'T');
					system("CLS");
					map.printMap();
				}
				else if (map.getPosition(hero.getRow(), hero.getCollum() - 1) == 'M') {

					stepOnMonster(hero, map, 0, -1);
					map.setPosition(currentRow, currentCol, 'T');
					system("CLS");
					map.printMap();
				}
				else if (map.getPosition(hero.getRow(), hero.getCollum() - 1) == 'T') {

					stepOnTreasure(hero, map, 0, -1);
					map.setPosition(currentRow, currentCol, 'T');
					system("CLS");
					map.printMap();
				}
			}
			break;
		}

		case 's':
		{
			if (hero.getRow() + 1 < map.getWidth()) {

				if (map.getPosition(hero.getRow() + 1, hero.getCollum()) == '.') {

					stepOnEmptyField(hero, map, 1, 0);
					map.setPosition(currentRow, currentCol, 'T');
					system("CLS");
					map.printMap();
				}
				else if (map.getPosition(hero.getRow() + 1, hero.getCollum()) == 'M') {

					stepOnMonster(hero, map, 1, 0);
					map.setPosition(currentRow, currentCol, 'T');
					system("CLS");
					map.printMap();
				}
				else if (map.getPosition(hero.getRow() + 1, hero.getCollum()) == 'T') {

					stepOnTreasure(hero, map, 1, 0);
					map.setPosition(currentRow, currentCol, 'T');
					system("CLS");
					map.printMap();
				}
			}
			break;
		}

		case 'd':
		{
			if (hero.getCollum() + 1 < map.getLength()) {

				if (map.getPosition(hero.getRow(), hero.getCollum() + 1) == '.') {

					stepOnEmptyField(hero, map, 0, 1);
					map.setPosition(currentRow, currentCol, 'T');
					system("CLS");
					map.printMap();
				}
				else if (map.getPosition(hero.getRow(), hero.getCollum() + 1) == 'M') {

					stepOnMonster(hero, map, 0, 1);
					map.setPosition(currentRow, currentCol, 'T');
					system("CLS");
					map.printMap();
				}
				else if (map.getPosition(hero.getRow(), hero.getCollum() + 1) == 'T') {

					stepOnTreasure(hero, map, 0, 1);
					map.setPosition(currentRow, currentCol, 'T');
					system("CLS");
					map.printMap();
				}
			}
			break;
		}
		}
		if (hero.getRow() == map.getWidth() - 1 && hero.getCollum() == map.getLength() - 1) {


			printLevelUpScreen(hero);
			hero.updateStatsFile();
			map.deleteMap();
			map.updateItemsFile();
			map.updateMapsFile();
			map.readFile();
			map.createMap();
			hero.setRow(0);
			hero.setCollum(0);
			map.printMap();
		}
	}

}


void Game::printLevelUpScreen(Hero& hero) {  // изкарване на екран за вдигане на ниво

	char command;
	size_t points = 30;
	hero.setLevel(hero.getLevel() + 1);  // повишаване на нивото на героя
	while (points > 0) {
		system("CLS");
		std::cout << "  ~ LEVEL UP ~" << '\n';    // изкарване на характеристиките на героя
		std::cout << "--------------------" << '\n';
		std::cout << " Level:    " << hero.getLevel() << '\n';
		std::cout << " Health:   " << hero.getFullHealth() << '\n';
		std::cout << " Strength: " << hero.getStrength() << '\n';
		std::cout << " Mana:     " << hero.getMana() << '\n';
		std::cout << "--------------------" << '\n';
		std::cout << " Press 'H' to add 10 points to Health"<<'\n';
		std::cout << " Press 'S' to add 10 points to Strength" << '\n';
		std::cout << " Press 'M' to add 10 points to Mana" << '\n';
		std::cout << " Level Up points left: " << points;
		command = _getch();
		switch (command) {      // избор към коя характеристика да добавим 10 точки

		case 'h': // живот
			hero.setFullHealth(hero.getFullHealth() + 10);
			points -= 10;
			break;
		case 's':  // силова атака
			hero.setStrength(hero.getStrength() + 10);
			points -= 10;
			break;
		case 'm':   // атака с магия
			hero.setMana(hero.getMana() + 10);
			points -= 10;
			break;
		}
	}
	hero.setHealth(hero.getFullHealth());  // възстановяваме напълно живота на героя след приключване на нивото
	system("CLS");
}