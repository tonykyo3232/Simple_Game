#include <iostream>
#include <string>
#include <iomanip>
#include <fstream> // file IO
#include <sstream>
#include <algorithm>
#include <time.h>
#include <stdlib.h> // reference: https://mathbits.com/MathBits/CompSci/Introduction/clear.htm

#include "player.h"

// void fileOpen(int level[], double attack[], double defend[], int &count);
void fileOpen(int level[], double attack[], double defend[], int exp[], int &count);
bool login(string &userName, string &password, Player&);
void menu(double attack[], double defend[], int life, int exp[], Player&);
void battle(int option, double attack[], double defend[], int life, int exp[], Player&);
void check_status(double attack[], double defend[], int life, int exp[], Player);
void updateInfo(int level, double attack, double defend, int life, int curr_exp, int curr_money, int curr_diamond, Player&);
bool save_player(string username, string password, double attack[], double defend[], int life, int exp[], Player);
void sleep(unsigned int mseconds);

using namespace std;

int main()
{
    const int SIZE = 100;
    int count = 0,
        life = 100,
        level[SIZE],
        exp[SIZE];
    double attack[SIZE],
           defend[SIZE];

    // read the context of the game
    // fileOpen(level, attack, defend, count);
    fileOpen(level, attack, defend, exp, count);

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
        system ("CLS");
        cout << "------------------------------------------" << endl;
        cout << "Welcome back " << username << "!" << endl;
        cout << "------------------------------------------" << endl;
        system ("PAUSE");
    }
    else{
        // welcome message
        system ("CLS");
        cout << "------------------------------------------" << endl;
        cout << "You can save your data in the end of the game" << endl;
        cout << "Please enter your name: " << endl;
        cout << "------------------------------------------" << endl;
        cout << "Enter name: ";
        cin >> name;
        P.setName(name);
        cout << "\n------------------------------------------" << endl;
        cout << "Hello "<< name << ", now you are in level 0 , you are ready to have an adventure!" << endl;
        cout << "This game has 5 level. if you accomplish all of them. You are the winner!" << endl;
    }

    // enter menu to start the selection
    menu(attack, defend, life, exp, P);

    char choice;
    cout << "Would you like to save your progress? (Y/N)";
    cin >> choice;
    if (choice == 'y' || choice == 'Y'){
        save_player(username, password, attack, defend, life, exp, P); // save player's information
    }

    return 0;
}

// void fileOpen(int level[], double attack[], double defend[], int &count)
void fileOpen(int level[], double attack[], double defend[], int exp[], int &count)
{
    fstream inputFile;

    // open the file
    inputFile.open("Level_List.txt");

    // read the file
    while (inputFile >> level[count] >> attack[count] >> defend[count] >> exp[count])
    {
        count++;
    }

    // close the file
    inputFile.close();
}

void menu(double attack[], double defend[], int life, int exp[], Player &P)
{
        string user_input = "";
        system ("CLS");
        cout << "------------------------------------------" << endl;
        cout << "There are numbers of level you can choose." << endl;
        cout << "1: Story 1(Beginner)" << endl;
        cout << "2: Story 2(Easy)" << endl;
        cout << "3: Story 3(Normal)" << endl;
        cout << "4: Story 4(Hard)" << endl;
        cout << "5: Story 5(Hell)" << endl;
        cout << "6: close the game." << endl;
        cout << "7: check your condition" << endl;
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

        do {
            switch(option) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    battle(option, attack, defend, life, exp, P);
                    break;
                case 6:
                    cout << "Game is over." << endl;
                    break;
                case 7:
                    check_status(attack, defend, life, exp, P);
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
        } while(option < 1 || option > 8);
}

