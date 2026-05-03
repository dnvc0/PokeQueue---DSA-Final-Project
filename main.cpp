// main file for PokeQueue - DSA Final Project
#include <iostream>
#include <cstdlib>  
#include <vector>
#include <stack>
#include <ctime>
#include <queue>
#include <string>   
using namespace std;

void clearScreen() {
    system("cls");
}

class Move {
    private:
        string moveName;
        int prioLvl;
        int damage;
    public:
        Move() {
            moveName = "";
            prioLvl = 0;
            damage = 0;
        }

        Move(string name, int priority, int dmg) {
            moveName = name;
            prioLvl = priority;
            damage = dmg;
        }

        string getName() {return moveName;}
        int getPriority() {return prioLvl;}
        int getDamage() {return damage;}

        void displayMove() {
            cout << moveName << " (Priority: " << prioLvl << ", Damage: " << damage << ")" << endl;
        }
};

class Pokemon { // hindi pa nai-implement yung faint condtions
    private:
        string name;
        int hp;
        int speed;
        bool isAlive;
        bool isFainted;
        Move moveSet[4];
    public:
        Pokemon(string n, int h, int s) {
            name = n;
            hp = h;
            speed = s;
            isAlive = true;
            isFainted = false;
        }

        string getName() {return name;}
        int getHP() {return hp;}
        int getSpeed() {return speed;}
        bool getIsAlive() {return isAlive;}
        Move getMove(int index) {return moveSet[index];}

        void displayPokemon() {
            cout << name << " (HP: " << hp << ", Speed: " << speed << ")" << endl;
        }

        void takeDamage(int dmg) {
            hp -= dmg;
            if (hp <= 0) {
                hp = 0;
                isAlive = false;
                cout << name << " has been defeated!" << endl;
            }
        }

        void setMove(int index, Move move) {
            moveSet[index] = move;
        }

        void addMove(Move move, int index) {
            moveSet[index] = move;
        }
};

void MoveQueue() {}

void PriorityMoveQueue() {}

void ActionStack() {}

void BattleSystem() {}

int main() {
    cout << "================Welcome to PokeQueue!====================" << endl;
    cout << "This is a turn-based battle system inspired by Pokemon." << endl;
    cout << "In this game, you will create a team of Pokemon and battle against other trainers." << endl;
    cout << "Do you want to start a new game? (y/n)" << endl;
    char choice;
    cin >> choice;
    if (choice == 'y') {
        cout << "Great! Let's get started!" << endl;
    } else {
        cout << "Maybe next time!" << endl;
        return 0;
    }

    while (true) {
        clearScreen();
        cout << "MAIN MENU" << endl;
        cout << "1. New Battle" << endl;
        cout << "2. How to Play" << endl;
        cout << "3. Exit game" << endl;
        int option;
        cin >> option;
        switch (option) {
            case 1:
                // yung six pokemon options dito ish-show
                // tapos may random enemy pokemon na lalaban sa player and then:
                BattleSystem();
                break;
            case 2:
                cout << "How to Play:" << endl; // instructions dito
                break;
            case 3:
                cout << "Thanks for playing!" << endl;
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}
