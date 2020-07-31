#include <iostream>
#include <string>
#include <iomanip>
#include <fstream> // file IO
#include <sstream>

#include <time.h>
#include "player.h"

void fileOpen(int level[], double attack[], double defend[], int &count);
void menu(int level[], double attack[], double defend[], int life, int point, int index, Player&);
void battle(int option, int level[], double attack[], double defend[], int life, int point, int index, Player&);
void check_status(int level[], double attack[], double defend[], int life, int point, int index, Player);
void updateInfo(int level, double attack, double defend, int life, Player&);
bool save_player(int level[], double attack[], double defend[], int life, int point, int index, Player);
bool load_player();
void sleep(unsigned int mseconds);

using namespace std;

int main()
{
    const int SIZE = 100;
    int count = 0;
    string name;
    int life = 100,
        level[SIZE],
        point = 0,
        index = 0;
    double attack[SIZE],
           defend[SIZE];

    Player P("",0,0,0,0);

    // read the context of the game
    fileOpen(level, attack, defend, count);

    // welcome message
    cout << "------------------------------------------" << endl;
    cout << "Welcome to Tony's game!" << endl;
    cout << "Please enter your name: " << endl;
    cout << "------------------------------------------" << endl;
    cout << "Enter name: ";
    cin >> name;
    P.setName(name);
    cout << "\n------------------------------------------" << endl;
    cout << "Hello "<< name << ", now you are in level "<< level[0] << " , you are ready to have an adventure!" << endl;
    cout << "This game has 5 level. if you accomplish all of them. You are the winner!" << endl;

    // enter menu to start the selection
    menu(level, attack, defend, life, point, index, P);

    // save player's information
    save_player(level, attack, defend, life, point, index, P);

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

    cout << "------------------------------------------------" << endl;
    cout << "=  You are in story " << option << "." << endl;
    cout << "=  Your current Level is: " << level[index] << endl;
    cout << "=  Your life now is: " << life << endl;
    cout << "=  Now your attack point is: " << attack[index] << endl;
    cout << "=  and defend point: " << defend[index] << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Here is a monster. Please start attacking." << endl;
    do{
        cout << "Wanna attack?(Y/N)";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            monsterLife = monsterLife - attack[index];
            cout << "You attack the monster, now he remains " << monsterLife << " point of life" << endl;
            life = life - damage + defend[index];
            cout << "You are attacked by monster. Now your life is remaining " << life << " points." << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
            if (life < 1)
            {
                cout << "You are dead. Game over!" << endl;
                cout << " +_+" << endl;
                cout << "++++++++++++++++++++++++++++++++++++++" << endl;
                break;
            }
        }
        if (choice == 'n' || choice == 'N'){
            life = life - (damage + 2) + defend[index];
            cout << "The monster attacks you directly!!! Now your life is remaining " << life << " points. Please ATTACK back!!!" << endl;
            break;
        }
    } while(monsterLife > 0);

    if (life > 0 && monsterLife < 1)
    {
            cout << "**********************************" << endl;
            cout << "You defeat the monster //" << endl;
            cout << "**********************************" << endl;
            point = point + 1;
            cout << "Now you have point: " << point <<  endl;
    }
    if (point % 2 != 0)
    {
            index = index + 1;
            life = life + 15;
            cout << "Congratulations! Level up!!!" << endl;
            cout << "===========================================" << endl;
            cout << "Level : " << level[index] << endl;
            cout << "Attack: " << attack[index] << endl;
            cout << "Defend: " << defend[index] << endl;
            cout << "===========================================" << endl;
    }

    // save the result
    updateInfo(level[index], attack[index], defend[index], life, P);

    cout << "Do you want to back to the menu?(Y/N)";
    cin >> choice;
    if(choice == 'Y' || choice == 'y')
        menu(level, attack, defend, life, point, index, P);
}


void check_status(int level[], double attack[], double defend[], int life, int point, int index, Player P){
    cout << "*******************************************" << endl;
    cout << "Checking status..." << endl;
    // delay to simulate loading
    sleep(1900);
    cout << "=  Your current Level is: " << level[index] << endl;
    cout << "=  Your life now is: " << life << endl;
    cout << "=  Now your attack point is: " << attack[index] << endl;
    cout << "=  and defend point: " << defend[index] << endl;
    cout << "*******************************************" << endl;
    cout << endl << endl;
    menu(level, attack, defend, life, point, index, P);
}

bool save_player(int level[], double attack[], double defend[], int life, int point, int index, Player P){
    cout << "Saving the player's data..." << endl;
    ofstream fout;
    fout.open("player-" + P.getName() + ".txt");
    fout << P.getName() << " " << P.getLevel() << " " << P.getAtkPt() << " " << P.getDefPt() << " " << P.getLife() << endl;
    fout.close();
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
    P.setLife(life);
    P.setAtkpt(attack);
    P.setDefpt(defend);

    sleep(1000); // delay to simulate loading

    // // debug
    // cout << "################" << endl;
    // cout << P.getName() << endl;
    // cout << P.getLevel() << endl;
    // cout << P.getLife() << endl;
    // cout << P.getAtkPt() << endl;
    // cout << P.getDefPt() << endl;
    // cout << "################" << endl;
}
