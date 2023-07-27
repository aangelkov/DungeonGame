#include"Hero.h"
#include<iostream>
#include<fstream>
#include<conio.h>
#include<assert.h>


Hero::Hero() {

	strength = health = mana = armor = weapon = spell = level = row = collum = fullHealth = 0;
	race = HUMAN;
}


int Hero::getHealth() {
	
	return this->health;
}

size_t Hero::getStrength() {

	return this->strength;
}

size_t Hero::getMana() {

	return this->mana;
}

size_t Hero::getLevel() {

	return this->level;
}

Race Hero::getRace() {

	return this->race;
}

size_t Hero::getWeapon() {
	return weapon;
}

size_t Hero::getSpell() {
	return spell;
}

size_t Hero::getArmor() {
	return armor;
}

int Hero::getCollum() {
	return collum;
}

int Hero::getRow() {
	return row;
}

void Hero::setWeapon(size_t wep) {
	assert(wep >= 0 && wep < 100);
	weapon=wep;
}

void Hero::setSpell(size_t sp) {
	assert(sp >= 0 && sp < 100);
	spell=sp;
}

void Hero::setArmor(size_t arm) {
	assert(arm >= 0 && arm < 100);
	armor=arm;
}

void Hero::setHealth(int health) {
	assert(health >= -100 && health < 300);
	this->health = health;
}

void Hero::setStrength(size_t strength) {
	assert(strength >= 0 && strength < 150);
	this->strength = strength;
}

void Hero::setMana(size_t mana) {
	assert(mana >= 0 && mana < 150);
	this->mana = mana;
}

void Hero::setLevel(size_t level) {
	assert(level >= 0 && level < 10);
	this->level = level;
}

void Hero::setRace(const Race race) {

	this->race = race;
}

void Hero::setRace(const char* race) {

	if (race == "HUMAN") {
	
		setRace(HUMAN);
	}
	else if (race == "WARRIOR") {

		setRace(WARRIOR);
	}
	else if (race == "MAGE") {

		setRace(MAGE);
	}
}

const char* Hero::toString(Race race) {

	switch (race) {
	case HUMAN:
		return "Human"; break;
	case MAGE:
		return "Mage"; break;
	case WARRIOR:
		return "Warrior"; break;
	}
}


void Hero::setRow(int r) {

	assert(r >= 0 && r < 100);
	row = r;
}

void Hero::setCollum(int c) {
	assert(c >= 0 && c < 100);
	collum = c;
}

void Hero::setFullHealth(size_t fHealth) {
	assert(fHealth >= 50 && fHealth < 300);
	fullHealth = fHealth;
}

void Hero::chooseRace() { // избиране на раса

	std::cout << " Choose your Hero's race! " << '\n';  // изкарване на избор
	std::cout << '\n';
	std::cout << " Press 'H' for Human" << '\n';
	std::cout << " Press 'W' for Warrior" << '\n';
	std::cout << " Press 'M' for Mage" << '\n';

	char type;
	do {

		type = _getch();
	}
	while (type != 'h' && type != 'w' && type != 'm'); // взимане на избора на потребителя

	switch (type) {

		case 'h': { 

			setRace(HUMAN);  // задаване на характеристиките на героя ако той е човек
			setStrength(30);
			setMana(20);
			setHealth(50);
			break;
		}
		case 'w': {

			setRace(WARRIOR); // ако е войн
			setStrength(40);
			setMana(10);
			setHealth(50);
			break;
		}
		case 'm': {

			setRace(MAGE);  // ако е магьосник
			setStrength(10);
			setMana(40);
			setHealth(50);
			break;
		}
	}
	setLevel(1);  // задаване на характеристиките които не зависят от расата
	setArmor(0);
	setWeapon(20);
	setSpell(20);
	setFullHealth(50);
}

size_t Hero::getFullHealth() {

	return fullHealth;
}

void Hero::updateStatsFile() { // обновяване на файла който съхранява информация за характеристиките на героя

	std::ofstream out;
	out.open("heroStats.txt");
	if (out) { // отваряме файла

		out << toString(getRace())<<" " << getLevel()<<" "<< getFullHealth()<<" " << getStrength()<<" " << getMana()<<" " << getArmor()<<" " <<getWeapon()<<" " << getSpell();
	}            // въвеждаме характеристиките на героя
	else {
		std::cout << "Hero Stats file didn't open.";
	}
	out.close(); // затваряме файла
}

void Hero::loadPrevious() {  // прочитане на файла който съдържа информация за характеристиките на героя

	std::ifstream in;
	int lvl, fullhlth, strngth, mna, armr, wpn, spll;
	char rc[10];
	in.open("heroStats.txt");  // отваряне
	if (in) {

		in  >>rc >>lvl>> fullhlth>> strngth>> mna>> armr>> wpn>> spll; // прочитане
		setRace(rc);
		setLevel(lvl);
		setFullHealth(fullhlth);  // задаваме съответните характеристики на героя
		setHealth(fullhlth);
		setStrength(strngth);
		setMana(mna);
		setArmor(armr);
		setWeapon(wpn);
		setSpell(spll);
	}
	else {
		std::cout << "Hero Stats file didn't open.";
	}
	in.close(); // затваряне на файла
}
