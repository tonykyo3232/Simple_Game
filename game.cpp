/*
idea to resolve system("pause"): https://stackoverflow.com/questions/1107705/systempause-why-is-it-wrong
https://www.includehelp.com/c-programming-questions/how-to-clear-output-screen-in-c.aspx
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream> // file IO
#include <sstream>
#include <algorithm>
#include <time.h>
#include <stdlib.h> // reference: https://mathbits.com/MathBits/CompSci/Introduction/clear.htm
#include<ctime> // used to work with date and time

#include "player.h"

void fileOpen(int level[], double attack[], double defend[], int exp[], int &count, string filename);
void main_menu(double attack[], double defend[], int exp[], Player&);
void battle_menu(double attack[], double defend[], int exp[], Player&);
void battle(int option, double attack[], double defend[], int exp[], Player&);
void buying_menu(Player&);
void check_status(Player);
void updateInfo(int level, double attack, double defend, int life, int curr_exp, int curr_money, int curr_diamond, Player&);
void sleep(unsigned int mseconds);
bool login(string &userName, string &password, Player&);
bool save_player(Player&);
void write_userlog(bool login, Player);
void cheat_code(Player&);

using namespace std;

int main(int argc, char** argv)
{
    const int SIZE = 100;
    int count = 0,
        level[SIZE],
        exp[SIZE];
    double attack[SIZE],
           defend[SIZE];

    // read the context of the game
    fileOpen(level, attack, defend, exp, count, argv[1]);

    // variables for player
    Player P;
    string name;

    // login information
    string username;
    string password;

    cout << "------------------------------------------" << endl;
    cout << "Welcome to Tony's game!" << endl;
    cout << "Please log in your account to continue the game" << endl;
    cout << "------------------------------------------" << endl;
    bool hasAccount = login(username, password, P);

    if(hasAccount){
        system ("clear");
        cout << "------------------------------------------" << endl;
        cout << "Welcome back " << P.getName() << "!" << endl;
        cout << "------------------------------------------" << endl;
        write_userlog(true, P);
        // system ("pause");
        cin.ignore();
        cin.get();
    }
    else{
        // welcome message
        system ("clear");
        cout << "------------------------------------------" << endl;
        cout << "You can save your data in the end of the game" << endl;
        cout << "Please enter your name: " << endl;
        cout << "------------------------------------------" << endl;
        cout << "Enter name: ";
        cin >> name;
        P.setName(name);
        write_userlog(true, P);
        system ("clear");
        cout << "Hello "<< name << ", now you are in level 0 , you are ready to have an adventure!" << endl;
        cout << "This game has 5 level. if you accomplish all of them. You are the winner!" << endl;
        // system ("PAUSE");
        cin.ignore();
        cin.get();
    }

    // main menu
    // enter menu to start the selection
    main_menu(attack, defend, exp, P);

    char choice;
    cout << "Have you saved the game?" << endl;;
    cout << "Would you like to save your progress? (Y/N)";
    cin >> choice;
    if (choice == 'y' || choice == 'Y'){
        save_player(P); // save player's information
    }

    cout << "\n------------------------------------------" << endl;
    cout << "Game is over." << endl;
    cout << "------------------------------------------" << endl;
    write_userlog(false, P);
    // system ("PAUSE");
    cin.ignore();
    cin.get();
    return 0;
}

void fileOpen(int level[], double attack[], double defend[], int exp[], int &count, string filename)
{
    fstream inputFile;

    // open the file
    inputFile.open(filename);

    // read the file
    while (inputFile >> level[count] >> attack[count] >> defend[count] >> exp[count])
    {
        count++;
    }

    // close the file
    inputFile.close();
}

// main menu
// user can choose to battle, check info, save game and purchase equipment
void main_menu(double attack[], double defend[], int exp[], Player &P)
{
    string user_input = "";
    bool exit = false;

    do{
        system ("clear");
        cout << "------------------------------------------" << endl;
        cout << "1: Start Battle" << endl;
        cout << "2: Check Info" << endl;
        cout << "3: Store" << endl;
        cout << "4: Save game" << endl;
        cout << "5: Use cheating code" << endl;
        cout << "6: Exit the game" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Enter your option: ";
        cin >> user_input;

        // convert user input to integer
        // if user enter "1", it will be converted to 1
        // if user enter "abc", it will be converted to 0
        stringstream toInt(user_input);

        // store the user input into option as an integer
        int option = 0;
        toInt >> option;

        switch(option)
        {
            case 1:
                battle_menu(attack, defend, exp, P);
                break;
            case 2:
                check_status(P);
                break;
            case 3:
                buying_menu(P);
                break;
            case 4:
                save_player(P);
                break;
            case 5:
                cheat_code(P);
                break;
            case 6:
                exit = true;
                break;
            default:
            {
                cout << "Please enter the valid number!" << endl;
                cout << "Please enter the option: ";
                cin >> user_input;
                stringstream toInt(user_input);
                int option = 0;
                toInt >> option;
            }
        }

    } while(exit == false);
}

void battle_menu(double attack[], double defend[], int exp[], Player &P)
{
        string user_input = "";
        bool exit = false;

        do {
            system ("clear");
            cout << "------------------------------------------" << endl;
            cout << "There are numbers of level you can choose." << endl;
            cout << "1: Story 1(Beginner)" << endl;
            cout << "2: Story 2(Easy)" << endl;
            cout << "3: Story 3(Normal)" << endl;
            cout << "4: Story 4(Hard)" << endl;
            cout << "5: Story 5(Hell)" << endl;
            cout << "6: check your condition" << endl;
            cout << "7: Return to main menu." << endl;
            cout << "------------------------------------------" << endl;
            cout << "Please select the level: ";
            cin >> user_input;

            // convert user input to integer
            // if user enter "1", it will be converted to 1
            // if user enter "abc", it will be converted to 0
            stringstream toInt(user_input);

            // store the user input into option as an integer
            int option = 0;
            toInt >> option;

            //debug
            // cout << "you enter: [" << option << "]"<< endl;

            switch(option) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    battle(option, attack, defend, exp, P);
                    break;
                case 6:
                    check_status(P);
                    break;
                case 7:
                    cout << "Returning to main menu..." << endl;
                    sleep(1000);
                    exit = true;
                    break;
                default:
                    {
                        cout << "Please enter the valid number!" << endl;
                        cout << "Please select the level: ";
                        cin >> user_input;
                        stringstream toInt(user_input);
                        int option = 0;
                        toInt >> option;
                    }
            }

        } while( exit == false);
}

void battle(int option, double attack[], double defend[], int exp[], Player &P)
{
    // default value (level 1)
    char choice;
    double damage = 2,
           monsterLife = 5;
    int exp_gain = 25,
        money_gain = 2,
        diamond_gain = 0;

    // adjust the level based on user's input
    if (option == 2){
        damage = 5;
        monsterLife = 10;
        exp_gain = 50;
        money_gain = 4;
    }
    else if(option == 3){
        damage = 15;
        monsterLife = 20;
        exp_gain = 75;
        money_gain = 8;
    }
    else if(option == 4){
        damage = 40;
        monsterLife = 50;
        exp_gain = 150;
        money_gain = 16;
    }
    else if(option == 5){
        damage = 150;
        monsterLife = 500;
        exp_gain = 300;
        money_gain = 50;
        diamond_gain = 1;
    }
    else{}
    system ("clear");
    cout << "------------------------------------------------" << endl;
    cout << "=  You are in story " << option << "." << endl;
    cout << "=  Your current Level is: " << P.getLevel() << endl;
    cout << "=  Your life now is: " << P.getLife() << endl;
    cout << "=  Now your attack point is: " << P.getAtkPt() << "+(" << P.getExtraAtk() << ")" << endl;
    cout << "=  and defend point: " << P.getDefPt() << "+(" << P.getExtraDef() << ")" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Here is a monster. Please start attacking." << endl;

    int game_level = P.getLevel(),
        game_life = P.getLife(),
        game_attack = P.getAtkPt() + P.getExtraAtk(),
        game_defend = P.getDefPt() + P.getExtraDef(),
        curr_exp = P.getExp(),
        curr_money = P.getMoney(),
        curr_diamond = P.getDiamond();

    do{
        cout << "Wanna attack?(Y/N)";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            monsterLife = monsterLife - game_attack;
            cout << "You attack the monster, now he remains " << monsterLife << " point of life" << endl;
            game_life = game_life - damage + game_defend;
            cout << "You are attacked by monster. Now your life is remaining " << game_life << " points." << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
            if (game_life < 1)
            {
                cout << "You are dead. Game over!" << endl;
                cout << " +_+" << endl;
                cout << "++++++++++++++++++++++++++++++++++++++" << endl;
                break;
            }
        }
        if (choice == 'n' || choice == 'N'){
            game_life = game_life - (damage + 2) + game_defend;
            cout << "The monster attacks you directly!!! Now your life is remaining " << game_life << " points. Please ATTACK back!!!" << endl;
        }

        cout << "Your life point is " << game_life << ", do you want to use the life potion? (You have " << P.getLifePotion() << " life potion) (Y/N)";
        char input, input2;
        cin >> input;
        if(input == 'Y' || input == 'y'){
            bool need_heal = true;
            while(need_heal){
                cout << "How many life potion?";
                cin >> input2;
                int num = input2 - 48; //convert char to int
                if(num > P.getLifePotion()){
                    cout << "Sorry. You don't have enough Life potions!" << endl;
                }
                else{
                    for(int i = 0; i < num; i++){
                        game_life += 10;
                    }
                    need_heal = false;
                    P.setLifePotion(P.getLifePotion() - num);
                }
            }
        }
    } while(monsterLife > 0);

    if (game_life > 0 && monsterLife < 1)
    {
            cout << "**********************************" << endl;
            cout << "You defeat the monster //" << endl;
            cout << "**********************************" << endl;

            // increase the exp, money and diamond obtained from battle
            curr_exp += exp_gain;
            curr_money += money_gain;
            curr_diamond = diamond_gain;
    }

    int prev_level = game_level;

    // a loop that determine how many level will be up
    while(curr_exp >= exp[game_level]){
        game_level++;
    }

    // check if needs to level up
    if (prev_level != game_level)
    {
            game_life = game_life + 15;
            cout << "Congratulations! Level up!!!" << endl;
            cout << "===========================================" << endl;
            cout << "Level : " << game_level << endl;
            cout << "Attack: " << attack[game_level] << "+(" << P.getExtraAtk() << ")" << endl;
            cout << "Defend: " << defend[game_level] << "+(" << P.getExtraDef() << ")" << endl;
            cout << "===========================================" << endl;
    }

    // save the result
    updateInfo(game_level, attack[game_level], defend[game_level], game_life, curr_exp, curr_money, curr_diamond, P);
    // system ("PAUSE");
    cin.ignore();
    cin.get();
}


void check_status(Player P){
    system ("clear");
    cout << "*******************************************" << endl;
    cout << "Checking status..." << endl;
    // delay to simulate loading
    sleep(1900);
    cout << "=  Your current Level is: " << P.getLevel() << endl;
    cout << "=  Your life now is: " << P.getLife() << endl;
    cout << "=  Number of life potion: " << P.getLifePotion() << endl;
    cout << "=  Now your attack point is: " << P.getAtkPt()  << "+(" << P.getExtraAtk() << ")" << endl;
    cout << "=  and defend point: " << P.getDefPt() << "+(" << P.getExtraDef() << ")" << endl;
    cout << "=  Your current exp is: " << P.getExp() << endl;
    cout << "=  You have " << P.getMoney() << "$" << endl;
    cout << "=  You have " << P.getDiamond() << " diamond(s)" << endl;
    cout << "*******************************************" << endl;
    // system ("PAUSE");
    cin.ignore();
    cin.get();
}


// ask user to create an account for saving the data
// if the user already has an account, overwrite the data
bool save_player(Player &P){
    system ("clear");
    string account_name;
    string pwd;

    // first time user
    if(P.getUser().empty() == true || P.getPwd().empty() == true){
        cout << "Please enter your account name (no spaces in between): ";
        cin >> account_name;
        cout << "Please enter your password (no spaces in between): ";
        cin >> pwd;
        P.setUser(account_name);
        P.setPwd(pwd);
    }

    cout << "Saving the player's data..." << endl;
    ofstream fout;

    // overwrite the user's data
    // saving order: account name, password, name, level, attack point, defend point, life point
    fout.open("player_" + P.getUser() + "_data" + ".txt", ofstream::trunc); // reference: http://www.cplusplus.com/reference/fstream/ofstream/open/
    fout << P.getUser() << " " << P.getPwd() << " " << P.getName() << " " << endl
    << P.getLevel() << " " << P.getAtkPt() << " " << P.getDefPt() << " " << P.getLife() << " " << P.getExp() << endl
    << P.getMoney() << " " << P.getDiamond() << endl
    << P.getExtraAtk() << " " << P.getExtraDef() << " " << P.getLifePotion() << endl;
    fout.close();

    // debug
    cout << "Overwriting these data..." << endl;
    cout << "----------------------------" << endl;
    cout << "User name: "<< P.getUser() << endl;
    cout << "Password: " << P.getPwd() << endl;
    cout << "Name: " << P.getName() << endl;
    cout << "Level: " << P.getLevel() << endl;
    cout << "Attack: " << P.getAtkPt() << "+(" << P.getExtraAtk() << ")" << endl;
    cout << "Defend: " << P.getDefPt() << "+(" << P.getExtraDef() << ")" << endl;
    cout << "Life point: " << P.getLife() << endl;
    cout << "Exp: " << P.getExp() << endl;
    cout << "Money: " << P.getMoney() << "$" << endl;
    cout << "Diamond: " << P.getDiamond() << endl;
    cout << "Number of life potion: " << P.getLifePotion() << endl;
    cout << "----------------------------" << endl;

    // disable for now
    // create an account for user if they doesn't have one
    // fout.open("player_" + account_name + "_info" + ".txt");
    // fout << account_name << " " << password;
    // fout.close();

    sleep(1600); // delay to simulate loading
    cout << "Data is saved..." << endl;
    // system ("PAUSE");
    cin.ignore();
    cin.get();
    return true;
}

// reference: https://ubuntuforums.org/showthread.php?t=296142
void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void updateInfo(int level, double attack, double defend, int life, int curr_exp, int curr_money, int curr_diamond, Player &P){
    P.setLevel(level);
    P.setAtkpt(attack);
    P.setDefpt(defend);
    P.setLife(life);
    P.setExp(curr_exp);
    P.setMoney(curr_money);
    P.setDiamond(curr_diamond);
    sleep(1000); // delay to simulate loading
}

// login in user's account
bool login(string &username, string &password, Player &P){
    fstream fin;
    bool status = false;

    string readUser = "",
            readPwd = "",
               name = "";
    int level = 0,
        life = 100,
        attack = 1,
        defend = 1,
        exp = 0,
        money = 0,
        diamond = 0,
        extra_atk = 0,
        extra_def = 0,
        life_potion = 0;

    do{
        cout << "Please enter your username (type NA to quit login):";
        cin >> username;

        // convert string to back to lower case
        // reference: https://thispointer.com/converting-a-string-to-upper-lower-case-in-c-using-stl-boost-library/#:~:text=Convert%20a%20String%20to%20Lower%20Case%20using%20STL&text=int%20tolower%20(%20int%20c%20)%3B,function%20each%20of%20them%20i.e.
        for_each(username.begin(), username.end(), [](char & c) {
            c = ::tolower(c);
        });

        // quit login and begin as a new user
        if(username == "na"){
            status = false;
            break;
        }

        sleep(1000); // delay to simulate loading
        cout << "Please enter your password:";
        cin >> password;
        sleep(1000); // delay to simulate loading

        cout << "Checking the account..." << endl;
        sleep(2000); // delay to simulate loading

        // try to open user file to ensure the account exists
        fin.open("player_" + username + "_data" + ".txt");

        // check if the file is found or not
        if(fin.is_open() == false){
            cout << "Cannot find user data.." << endl;
            cout << "Please enter the username again..." << endl;
            sleep(1000); // delay to simulate loading
        }
        else{
            // once the user account is found, check the password next
            fin >> readUser >> readPwd >> name >> level >> attack >> defend >> life >> exp >> money >> diamond >> extra_atk >> extra_def >> life_potion;

            // // debug
            // cout << "readUser: [" << readUser << "]" << endl;
            // cout << "readPwd: [" << readPwd << "]" << endl;
            // cout << "name: [" << name << "]" << endl;
            // cout << "level: [" << level << "]" << endl;
            // cout << "attack: [" << attack << "]" << endl;
            // cout << "defend: ["<< defend << "]" << endl;
            // cout << "life: [" << life << "]" << endl;

            // if the username and password match, it log in sucessfully
            if(readUser == username && readPwd == password){
                status = true;
            }
            else{
                cout << "the password is incorrect! Please enter it again..." << endl;
                sleep(1000); // delay to simulate loading
            }
        }

    } while(status == false);

    fin.close();

    // save account info
    P.setUser(username);
    P.setPwd(password);
    P.setName(name);
    P.setLevel(level);
    P.setAtkpt(attack);
    P.setDefpt(defend);
    P.setLife(life);
    P.setExp(exp);
    P.setMoney(money);
    P.setDiamond(diamond);
    P.setExtraAtk(extra_atk);
    P.setExtraDef(extra_def);
    P.setLifePotion(life_potion);

    return status;
}

void write_userlog(bool login, Player P){
    time_t t; // t passed as argument in function time()
    struct tm * tt; // decalring variable for localtime()
    time (&t); //passing argument to time()
    tt = localtime(&t);

    ofstream fout;

    fout.open("userlog.txt", ofstream::app);

    if (login == true)
        fout << "User " << P.getName() << "(" << P.getUser() << ") login time: "<< asctime(tt);
    else
        fout << "User " << P.getName() << "(" << P.getUser() << ") logout time: "<< asctime(tt);

    fout.close();
}


void buying_menu(Player &P){

    string user_input = "";
    bool exit = false;

    do{
        system ("clear");
        cout << "*****************************" << endl;
        cout << "Welcome to Tony's shop" << endl;
        cout << "Please enter the option to purchase the item." << endl;
        cout << "Now you have " <<  P.getMoney() << "$ and " << P.getDiamond() << " diamond(s)" << endl;
        cout << "*****************************" << endl;

        cout << "\n----------------------------" << endl;
        cout << "1. Life potion - 5$" << endl;
        cout << "2. Sell diamond(s)" << endl;
        cout << "3. Strengthen your weapon - 20$" << endl;
        cout << "4. Strengthen your shield - 20$" << endl;
        cout << "5. Exit Shop" << endl;
        cout << "----------------------------" << endl;
        cout << "Enter your option: ";
        cin >> user_input;

        // convert user input to integer
        // if user enter "1", it will be converted to 1
        // if user enter "abc", it will be converted to 0
        stringstream toInt(user_input);

        // store the user input into option as an integer
        int option = 0;
        toInt >> option;

        switch(option)
        {
            case 1:
            {
                int curr_life_potion = P.getLifePotion();
                if(P.getMoney() >= 5){
                    curr_life_potion++;
                    int total_money = P.getMoney() - 5;
                    P.setLifePotion(curr_life_potion);
                    P.setMoney(total_money);
                    cout << "You have purchase a life potion!" << endl;
                }
                else{
                    cout << "Sorry. You don't have enough money!" << endl;
                }
                sleep(1600); // delay to simulate loading
                // system ("PAUSE");
                cin.ignore();
                cin.get();
                break;
            }
            case 2:
            {
                int curr_diamond = P.getDiamond();
                if(curr_diamond == 0){
                    cout << "Sorry! You don't have any diamond to sell..." << endl;
                }
                else{
                    int money_gain = curr_diamond * 50;
                    curr_diamond = 0;
                    int total_money = P.getMoney() + money_gain;
                    P.setMoney(total_money);
                    P.setDiamond(0);
                    cout << "Diamond(s) have sold and you gain " << money_gain << "$" << endl;
                }
                sleep(1600); // delay to simulate loading
                // system ("PAUSE");
                cin.ignore();
                cin.get();
                break;
            }
            case 3:
            {
                int curr_extra_atk = P.getExtraAtk();
                if(P.getMoney() >= 20){
                    int total_money = P.getMoney() - 20;
                    curr_extra_atk++;
                    P.setExtraAtk(curr_extra_atk);
                    P.setMoney(total_money);
                    cout << "You have Strengthen your weapon!" << endl;
                }
                else{
                    cout << "Sorry. You don't have enough money!" << endl;
                }
                sleep(1600); // delay to simulate loading
                // system ("PAUSE");
                cin.ignore();
                cin.get();
                break;
            }
            case 4:
            {
                int curr_extra_def = P.getExtraDef();
                if(P.getMoney() >= 20){
                    int total_money = P.getMoney() - 20;
                    curr_extra_def++;
                    P.setExtraDef(curr_extra_def);
                    P.setMoney(total_money);
                    cout << "You have Strengthen your shield!" << endl;
                }
                else{
                    cout << "Sorry. You don't have enough money!" << endl;
                }
                sleep(1600); // delay to simulate loading
                // system ("PAUSE");
                cin.ignore();
                cin.get();
                break;
            }
            case 5:
                cout << "Returning back to main menu..." << endl;
                sleep(1600); // delay to simulate loading
                exit = true;
                break;
            default:
            {
                cout << "Please enter the valid number!" << endl;
                cout << "Please enter the option: ";
                cin >> user_input;
                stringstream toInt(user_input);
                int option = 0;
                toInt >> option;
            }
        }

    } while(exit == false);
}

void cheat_code(Player &P){
    string user_input;
    bool exit = false;
    do{
        system ("clear");
        cout << "*****************************" << endl;
        cout << "Welcome to Tony's cheating center" << endl;
        cout << "*****************************" << endl;

        cout << "Please enter the code (press n for going back to menu):";
        cin >> user_input;

        if(user_input == "n" || user_input == "N") exit = true;
        if(exit == true) break;

        if(user_input == "life_plus_ten"){
            P.setLife(P.getLife() + 10);
            cout << "cheat code is recognized..." << endl;
            sleep(1500);
            cout << "You get 10 extra life" << endl;
            system("PAUSE");
            check_status(P);
        }
        else if(user_input == "atk_plus_ten"){
            P.setExtraAtk(P.getExtraAtk() + 10);
            cout << "cheat code is recognized..." << endl;
            sleep(1500);
            cout << "You get 10 extra attack points" << endl;
            system("PAUSE");
            check_status(P);
        }
        else if(user_input == "def_plus_ten"){
            P.setExtraDef(P.getExtraDef() + 10);
            cout << "cheat code is recognized..." << endl;
            sleep(1500);
            cout << "You get 10 extra defend points" << endl;
            system("PAUSE");
            check_status(P);
        }
        else if(user_input == "money_plus_ten"){
            P.setMoney(P.getMoney() + 10);
            cout << "cheat code is recognized..." << endl;
            sleep(1500);
            cout << "You get extra 10$" << endl;
            system("PAUSE");
            check_status(P);
        }
        else if(user_input == "diamond_plus_one"){
            P.setDiamond(P.getDiamond() + 1);
            cout << "cheat code is recognized..." << endl;
            sleep(1500);
            cout << "You get 1 extra diamond" << endl;
            system("PAUSE");
            check_status(P);
        }
        else{
            cout << "Please enter the valid cheat code..." << endl;
            sleep(1500);
            system("PAUSE");
        }
    }while(exit == false);

    cout << "Backing to menu..." << endl;
    sleep(1500);
}
