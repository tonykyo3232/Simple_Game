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
    double avoidRate;

    // user account info
    string user_name;
    string passward;

    // player's accessories
    int money;
    int diamond;

public:
    // Default Constructor
    Player();
    Player(string name, int level, int life, int attack, int defend);

    string getName() {return name;} const
    int getLevel(){return level;} const
    int getLife() {return life;} const
    int getAtkPt(){return attack;} const
    int getDefPt(){return defend;} const
    string getUser() {return user_name;} const
    string getPwd() {return passward;} const
    bool setUser(string entry_user) {this->user_name = entry_user; return true;}
    bool setPwd(string entry_pwd) {this->passward = entry_pwd; return true;}
    bool setName(string entry_name) {this->name = entry_name; return true;}
    bool setLevel(int entry_level) { this->level = entry_level; return true;}
    bool setLife(int entry_life) {this->life = entry_life ; return true;}
    bool setAtkpt(int entry_attack) {this->attack = entry_attack; return true;}
    bool setDefpt(int entry_defend) {this->defend = entry_defend; return true;}

    // future design parts
    double getAvoidRate();
    int getMoney();
    int getDiamond();
};

#endif // PLAYER_H_INCLUDED
