#include <iostream>
#include <string>
#include <iomanip>
#include <fstream> // file IO
#include <sstream>
#include <algorithm>
#include <time.h>
#include <stdlib.h> // reference: https://mathbits.com/MathBits/CompSci/Introduction/clear.htm

#include "player.h"

void fileOpen(int level[], double attack[], double defend[], int &count);
bool login(string &userName, string &passward, Player&);
void menu(int level[], double attack[], double defend[], int life, int point, int index, Player&);
void battle(int option, int level[], double attack[], double defend[], int life, int point, int index, Player&);
void check_status(int level[], double attack[], double defend[], int life, int point, int index, Player);
void updateInfo(int level, double attack, double defend, int life, Player&);
bool save_player(string username, string passward, int level[], double attack[], double defend[], int life, int point, int index, Player);
bool load_player();
void sleep(unsigned int mseconds);

using namespace std;

int main()
{
    const int SIZE = 100;
    int count = 0,
        life = 100,
        level[SIZE],
        point = 0,
        index = 0;
    double attack[SIZE],
           defend[SIZE];

    // read the context of the game
    fileOpen(level, attack, defend, count);

    // variables for player
    Player P;
    string name;

    // login information
    string username;
    string passward;

    cout << "------------------------------------------" << endl;
    cout << "Welcome to Tony's game!" << endl;
    cout << "Please log in your account to continue the game" << endl;
    cout << "------------------------------------------" << endl;
    bool hasAccount = login(username, passward, P);

    if(hasAccount){
        system ("CLS");
        cout << "------------------------------------------" << endl;
        cout << "Welcome back " << username << "!" << endl;
        cout << "------------------------------------------" << endl;
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
        cout << "Hello "<< name << ", now you are in level "<< level[0] << " , you are ready to have an adventure!" << endl;
        cout << "This game has 5 level. if you accomplish all of them. You are the winner!" << endl;
    }

    // enter menu to start the selection
    menu(level, attack, defend, life, point, index, P);

    char choice;
    cout << "Would you like to save your progress? (Y/N)";
    cin >> choice;
    if (choice == 'y' || choice == 'Y'){
        save_player(username, passward, level, attack, defend, life, point, index, P); // save player's information
    }

    return 0;
}

void fileOpen(int level[], double attack[], double defend[], int &count)
{
    fstream inputFile;

    // open the file
    inputFile.open("Level_List.txt");

    // read the file
    while (inputFile >> level[count] >> attack[count] >> defend[count])
    {
        count++;
    }

    // close the file
    inputFile.close();
}

void menu(int level[], double attack[], double defend[], int life, int point, int index, Player &P)
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
                    battle(option, level, attack, defend, life, point, index, P);
                    break;
                case 6:
                    cout << "Game is over." << endl;
                    break;
                case 7:
                    check_status(level, attack, defend, life, point, index, P);
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

void battle(int option, int level[], double attack[], double defend[], int life, int point, int index, Player &P)
{
    // default value (level 1)
    char choice;
    double damage = 2;
    double monsterLife = 5;

    // adjust the level based on user's input
    if (option == 2){
        damage = 5;
        monsterLife = 10;
    }
    else if(option == 3){
        damage = 15;
        monsterLife = 20;
    }
    else if(option == 4){
        damage = 40;
        monsterLife = 50;
    }
    else if(option == 5){
        damage = 150;
        monsterLife = 500;
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
        game_defend = P.getDefPt();

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
            point = point + 1;
            cout << "Now you have point: " << point <<  endl;
    }
    if (point % 2 != 0)
    {
            game_level = game_level + 1;
            game_life = game_life + 15;
            cout << "Congratulations! Level up!!!" << endl;
            cout << "===========================================" << endl;
            cout << "Level : " << game_level << endl;
            cout << "Attack: " << attack[game_level] << endl;
            cout << "Defend: " << defend[game_level] << endl;
            cout << "===========================================" << endl;
    }

    // save the result
    updateInfo(game_level, attack[game_level], defend[game_level], game_life, P);

    cout << "Do you want to back to the menu?(Y/N)";
    cin >> choice;
    if(choice == 'Y' || choice == 'y')
        menu(level, attack, defend, life, point, index, P);
}


