// main file for PokeQueue - DSA Final Project
#include <iostream>
#include <cstdlib>  
#include <queue>
#include <stack>
#include <ctime>
#include <string> 
#include <conio.h>  
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

        string getMoveName() const {return moveName;}
        int getPriority() const {return prioLvl;}
        int getDamage() const {return damage;}

        void displayMove() const {
            cout << moveName << "\t(Priority: " << prioLvl << ", Damage: " << damage << ")" << endl;
        }
};

class Pokemon { // hindi pa nai-implement yung faint condtions
    private:
        string name;
        int hp;
        int maxHP;
        int speed;
        bool isAlive;
        bool isFainted;
        Move moveSet[4];
    public:
        Pokemon() {
            name = "";
            hp = 0;
            maxHP = 0;
            speed = 0;
            isAlive = false;
            isFainted = true;
        }

        Pokemon(string n, int h, int s) {
            name = n;
            hp = h;
            maxHP = h;
            speed = s;
            isAlive = true;
            isFainted = false;
        }

        string getName() const {return name;}
        int getHP() const {return hp;}
        int getMaxHP() const {return maxHP;}
        int getSpeed() const {return speed;}
        bool getIsAlive() const {return isAlive;}
        Move getMove(int index) const {return moveSet[index];}

        void takeDamage(int dmg) {
            hp -= dmg;
            if (hp <= 0) {
                hp = 0;
                isAlive = false;
                cout << "> KO! " << name << " has been defeated!" << endl;
            }
        }

        void setMove(int index, Move move) {
            moveSet[index] = move;
        }

        void addMove(Move move, int index) {
            moveSet[index] = move;
        }
};

void MoveQueue(Pokemon &player, Pokemon &enemy, Move &playerMove, Move &enemyMove) {
    while (true) {
        cout << endl;
        cout << string(42, '-') << endl;
        cout << "Choose Move:\n";
        for (int i = 0; i < 4; i++) {
            cout << i + 1 << ". ";
            player.getMove(i).displayMove();
        }
        cout << string(42, '-') << endl;

        int choice;
        cin >> choice;

        if (choice < 1 || choice > 4) {
            cout << "Invalid move!\n";
            system("pause");
            continue;
        }

        playerMove = player.getMove(choice - 1);
        enemyMove = enemy.getMove(rand() % 4);
        break;
    }
}

void PriorityMoveQueue(const Move &playerMove, const Move &enemyMove, const Pokemon &player, const Pokemon &enemy, bool &playerFirst) {
    if (playerMove.getPriority() > enemyMove.getPriority()) {
        playerFirst = true;
    }
    else if (playerMove.getPriority() < enemyMove.getPriority()) {
        playerFirst = false;
    }
    else {
        playerFirst = player.getSpeed() >= enemy.getSpeed();
    }
}

void ActionStack(stack<string> &history, const string &action) {
    history.push(action);
}

void createRandomEnemy(Pokemon &enemy) {
    int randEnemy = rand() % 3;

    if (randEnemy == 0) {
        enemy = Pokemon("Charmander", 100, 65);
        enemy.setMove(0, Move("Scratch", 1, 10));
        enemy.setMove(1, Move("Ember", 1, 20));
        enemy.setMove(2, Move("Flame Burst", 1, 18));
        enemy.setMove(3, Move("Slash", 2, 15));
    }
    else if (randEnemy == 1) {
        enemy = Pokemon("Squirtle", 100, 50);
        enemy.setMove(0, Move("Tackle", 1, 10));
        enemy.setMove(1, Move("Water Gun", 1, 20));
        enemy.setMove(2, Move("Bubble", 1, 18));
        enemy.setMove(3, Move("Aqua Jet", 2, 15));
    }
    else {
        enemy = Pokemon("Bulbasaur", 100, 45);
        enemy.setMove(0, Move("Tackle", 1, 10));
        enemy.setMove(1, Move("Vine Whip", 1, 20));
        enemy.setMove(2, Move("Razor Leaf", 1, 18));
        enemy.setMove(3, Move("Quick Attack", 2, 15));
    }
}

void displayHPBar(int hp, int maxHP, int speed) {
    int bars = (hp * 20) / maxHP;
    cout << "HP: [";
    for (int i = 0; i < 20; i++) {
        if (i < bars) cout << "#";
        else cout << "-";
    }
    cout << "] " << hp << "/" << maxHP << " Speed: " << speed << endl;
}

