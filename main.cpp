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

enum StatusType { NONE, FLINCH, SLEEP, BURN, POISON, PARALYZE, SHIELD_BREAK, FAIL_IF_HIT };
class Move {
    private:
        string moveName;
        int prioLvl;
        int damage;
        StatusType status;
        int statusChance; 
    public:
        Move() : moveName(""), prioLvl(0), damage(0), status(NONE), statusChance(0) {}
        Move(string name, int priority, int dmg, StatusType st = NONE, int chance = 0) {
            moveName = name;
            prioLvl = priority;
            damage = dmg;
            status = st;
            statusChance = chance;
        }

        string getMoveName() const { return moveName; }
        int getPriority() const { return prioLvl; }
        int getDamage() const { return damage; }
        StatusType getStatus() const { return status; }
        int getStatusChance() const { return statusChance; }

        void displayMove() const {
            cout << moveName << "\t(Prio: " << prioLvl << ", Dmg: " << damage << ")";
            if (status != NONE) cout << " [" << statusChance << "% Effect]";
            cout << endl;
        }
};

class Pokemon { // hindi pa nai-implement yung faint condtions
    private:
        string name;
        int hp;
        int maxHP;
        int speed;
        int turnCount;
        bool isAlive;
        bool isFainted;
        Move moveSet[4];
    public:
        Pokemon() {
            name = "";
            hp = 0;
            maxHP = 0;
            turnCount = 0;
            speed = 0;
            isAlive = false;
            isFainted = true;
        }

        Pokemon(string n, int h, int s) {
            name = n;
            hp = h;
            maxHP = h;
            speed = s;
            turnCount = 0;
            isAlive = true;
            isFainted = false;
        }

        string getName() const {return name;}
        int getHP() const {return hp;}
        int getMaxHP() const {return maxHP;}
        int getSpeed() const {return speed;}
        bool getIsAlive() const {return isAlive;}
        Move getMove(int index) const {return moveSet[index];}
        int getTurnCount() const { return turnCount; }
        void incrementTurn() { turnCount++; }

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

