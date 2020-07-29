#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <time.h>

void fileOpen(int level[], double attack[], double defend[], int &count);

void menu(int level[], double attack[], double defend[], int life, int point, int index);
void battle(int option, int level[], double attack[], double defend[], int life, int point, int index);
void check_status(int level[], double attack[], double defend[], int life, int point, int index);
bool save_Player();
bool load_Player();
void sleep(unsigned int mseconds);

using namespace std;

int main()
{
    const int SIZE = 100;
    int count = 0;
    string name;
    // char choice;
    int life = 100,
        level[SIZE],
        point = 0,
        index = 0;
    double attack[SIZE],
           defend[SIZE];

    fileOpen(level, attack, defend, count);
    cout << "------------------------------------------" << endl;
    cout << "Welcome to Tony's game!" << endl;
    cout << "Please enter your name: " << endl;
    cout << "------------------------------------------" << endl;
    cout << "Enter name:";
    cin >> name;
    cout << "\n------------------------------------------" << endl;
    cout << "Hello "<< name << ", now you are in " << level[0] << " level, you are ready to have an adventure!" << endl;
    cout << "This game has 5 level. if you accomplish all of them. You are the winner!" << endl;
    menu(level, attack, defend, life, point, index);

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

void menu(int level[], double attack[], double defend[], int life, int point, int index)
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
        // cin >> choose;
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
                    battle(option, level, attack, defend, life, point, index);
                    break;
                case 6:
                    cout << "Game is over." << endl;
                    break;
                case 7:
                    check_status(level, attack, defend, life, point, index);
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

void battle(int option, int level[], double attack[], double defend[], int life, int point, int index)
{
    //default value (level 1)
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
    cout << "=  Now my attack point is: " << attack[index] << endl;
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

    cout << "Do you want to back to the menu?(Y/N)";
    cin >> choice;
    if(choice == 'Y' || choice == 'y')
        menu(level, attack, defend, life, point, index);
}


void check_status(int level[], double attack[], double defend[], int life, int point, int index){
    cout << "*******************************************" << endl;
    cout << "Checking status..." << endl;
    
    // delay to simulate loading
    sleep(2000);
     
    cout << "*******************************************" << endl;
    cout << endl << endl;
    menu(level, attack, defend, life, point, index);
}

bool save_Player(){
    return true;
}

bool load_Player(){
    return true;
}


// reference: https://ubuntuforums.org/showthread.php?t=296142
void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}