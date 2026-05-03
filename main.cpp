// main file for PokeQueue - DSA Final Project
#include <iostream>
#include <cstdlib>  
#include <vector>
#include <stack>
#include <queue>
#include <ctime> 
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

void BattleSystem() {
    clearScreen();
    cout << "=== 1v1 BATTLE START ===\n";

    // ===== PLAYER POKEMON =====
    Pokemon player("Pikachu", 100, 90);
    player.setMove(0, Move("Quick Attack", 2, 15));
    player.setMove(1, Move("Thunderbolt", 1, 25));
    player.setMove(2, Move("Iron Tail", 1, 20));
    player.setMove(3, Move("Electro Ball", 1, 18));

    // ===== RANDOM ENEMY =====
    Pokemon enemy;
    int randEnemy = rand() % 3;

    if (randEnemy == 0) {
        enemy = Pokemon("Charmander", 100, 65);
        enemy.setMove(0, Move("Scratch", 1, 10));
        enemy.setMove(1, Move("Ember", 1, 20));
        enemy.setMove(2, Move("Flame Burst", 1, 18));
        enemy.setMove(3, Move("Slash", 2, 15));
    }
    else if (randEnemy == 1) {
        enemy = Pokemon("Squirtle", 110, 50);
        enemy.setMove(0, Move("Tackle", 1, 10));
        enemy.setMove(1, Move("Water Gun", 1, 20));
        enemy.setMove(2, Move("Bubble", 1, 18));
        enemy.setMove(3, Move("Aqua Jet", 2, 15));
    }
    else {
        enemy = Pokemon("Bulbasaur", 120, 45);
        enemy.setMove(0, Move("Tackle", 1, 10));
        enemy.setMove(1, Move("Vine Whip", 1, 20));
        enemy.setMove(2, Move("Razor Leaf", 1, 18));
        enemy.setMove(3, Move("Quick Attack", 2, 15));
    }

    // ===== STACK (HISTORY) =====
    stack<string> history;

    // ===== BATTLE LOOP =====
    while (player.getIsAlive() && enemy.getIsAlive()) {
        clearScreen();

        cout << "=== BATTLE ===\n\n";

        cout << "Your Pokemon: ";
        player.displayPokemon();

        cout << "Enemy Pokemon: ";
        enemy.displayPokemon();

        // ===== PLAYER MOVE =====
        cout << "\nChoose Move:\n";
        for (int i = 0; i < 4; i++) {
            cout << i + 1 << ". ";
            player.getMove(i).displayMove();
        }

        int choice;
        cin >> choice;

        if (choice < 1 || choice > 4) {
            cout << "Invalid move!\n";
            system("pause");
            continue;
        }

        Move playerMove = player.getMove(choice - 1);

        // ===== RANDOM ENEMY MOVE =====
        Move enemyMove = enemy.getMove(rand() % 4);

        cout << "\n--- Turn Start ---\n";

        // ===== PRIORITY + SPEED LOGIC =====
        bool playerFirst;

        if (playerMove.getPriority() > enemyMove.getPriority()) {
            playerFirst = true;
        }
        else if (playerMove.getPriority() < enemyMove.getPriority()) {
            playerFirst = false;
        }
        else {
            // same priority → check speed
            playerFirst = player.getSpeed() >= enemy.getSpeed();
        }

        // ===== EXECUTION =====
        if (playerFirst) {
            cout << player.getName() << " used " << playerMove.getName() << "!\n";
            enemy.takeDamage(playerMove.getDamage());
            history.push(player.getName() + " used " + playerMove.getName());

            if (enemy.getIsAlive()) {
                cout << enemy.getName() << " used " << enemyMove.getName() << "!\n";
                player.takeDamage(enemyMove.getDamage());
                history.push(enemy.getName() + " used " + enemyMove.getName());
            }
        } else {
            cout << enemy.getName() << " used " << enemyMove.getName() << "!\n";
            player.takeDamage(enemyMove.getDamage());
            history.push(enemy.getName() + " used " + enemyMove.getName());

            if (player.getIsAlive()) {
                cout << player.getName() << " used " << playerMove.getName() << "!\n";
                enemy.takeDamage(playerMove.getDamage());
                history.push(player.getName() + " used " + playerMove.getName());
            }
        }

        cout << "--- Turn End ---\n";
        system("pause");
}

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

    srand(time(0));
    return 0;
}
