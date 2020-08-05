#include "player.h"

#include <iomanip>

using namespace std;


// Default Constructor implementation
Player::Player(){
	name = "";
    level = 0;
    life = 100;
    attack = 1;
    defend = 1;
    avoidRate = 0;

    // player's accessories
    money = 0;
    diamond = 0;
}

// Constructor for assigning value
Player::Player(string entry_name, int entry_level, int entry_life, int entry_attack, int entry_defend){
	this->name = entry_name;
	this->level = entry_level;
	this->life = entry_life;
	this->attack = entry_attack;
	this->defend = entry_defend;
}
