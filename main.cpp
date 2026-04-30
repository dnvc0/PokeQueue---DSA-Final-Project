// main file for PokeQueue - DSA Final Project
#include <iostream>
#include <cstdlib>
using namespace std;

void clearScreen() {
    system("cls");
}

void Move() {}

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
        cout << "What would you like to do?" << endl;
        cout << "1. Battle another trainer" << endl;
        cout << "2. View your team" << endl;
        cout << "3. Exit game" << endl;
        int option;
        cin >> option;
        switch (option) {
            case 1:
                BattleSystem();
                break;
            case 2:
                cout << "Your team:" << endl;
                // code to display team goes here
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