void battle(int option, double attack[], double defend[], int life, int exp[], Player &P)
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
    else{
    }
    system ("CLS");
    cout << "------------------------------------------------" << endl;
    cout << "=  You are in story " << option << "." << endl;
    cout << "=  Your current Level is: " << P.getLevel() << endl;
    cout << "=  Your life now is: " << P.getLife() << endl;
    cout << "=  Now your attack point is: " << P.getAtkPt() << endl;
    cout << "=  and defend point: " << P.getDefPt() << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Here is a monster. Please start attacking." << endl;

    int game_level = P.getLevel(),
        game_life = P.getLife(),
        game_attack = P.getAtkPt(),
        game_defend = P.getDefPt(),
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
            cout << "The monster attacks you directly!!! Now your life is remaining " << life << " points. Please ATTACK back!!!" << endl;
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
            cout << "Attack: " << attack[game_level] << endl;
            cout << "Defend: " << defend[game_level] << endl;
            cout << "===========================================" << endl;
    }

    // save the result
    updateInfo(game_level, attack[game_level], defend[game_level], game_life, curr_exp, curr_money, curr_diamond, P);

    cout << "Do you want to back to the menu?(Y/N)";
    cin >> choice;
    if(choice == 'Y' || choice == 'y')
        menu(attack, defend, life, exp, P);
}


void check_status(double attack[], double defend[], int life, int exp[], Player P){
    system ("CLS");
    cout << "*******************************************" << endl;
    cout << "Checking status..." << endl;
    // delay to simulate loading
    sleep(1900);
    cout << "=  Your current Level is: " << P.getLevel() << endl;
    cout << "=  Your life now is: " << P.getLife() << endl;
    cout << "=  Now your attack point is: " << P.getAtkPt() << endl;
    cout << "=  and defend point: " << P.getDefPt() << endl;
    cout << "= Your current exp is: " << P.getExp() << endl;
    cout << "= You have " << P.getMoney() << "$" << endl;
    cout << "= You have " << P.getDiamond() << " diamond(s)" << endl;
    cout << "*******************************************" << endl;
    system ("PAUSE");
    menu(attack, defend, life, exp, P);
}


// ask user to create an account for saving the data
// if the user already has an account, overwrite the data
bool save_player(string username, string password, double attack[], double defend[], int life, int exp[], Player P){
    system ("CLS");
    string account_name;
    string pwd;

    // first time user
    if(username.empty() == true || password.empty() == true){
        cout << "Please enter your account name (no spaces in between): ";
        cin >> account_name;
        cout << "Please enter your password (no spaces in between): ";
        cin >> pwd;
        username = account_name;
        password = pwd;
    }

    cout << "Saving the player's data..." << endl;
    ofstream fout;

    // overwrite the user's data
    // saving order: account name, password, name, level, attack point, defend point, life point
    fout.open("player_" + username + "_data" + ".txt", ofstream::trunc); // reference: http://www.cplusplus.com/reference/fstream/ofstream/open/
    fout << username << " " << password << " " << P.getName() << " " << P.getLevel() << " " << P.getAtkPt()
    << " " << P.getDefPt() << " " << P.getLife() << " " << P.getExp() << " "<< P.getMoney() << " " << P.getDiamond() << endl;
    fout.close();

    // debug
    cout << "overwriting these data..." << endl;
    cout << "----------------------------" << endl;
    cout << "User name: "<< username << endl;
    cout << "Password: " << password << endl;
    cout << "Name: " << P.getName() << endl;
    cout << "Level: " << P.getLevel() << endl;
    cout << "Attack: " << P.getAtkPt() << endl;
    cout << "Defend: " << P.getDefPt() << endl;
    cout << "Life point: " << P.getLife() << endl;
    cout << "Exp: " << P.getExp() << endl;
    cout << "Money: " << P.getMoney() << endl;
    cout << "Diamond: " << P.getDiamond() << endl;
    cout << "----------------------------" << endl;

    // disable for now
    // create an account for user if they doesn't have one
    // fout.open("player_" + account_name + "_info" + ".txt");
    // fout << account_name << " " << password;
    // fout.close();

    sleep(1600); // delay to simulate loading
    cout << "Data is saved..." << endl;
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
        diamond = 0;

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
            fin >> readUser >> readPwd >> name >> level >> attack >> defend >> life >> exp >> money >> diamond;

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

    return status;
}
