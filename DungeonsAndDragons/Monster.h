#pragma once


class Monster {

private:	
	size_t strength;
	size_t mana;
	int health;
	size_t level;
	size_t armorPercent;
	void setStrength(const size_t strength);
	void setMana(const size_t mana);
	void setHealth(const int health); 
	void setLevel(const size_t level);
	void setArmorPercent(const size_t armorPercent);
	Monster(size_t);
public:
	friend class Game;
	size_t getStrength();
	size_t getMana();
	int getHealth();
	size_t getLevel();
	size_t getArmorPercent();
};