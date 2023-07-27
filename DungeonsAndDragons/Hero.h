#pragma once



enum Race {
	HUMAN, MAGE, WARRIOR
};



class Hero {

private:
	size_t strength;
	size_t mana;
	int health;
	size_t fullHealth;
	size_t level;
	Race race;
	size_t armor;
	size_t weapon;
	size_t spell;
	int row;
	int collum;
	void setStrength(size_t strength);
	void setMana(size_t mana);
	void setHealth(int health);
	void setFullHealth(size_t fullHealth);
	void setLevel(size_t level);
	void setRace(Race race);
	void setRace(const char*);
	void setArmor(size_t armor);
	void setWeapon(size_t weapon);
	void setSpell(size_t spell);
	void setRow(int);
	void setCollum(int);
	void chooseRace();
	void loadPrevious();
	void updateStatsFile();
	const char* toString(Race);
public:
	friend class Game;
	Hero();
	size_t getArmor();
	size_t getWeapon();
	size_t getSpell();
	size_t getStrength();
	size_t getMana();
	int getHealth();
	size_t getFullHealth();
	size_t getLevel();
	int getRow();
	int getCollum();
	Race getRace();


};

