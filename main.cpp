// main file for PokeQueue - DSA Final Project
#include <iostream>
#include <cstdlib>  
#include <queue>
#include <stack>
#include <ctime>
#include <string> 
#include <conio.h>  
using namespace std;

bool readInteger(int &value) {
    string line;
    if (!getline(cin >> ws, line)) return false;
    try {
        size_t pos;
        int result = stoi(line, &pos);
        if (pos != line.size()) return false;
        value = result;
        return true;
    } catch (...) {
        return false;
    }
}

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

struct MoveAction {
    string actorName;
    bool isPlayer;
    Move move;
    int priority;
    int speed;
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
        StatusType currentStatus;
        int statusTurnsRemaining;
    public:
        Pokemon() {
            name = "";
            hp = 0;
            maxHP = 0;
            turnCount = 0;
            speed = 0;
            isAlive = false;
            isFainted = true;
            currentStatus = NONE;
            statusTurnsRemaining = 0;
        }

        Pokemon(string n, int h, int s) {
            name = n;
            hp = h;
            maxHP = h;
            speed = s;
            turnCount = 0;
            isAlive = true;
            isFainted = false;
            currentStatus = NONE;
            statusTurnsRemaining = 0;
        }

        string getName() const {return name;}
        int getHP() const {return hp;}
        int getMaxHP() const {return maxHP;}
        int getSpeed() const {return speed;}
        bool getIsAlive() const {return isAlive;}
        Move getMove(int index) const {return moveSet[index];}
        int getTurnCount() const { return turnCount; }
        void incrementTurn() { turnCount++; }
        StatusType getCurrentStatus() const { return currentStatus; }
        int getStatusTurnsRemaining() const { return statusTurnsRemaining; }

        void applyStatus(StatusType status, int turns) {
            if (currentStatus == NONE) {
                currentStatus = status;
                statusTurnsRemaining = turns;
            }
        }

        void removeStatus() {
            currentStatus = NONE;
            statusTurnsRemaining = 0;
        }

        void decrementStatusTurns() {
            if (statusTurnsRemaining > 0) {
                statusTurnsRemaining--;
                if (statusTurnsRemaining <= 0) {
                    currentStatus = NONE;
                }
            }
        }

        string getStatusString() const {
            switch(currentStatus) {
                case SLEEP: return "[SLEEP]";
                case BURN: return "[BURN]";
                case POISON: return "[POISON]";
                case PARALYZE: return "[PARALYZE]";
                default: return "";
            }
        }