void BattleSystem() {
    // ===== PLAYER POKEMON =====
    Pokemon player("Pikachu", 100, 90);
    player.setMove(0, Move("Quick Attack", 2, 15));
    player.setMove(1, Move("Thunderbolt", 1, 25));
    player.setMove(2, Move("Iron Tail", 1, 20));
    player.setMove(3, Move("Electro Ball", 1, 18));

    // ===== RANDOM ENEMY =====
    Pokemon enemy;
    createRandomEnemy(enemy);

    // ===== STACK (HISTORY) =====
    stack<string> history;

    // ===== BATTLE LOOP =====
    while (player.getIsAlive() && enemy.getIsAlive()) {
        clearScreen();
        cout << string(48, '-') << endl;
        cout << " ______ _______ _______ _______ _____   _______" << endl; 
        cout << "|   __ \\   _   |_     _|_     _|     |_|    ___|" << endl;
        cout << "|   __ <       | |   |   |   | |       |    ___|" << endl;
        cout << "|______/___|___| |___|   |___| |_______|_______|" << endl;
        cout << string(48, '-') << endl;

        cout << "\nYOUR POKEMON: \n";
        cout << player.getName() << endl;
        displayHPBar(player.getHP(), player.getMaxHP(), player.getSpeed());

        cout << "\nENEMY POKEMON: \n";
        cout << enemy.getName() << endl;
        displayHPBar(enemy.getHP(), enemy.getMaxHP(), enemy.getSpeed());

        // ===== PLAYER MOVE =====
        Move playerMove;
        Move enemyMove;
        MoveQueue(player, enemy, playerMove, enemyMove);

        cout << endl << string(15, '-') << " Turn Start " << string(15, '-') << endl;

        // ===== PRIORITY + SPEED LOGIC =====
        bool playerFirst;
        PriorityMoveQueue(playerMove, enemyMove, player, enemy, playerFirst);

        // ===== EXECUTION =====
        if (playerFirst) {
            cout << "> " << player.getName() << " used " << playerMove.getMoveName() << "!\n";
            enemy.takeDamage(playerMove.getDamage());
            history.push("> " + player.getName() + " used " + playerMove.getMoveName());

            if (enemy.getIsAlive()) {
                cout << "> " << enemy.getName() << " used " << enemyMove.getMoveName() << "!\n";
                player.takeDamage(enemyMove.getDamage());
                history.push("> " + enemy.getName() + " used " + enemyMove.getMoveName());
            }
        } else {
            cout << "> " << enemy.getName() << " used " << enemyMove.getMoveName() << "!\n";
            player.takeDamage(enemyMove.getDamage());
            history.push("> " + enemy.getName() + " used " + enemyMove.getMoveName());

            if (player.getIsAlive()) {
                cout << "> " << player.getName() << " used " << playerMove.getMoveName() << "!\n";
                enemy.takeDamage(playerMove.getDamage());
                history.push("> " + player.getName() + " used " + playerMove.getMoveName());
            }
        }

        cout << string(15, '-') << "  Turn End  " << string(15, '-') << "\n\n";
        system("pause");
    }

    // ===== RESULT =====
    cout << endl << string(16, '-') << " RESULT  " << string(17, '-') << endl;
    if (player.getIsAlive()) cout << "You Win!\n";
    else cout << "You Lose!\n";

    // ===== HISTORY =====
    cout << endl << string(16, '-') << " HISTORY " << string(17, '-') << endl;
    while (!history.empty()) {
        cout << history.top() << endl;
        history.pop();
    }

    cout << endl;
    system("pause");
}

int main() {
    srand(time(0));

    cout << string(81, '=') << endl;
    cout << " _______  _______  ___   _  _______  _______  __   __  _______  __   __  _______ " << endl;
    cout << "|       ||       ||   | | ||       ||       ||  | |  ||       ||  | |  ||       |" << endl;
    cout << "|    _  ||   _   ||   |_| ||    ___||   _   ||  | |  ||    ___||  | |  ||    ___|" << endl;
    cout << "|   |_| ||  | |  ||      _||   |___ |  | |  ||  |_|  ||   |___ |  |_|  ||   |___ " << endl;
    cout << "|    ___||  |_|  ||     |_ |    ___||  |_|  ||       ||    ___||       ||    ___|" << endl;
    cout << "|   |    |       ||    _  ||   |___ |      | |       ||   |___ |       ||   |___ " << endl;
    cout << "|___|    |_______||___| |_||_______||____||_||_______||_______||_______||_______|" << endl;
    cout << string(81, '=') << endl;
    cout << "\nThis is a turn-based battle system inspired by Pokemon." << endl;
    cout << "In this game, you will choose a pokemon to duel against an enemy pokemon." << endl;
    cout << "\nPress any key to start..." << endl;
    _getch();

    while (true) {
        clearScreen();
        cout << "              _                                 " << endl;
        cout << "  /\\/\\   __ _(_)_ __     /\\/\\   ___ _ __  _   _ " << endl;
        cout << " /    \\ / _` | | '_ \\   /    \\ / _ \\ '_ \\| | | |" << endl;
        cout << "/ /\\/\\ \\ (_| | | | | | / /\\/\\ \\  __/ | | | |_| |" << endl;
        cout << "\\/    \\/\\__,_|_|_| |_| \\/    \\/\\___|_| |_|\\__,_|" << endl;
        cout << "\n1. New Battle" << endl;
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
                cout << " _____ _____ _ _ _    _____ _____    _____ __    _____ __ __ " << endl;
                cout << "|  |  |     | | | |  |_   _|     |  |  _  |  |  |  _  |  |  |" << endl;
                cout << "|     |  |  | | | |    | | |  |  |  |   __|  |__|     |_   _|" << endl;
                cout << "|__|__|_____|_____|    |_| |_____|  |__|  |_____|__|__| |_|  " << endl;
                cout << "\n1. Choose a Pokemon to battle against an enemy Pokemon." << endl;
                cout << "2. Each turn, you and the enemy will use moves to attack each other." << endl;
                cout << "3. The goal is to reduce the enemy's HP to 0 before your Pokemon's HP reaches 0.\n\n";
                system("pause");
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