void check_status(int level[], double attack[], double defend[], int life, int point, int index, Player P){
    system ("CLS");
    cout << "*******************************************" << endl;
    cout << "Checking status..." << endl;
    // delay to simulate loading
    sleep(1900);
    cout << "=  Your current Level is: " << P.getLevel() << endl;
    cout << "=  Your life now is: " << P.getLife() << endl;
    cout << "=  Now your attack point is: " << P.getAtkPt() << endl;
    cout << "=  and defend point: " << P.getDefPt() << endl;
    cout << "*******************************************" << endl;
    system ("PAUSE");
    menu(level, attack, defend, life, point, index, P);
}

// ask user to create an account for saving the data
// if the user already has an account, overwrite the data
bool save_player(string username, string passward, int level[], double attack[], double defend[], int life, int point, int index, Player P){
    system ("CLS");
    string account_name;
    string pwd;

    // first time user
    if(username.empty() == true || passward.empty() == true){
        cout << "Please enter your account name (no spaces in between): ";
        cin >> account_name;
        cout << "Please enter your password (no spaces in between): ";
        cin >> pwd;
        username = account_name;
        passward = pwd;
    }

    cout << "Saving the player's data..." << endl;
    ofstream fout;

    // overwrite the user's data
    // saving order: account name, password, name, level, attack point, defend point, life point
    fout.open("player_" + username + "_data" + ".txt", ofstream::trunc); // reference: http://www.cplusplus.com/reference/fstream/ofstream/open/
    fout << username << " " << passward << " " << P.getName() << " " << P.getLevel() << " " << P.getAtkPt() << " " << P.getDefPt() << " " << P.getLife() << endl;
    fout.close();

    // debug
    cout << "overwriting these data..." << endl;
    cout << "----------------------------" << endl;
    cout << username << endl;
    cout << passward << endl;
    cout << P.getName() << endl;
    cout << P.getLevel() << endl;
    cout << P.getAtkPt() << endl;
    cout << P.getDefPt() << endl;
    cout << P.getLife() << endl;
    cout << "----------------------------" << endl;

    // disable for now
    // create an account for user if they doesn't have one
    // fout.open("player_" + account_name + "_info" + ".txt");
    // fout << account_name << " " << passward;
    // fout.close();

    sleep(1600); // delay to simulate loading
    cout << "Data is saved..." << endl;
    return true;
}

bool load_player(){
    return true;
}


// reference: https://ubuntuforums.org/showthread.php?t=296142
void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void updateInfo(int level, double attack, double defend, int life, Player &P){
    P.setLevel(level);
    P.setAtkpt(attack);
    P.setDefpt(defend);
    P.setLife(life);
    sleep(1000); // delay to simulate loading
}

// login in user's account
bool login(string &username, string &passward, Player &P){
    fstream fin;
    bool status = false;

    string readUser = "",
            readPwd = "",
               name = "";
    int level = 0,
        life = 100,
        attack = 1,
        defend = 1;

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
        cout << "Please enter your passward:";
        cin >> passward;
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
            // once the user account is found, check the passward next
            fin >> readUser >> readPwd >> name >> level >> attack >> defend >> life;

            // // debug
            // cout << "readUser: [" << readUser << "]" << endl;
            // cout << "readPwd: [" << readPwd << "]" << endl;
            // cout << "name: [" << name << "]" << endl;
            // cout << "level: [" << level << "]" << endl;
            // cout << "attack: [" << attack << "]" << endl;
            // cout << "defend: ["<< defend << "]" << endl;
            // cout << "life: [" << life << "]" << endl;

            // if the username and passward match, it log in sucessfully
            if(readUser == username && readPwd == passward){
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
    P.setPwd(passward);
    P.setName(name);
    P.setLevel(level);
    P.setAtkpt(attack);
    P.setDefpt(defend);
    P.setLife(life);

    return status;
}