    if (randEnemy == 0) { // Smeargle: The Status Lead
        enemy = Pokemon("Smeargle", 314, 75);
        enemy.setMove(0, Move("Fake Out", 3, 40, FLINCH, 100));
        enemy.setMove(1, Move("Wicked Torque", 0, 80, SLEEP, 10));
        enemy.setMove(2, Move("Gunk Shot", 0, 120, POISON, 30));
        enemy.setMove(3, Move("Dragon Tail", -6, 60));
    }
    else if (randEnemy == 1) { // Mew: The Heavy Hitter
        enemy = Pokemon("Mew", 404, 100);
        enemy.setMove(0, Move("Focus Punch", -4, 150, FAIL_IF_HIT, 100));
        enemy.setMove(1, Move("Flamethrower", 0, 90, BURN, 10));
        enemy.setMove(2, Move("Thunderbolt", 0, 90, PARALYZE, 10));
        enemy.setMove(3, Move("Fake Out", 3, 40, FLINCH, 100));
    }
    else { // Dragonite: The Tank
        enemy = Pokemon("Dragonite", 386, 80);
        enemy.setMove(0, Move("Extreme Speed", 2, 80));
        enemy.setMove(1, Move("Gunk Shot", 0, 120, POISON, 30));
        enemy.setMove(2, Move("Flamethrower", 0, 90, BURN, 10));
        enemy.setMove(3, Move("Dragon Tail", -6, 60));
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
    // ===== POKEMON SELECTION =====
    Pokemon roster[4];
    
    // 1. Smeargle
    roster[0] = Pokemon("Smeargle", 314, 75);
    roster[0].setMove(0, Move("Fake Out", 3, 40, FLINCH, 100));
    roster[0].setMove(1, Move("Wicked Torque", 0, 80, SLEEP, 10));
    roster[0].setMove(2, Move("Gunk Shot", 0, 120, POISON, 30));
    roster[0].setMove(3, Move("Dragon Tail", -6, 60));

    // 2. Lucario
    roster[1] = Pokemon("Lucario", 344, 90);
    roster[1].setMove(0, Move("Extreme Speed", 2, 80));
    roster[1].setMove(1, Move("Feint", 2, 30, SHIELD_BREAK, 100));
    roster[1].setMove(2, Move("Sucker Punch", 1, 70));
    roster[1].setMove(3, Move("Thunderbolt", 0, 90, PARALYZE, 10));

    // 3. Mew
    roster[2] = Pokemon("Mew", 404, 100);
    roster[2].setMove(0, Move("Fake Out", 3, 40, FLINCH, 100));
    roster[2].setMove(1, Move("Focus Punch", -4, 150, FAIL_IF_HIT, 100));
    roster[2].setMove(2, Move("Flamethrower", 0, 90, BURN, 10));
    roster[2].setMove(3, Move("Gunk Shot", 0, 120, POISON, 30));

    // 4. Dragonite
    roster[3] = Pokemon("Dragonite", 386, 80);
    roster[3].setMove(0, Move("Extreme Speed", 2, 80));
    roster[3].setMove(1, Move("Gunk Shot", 0, 120, POISON, 30));
    roster[3].setMove(2, Move("Flamethrower", 0, 90, BURN, 10));
    roster[3].setMove(3, Move("Dragon Tail", -6, 60));

    clearScreen();
    cout << "Select your Pokemon:\n";
    for(int i = 0; i < 4; i++) {
        cout << i + 1 << ". " << roster[i].getName() << " (HP: " << roster[i].getMaxHP() << ", Speed: " << roster[i].getSpeed() << ")\n";
    }

    int pChoice;
    cin >> pChoice;
    if(pChoice < 1 || pChoice > 4) pChoice = 1; // Default to Smeargle if invalid

    Pokemon player = roster[pChoice - 1];

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

// ===== EXECUTION WITH STATUS LOGIC =====
        bool enemyFlinched = false;
        bool playerFlinched = false;
        
        if (playerFirst) {
            // Player Attacks First
            string playerAction;
            if (playerMove.getMoveName() == "Fake Out" && player.getTurnCount() > 0) {
                playerAction = "> " + player.getName() + " used Fake Out, but it failed!";
                cout << playerAction << endl;
            } else {
                playerAction = "> " + player.getName() + " used " + playerMove.getMoveName() + "!";
                cout << playerAction << endl;
                enemy.takeDamage(playerMove.getDamage());
                
                if (playerMove.getStatus() == FLINCH && (rand() % 100 < playerMove.getStatusChance())) {
                    enemyFlinched = true;
                }
            }
            ActionStack(history, playerAction);

            // Enemy Attacks Second (if still alive and not flinched)
            if (enemy.getIsAlive() && !enemyFlinched) {
                string enemyAction;
                if (enemyMove.getMoveName() == "Fake Out" && enemy.getTurnCount() > 0) {
                    enemyAction = "> " + enemy.getName() + " used Fake Out, but it failed!";
                    cout << enemyAction << endl;
                } else {
                    enemyAction = "> " + enemy.getName() + " used " + enemyMove.getMoveName() + "!";
                    cout << enemyAction << endl;
                    player.takeDamage(enemyMove.getDamage());
                }
                ActionStack(history, enemyAction);
            } else if (enemyFlinched) {
                string flinchAction = "> " + enemy.getName() + " flinched and couldn't move!";
                cout << flinchAction << endl;
                ActionStack(history, flinchAction);
            }
        } else {
            // Enemy Attacks First
            string enemyAction;
            if (enemyMove.getMoveName() == "Fake Out" && enemy.getTurnCount() > 0) {
                enemyAction = "> " + enemy.getName() + " used Fake Out, but it failed!";
                cout << enemyAction << endl;
            } else {
                enemyAction = "> " + enemy.getName() + " used " + enemyMove.getMoveName() + "!";
                cout << enemyAction << endl;
                player.takeDamage(enemyMove.getDamage());
                
                if (enemyMove.getStatus() == FLINCH && (rand() % 100 < enemyMove.getStatusChance())) {
                    playerFlinched = true;
                }
            }
            ActionStack(history, enemyAction);

            // Player Attacks Second (if still alive and not flinched)
            if (player.getIsAlive() && !playerFlinched) {
                string playerAction;
                if (playerMove.getMoveName() == "Fake Out" && player.getTurnCount() > 0) {
                    playerAction = "> " + player.getName() + " used Fake Out, but it failed!";
                    cout << playerAction << endl;
                } else if (playerMove.getStatus() == FAIL_IF_HIT) {
                    playerAction = "> " + player.getName() + " lost its focus and couldn't move!";
                    cout << playerAction << endl;
                } else {
                    playerAction = "> " + player.getName() + " used " + playerMove.getMoveName() + "!";
                    cout << playerAction << endl;
                    enemy.takeDamage(playerMove.getDamage());
                }
                ActionStack(history, playerAction);
            } else if (playerFlinched) {
                string flinchAction = "> " + player.getName() + " flinched and couldn't move!";
                cout << flinchAction << endl;
                ActionStack(history, flinchAction);
            }
        }
        player.incrementTurn();
        enemy.incrementTurn();
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
