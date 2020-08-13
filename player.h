#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <string>

using namespace std;

class Player{
private:
    // player's basic information
    string name;
    int level;
    int life;
    int attack;
    int defend;
    int exp;

    int extra_atk;
    int extra_def;
    int life_potion;

    // future design
    double avoidRate;

    // user account info
    string user_name;
    string password;

    // player's accessories
    int money;
    int diamond;

public:
    // Default Constructor
    Player();
    Player(string name, int level, int life, int attack, int defend);

    // getter functions
    string getName() {return name;} const
    int getLevel(){return level;} const
    int getLife() {return life;} const
    int getAtkPt(){return attack;} const
    int getDefPt(){return defend;} const
    int getExp(){return exp;} const
    int getMoney(){return money;} const
    int getDiamond(){return diamond;} const
    int getExtraAtk(){return extra_atk;} const
    int getExtraDef(){return extra_def;} const
    int getLifePotion(){return life_potion;} const
    string getUser() {return user_name;} const
    string getPwd() {return password;} const

    // setting functions
    bool setUser(string entry_user) {this->user_name = entry_user; return true;}
    bool setPwd(string entry_pwd) {this->password = entry_pwd; return true;}
    bool setName(string entry_name) {this->name = entry_name; return true;}
    bool setLevel(int entry_level) { this->level = entry_level; return true;}
    bool setLife(int entry_life) {this->life = entry_life ; return true;}
    bool setAtkpt(int entry_attack) {this->attack = entry_attack; return true;}
    bool setDefpt(int entry_defend) {this->defend = entry_defend; return true;}
    bool setExp(int entry_exp) {this->exp = entry_exp; return true;}
    bool setMoney(int entry_money) {this->money = entry_money; return true;}
    bool setDiamond(int entry_diamond) {this->diamond = entry_diamond; return true;}
    bool setExtraAtk(int entry_extra_atk) {this->extra_atk = entry_extra_atk; return true;}
    bool setExtraDef(int entry_extra_def) {this->extra_def = entry_extra_def; return true;}
    bool setLifePotion(int entry_life_potion) {this->life_potion = entry_life_potion; return true;}

    // future design parts
    double getAvoidRate();
};

#endif // PLAYER_H_INCLUDED