        void takeDamage(int dmg) {
            if(!isAlive) return;
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
        if (!readInteger(choice) || choice < 1 || choice > 4) {
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

string getEnemyDisplayName(const Pokemon &player, const Pokemon &enemy) {
    if (player.getName() == enemy.getName()) {
        return "Enemy " + enemy.getName();
    }
    return enemy.getName();
}

Pokemon roster[4];

void initRoster() {
    roster[0] = Pokemon("Smeargle", 314, 75);
    roster[0].setMove(0, Move("Fake Out", 3, 40, FLINCH, 100));
    roster[0].setMove(1, Move("Wicked Torque", 0, 80, SLEEP, 10));
    roster[0].setMove(2, Move("Gunk Shot", 0, 120, POISON, 30));
    roster[0].setMove(3, Move("Dragon Tail", -6, 60));

    roster[1] = Pokemon("Lucario", 344, 90);
    roster[1].setMove(0, Move("Extreme Speed", 2, 80));
    roster[1].setMove(1, Move("Feint", 2, 30, SHIELD_BREAK, 100));
    roster[1].setMove(2, Move("Sucker Punch", 1, 70));
    roster[1].setMove(3, Move("Thunderbolt", 0, 90, PARALYZE, 10));

    roster[2] = Pokemon("Mew", 404, 100);
    roster[2].setMove(0, Move("Fake Out", 3, 40, FLINCH, 100));
    roster[2].setMove(1, Move("Focus Punch", -4, 150, FAIL_IF_HIT, 100));
    roster[2].setMove(2, Move("Flamethrower", 0, 90, BURN, 10));
    roster[2].setMove(3, Move("Gunk Shot", 0, 120, POISON, 30));

    roster[3] = Pokemon("Dragonite", 386, 80);
    roster[3].setMove(0, Move("Extreme Speed", 2, 80));
    roster[3].setMove(1, Move("Gunk Shot", 0, 120, POISON, 30));
    roster[3].setMove(2, Move("Flamethrower", 0, 90, BURN, 10));
    roster[3].setMove(3, Move("Dragon Tail", -6, 60));
}

void createRandomEnemy(Pokemon &enemy) {
    int randEnemy = rand() % 4;

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
    else if (randEnemy == 2) { // Dragonite: The Tank
        enemy = Pokemon("Dragonite", 386, 80);
        enemy.setMove(0, Move("Extreme Speed", 2, 80));
        enemy.setMove(1, Move("Gunk Shot", 0, 120, POISON, 30));
        enemy.setMove(2, Move("Flamethrower", 0, 90, BURN, 10));
        enemy.setMove(3, Move("Dragon Tail", -6, 60));
    }
    else { // Lucario: The Balanced Fighter
        enemy = Pokemon("Lucario", 344, 90);
        enemy.setMove(0, Move("Extreme Speed", 2, 80));
        enemy.setMove(1, Move("Feint", 2, 30, SHIELD_BREAK, 100));
        enemy.setMove(2, Move("Sucker Punch", 1, 70));
        enemy.setMove(3, Move("Thunderbolt", 0, 90, PARALYZE, 10));
    }
}

void displayHPBar(int hp, int maxHP, int speed, const Pokemon &poke) {
    int bars = (hp * 20) / maxHP;
    cout << "HP: [";
    for (int i = 0; i < 20; i++) {
        if (i < bars) cout << "#";
        else cout << "-";
    }
    cout << "] " << hp << "/" << maxHP << " Speed: " << speed;
    if (poke.getCurrentStatus() != NONE) {
        cout << " " << poke.getStatusString();
    }
    cout << endl;
}


void BattleSystem() {
    initRoster();
    clearScreen();
    cout << "Select your Pokemon:\n";
    for(int i = 0; i < 4; i++) {
        cout << i + 1 << ". " << roster[i].getName() << " (HP: " << roster[i].getMaxHP() << ", Speed: " << roster[i].getSpeed() << ")\n";
    }

    int pChoice;
    if (!readInteger(pChoice) || pChoice < 1 || pChoice > 4) {
        cout << "Invalid choice. Defaulting to Smeargle.\n";
        system("pause");
        pChoice = 1;
    }

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
        displayHPBar(player.getHP(), player.getMaxHP(), player.getSpeed(), player);

        cout << "\nENEMY POKEMON: \n";
        cout << getEnemyDisplayName(player, enemy) << endl;
        displayHPBar(enemy.getHP(), enemy.getMaxHP(), enemy.getSpeed(), enemy);

        // ===== PLAYER MOVE =====
        Move playerMove;
        Move enemyMove;
        MoveQueue(player, enemy, playerMove, enemyMove);

        cout << endl << string(15, '-') << " Turn Start " << string(15, '-') << endl;

        // ===== PRIORITY + SPEED LOGIC =====
        bool playerFirst;
        PriorityMoveQueue(playerMove, enemyMove, player, enemy, playerFirst);

        // ===== BUILD MOVE QUEUE =====
        queue<MoveAction> moveQueue;
        
        // Check status conditions that prevent moves
        bool playerAsleep = player.getCurrentStatus() == SLEEP && player.getStatusTurnsRemaining() > 0;
        bool enemyAsleep = enemy.getCurrentStatus() == SLEEP && enemy.getStatusTurnsRemaining() > 0;
        
        // Add moves to queue based on priority
        if (playerFirst) {
            if (!playerAsleep && (playerMove.getMoveName() != "Fake Out" || player.getTurnCount() == 0)) {
                MoveAction playerMA;
                playerMA.actorName = player.getName();
                playerMA.isPlayer = true;
                playerMA.move = playerMove;
                playerMA.priority = playerMove.getPriority();
                playerMA.speed = player.getSpeed();
                moveQueue.push(playerMA);
            }
            if (!enemyAsleep) {
                MoveAction enemyMA;
                enemyMA.actorName = getEnemyDisplayName(player, enemy);
                enemyMA.isPlayer = false;
                enemyMA.move = enemyMove;
                enemyMA.priority = enemyMove.getPriority();
                enemyMA.speed = enemy.getSpeed();
                moveQueue.push(enemyMA);
            }
        } else {
            if (!enemyAsleep) {
                MoveAction enemyMA;
                enemyMA.actorName = getEnemyDisplayName(player, enemy);
                enemyMA.isPlayer = false;
                enemyMA.move = enemyMove;
                enemyMA.priority = enemyMove.getPriority();
                enemyMA.speed = enemy.getSpeed();
                moveQueue.push(enemyMA);
            }
            if (!playerAsleep && (playerMove.getMoveName() != "Fake Out" || player.getTurnCount() == 0)) {
                MoveAction playerMA;
                playerMA.actorName = player.getName();
                playerMA.isPlayer = true;
                playerMA.move = playerMove;
                playerMA.priority = playerMove.getPriority();
                playerMA.speed = player.getSpeed();
                moveQueue.push(playerMA);
            }
        }

        // ===== EXECUTE MOVES FROM QUEUE =====
        bool enemyCanMove = true;
        bool playerCanMove = true;
        
        while (!moveQueue.empty()) {
            if (!player.getIsAlive() || !enemy.getIsAlive()) {
                while (!moveQueue.empty()) moveQueue.pop();
                break;
            }

            MoveAction action = moveQueue.front();
            moveQueue.pop();
            
            // Check if the actor can still move
            if (action.isPlayer && !playerCanMove) {
                string msg = "> " + action.actorName + " is unable to move!";
                cout << msg << endl;
                ActionStack(history, msg);
                continue;
            }
            if (!action.isPlayer && !enemyCanMove) {
                string msg = "> " + action.actorName + " is unable to move!";
                cout << msg << endl;
                ActionStack(history, msg);
                continue;
            }
            
            // Execute the move
            string moveMsg;
            if (action.move.getMoveName() == "Fake Out" && (action.isPlayer ? player.getTurnCount() > 0 : enemy.getTurnCount() > 0)) {
                moveMsg = "> " + action.actorName + " used Fake Out, but it failed!";
                cout << moveMsg << endl;
                ActionStack(history, moveMsg);
            } else if (!action.isPlayer && action.move.getStatus() == FAIL_IF_HIT && player.getHP() < player.getMaxHP()) {
                moveMsg = "> " + action.actorName + " lost its focus and couldn't move!";
                cout << moveMsg << endl;
                ActionStack(history, moveMsg);
            } else {
                moveMsg = "> " + action.actorName + " used " + action.move.getMoveName() + "!";
                cout << moveMsg << endl;
                ActionStack(history, moveMsg);
                
                // Apply damage
                if (action.isPlayer) {
                    enemy.takeDamage(action.move.getDamage());
                } else {
                    player.takeDamage(action.move.getDamage());
                }

                // If a KO happened, clear the queue and stop executing further moves
                if (!player.getIsAlive() || !enemy.getIsAlive()) {
                    while (!moveQueue.empty()) {
                        moveQueue.pop();
                    }
                    break;
                }
                
                // Apply status effects immediately
                if (action.move.getStatus() == FLINCH && (rand() % 100 < action.move.getStatusChance())) {
                    if (action.isPlayer) {
                        enemyCanMove = false;
                        string msg = "> " + getEnemyDisplayName(player, enemy) + " flinched and can't move!";
                        cout << msg << endl;
                        ActionStack(history, msg);
                    } else {
                        playerCanMove = false;
                        string msg = "> " + player.getName() + " flinched and can't move!";
                        cout << msg << endl;
                        ActionStack(history, msg);
                    }
                } else if (action.move.getStatus() == SLEEP && (rand() % 100 < action.move.getStatusChance())) {
                    if (action.isPlayer) {
                        enemy.applyStatus(SLEEP, 2);
                        enemyCanMove = false;
                        cout << "> " << getEnemyDisplayName(player, enemy) << " fell asleep!" << endl;
                    } else {
                        player.applyStatus(SLEEP, 2);
                        playerCanMove = false;
                        cout << "> " << player.getName() << " fell asleep!" << endl;
                    }
                } else if (action.move.getStatus() == BURN && (rand() % 100 < action.move.getStatusChance())) {
                    if (action.isPlayer) {
                        enemy.applyStatus(BURN, 10);
                        cout << "> " << getEnemyDisplayName(player, enemy) << " was burned!" << endl;
                    } else {
                        player.applyStatus(BURN, 10);
                        cout << "> " << player.getName() << " was burned!" << endl;
                    }
                } else if (action.move.getStatus() == POISON && (rand() % 100 < action.move.getStatusChance())) {
                    if (action.isPlayer) {
                        enemy.applyStatus(POISON, 10);
                        cout << "> " << getEnemyDisplayName(player, enemy) << " was poisoned!" << endl;
                    } else {
                        player.applyStatus(POISON, 10);
                        cout << "> " << player.getName() << " was poisoned!" << endl;
                    }
                } else if (action.move.getStatus() == PARALYZE && (rand() % 100 < action.move.getStatusChance())) {
                    if (action.isPlayer) {
                        enemy.applyStatus(PARALYZE, 10);
                        enemyCanMove = false;
                        cout << "> " << getEnemyDisplayName(player, enemy) << " was paralyzed and can't move!" << endl;
                    } else {
                        player.applyStatus(PARALYZE, 10);
                        playerCanMove = false;
                        cout << "> " << player.getName() << " was paralyzed and can't move!" << endl;
                    }
                }
            }
        }
        
        // Handle sleep/asleep conditions
        if (playerAsleep) {
            string msg = "> " + player.getName() + " is asleep and can't move!";
            cout << msg << endl;
            ActionStack(history, msg);
        }
        if (enemyAsleep) {
            string msg = "> " + getEnemyDisplayName(player, enemy) + " is asleep and can't move!";
            cout << msg << endl;
            ActionStack(history, msg);
        }

        // Apply end-of-turn damage from status effects
        if (player.getCurrentStatus() == BURN && player.getIsAlive()) {
            int burnDmg = player.getMaxHP() / 8;
            player.takeDamage(burnDmg);
            cout << "> " << player.getName() << " took " << burnDmg << " damage from burn!" << endl;
        } else if (player.getCurrentStatus() == POISON && player.getIsAlive()) {
            int poisonDmg = player.getMaxHP() / 8;
            player.takeDamage(poisonDmg);
            cout << "> " << player.getName() << " took " << poisonDmg << " damage from poison!" << endl;
        }

        if (enemy.getCurrentStatus() == BURN && enemy.getIsAlive()) {
            int burnDmg = enemy.getMaxHP() / 8;
            enemy.takeDamage(burnDmg);
            cout << "> " << getEnemyDisplayName(player, enemy) << " took " << burnDmg << " damage from burn!" << endl;
        } else if (enemy.getCurrentStatus() == POISON && enemy.getIsAlive()) {
            int poisonDmg = enemy.getMaxHP() / 8;
            enemy.takeDamage(poisonDmg);
            cout << "> " << getEnemyDisplayName(player, enemy) << " took " << poisonDmg << " damage from poison!" << endl;
        }

        cout << string(15, '-') << "  Turn End  " << string(15, '-') << "\n\n";

        // Decrement status turn counters
        player.decrementStatusTurns();
        enemy.decrementStatusTurns();

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

bool searchMove(const Pokemon &poke, string target, int index = 0) {
    if (index >= 4) return false;
    if (poke.getMove(index).getMoveName() == target) return true;
    return searchMove(poke, target, index + 1);
}

void searchMoveMenu() {
    clearScreen();
    cout << "Enter move name to search: ";
    cin.ignore();
    string target;
    getline(cin, target);

    cout << "\n--- Search Results for \"" << target << "\" ---\n";
    bool found = false;
    for (int i = 0; i < 4; i++) {
        if (searchMove(roster[i], target)) {
            cout << "> " << roster[i].getName() << " knows " << target << "!\n";
            found = true;
        }
    }
    if (!found) cout << "> Move \"" << target << "\" not found.\n";

    cout << endl;
    system("pause");
}

int main() {
    srand(time(0));

    initRoster();

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
        cout << "3. Move Dex" << endl;
        cout << "4. Exit game" << endl;
        int option;
        if (!readInteger(option)) {
            cout << "Invalid option. Please enter a number between 1 and 4." << endl;
            system("pause");
            continue;
        }
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
                searchMoveMenu();
                break;
            case 4:
                cout << "Thanks for playing!" << endl;
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl;
                system("pause"); 
        }
    }

    return 0;
}
