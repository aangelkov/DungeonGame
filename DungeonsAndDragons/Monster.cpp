#include"Monster.h"
#include<assert.h>
#include"Hero.h"

Monster::Monster(size_t lvl) {

	level = lvl;                // задават се характеристиките на чудовището спрямо нивото на картата на което то се намира
	strength = 12 + level * 10;
	mana = 12 + level * 10;
	health = 38 + level * 10;
	armorPercent = 8 + level * 5;
}

size_t Monster::getStrength() {

	return this->strength;
}

int Monster::getHealth() {

	return this->health;
}

size_t Monster::getMana() {

	return this->mana;
}

size_t Monster::getArmorPercent() {

	return this->armorPercent;
}

size_t Monster::getLevel() {

	return this->level;
}

void Monster::setHealth(const int health) {

	assert(health > -250 && health < 250);
	this->health = health ;
}

void Monster::setStrength(const size_t strength) {

	assert(strength > 0 && strength < 200);
	this->strength = strength;
}

void Monster::setMana(const size_t mana) {

	assert(mana > 0 && mana < 200);
	this->mana = mana;
}

void Monster::setLevel(const size_t level) {

	assert(level > 0 && level < 15);
	this->level = level;
}

void Monster::setArmorPercent(const size_t armorPercent) {

	assert(armorPercent > 0 && armorPercent < 100);
	this->armorPercent = armorPercent;
}