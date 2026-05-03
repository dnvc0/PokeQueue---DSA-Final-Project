// main file for PokeQueue - DSA Final Project
#include <iostream>
#include <cstdlib>  
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
    cout << "=== TEAM BATTLE START ===\n";

    // player set up
    Team playerTeam;

    // TODO: assign kayo pokemon dito
    // Example:
    // Pokemon p1("Name", HP, Speed);
    // p1.setMove(0, Move("Move1", priority, damage));
    // p1.setMove(1, Move("Move2", priority, damage));
    // playerTeam.setPokemon(0, p1);

    // TEMP PLACEHOLDER
    for (int i = 0; i < 6; i++) {
        Pokemon temp;
        playerTeam.setPokemon(i, temp);
    }

    // empty setup
    Pokemon enemy;

    // TODO: define nyo yung enemy pokemon dito
    // Example:
    // enemy = Pokemon("EnemyName", HP, Speed);
    // enemy.setMove(0, Move("Move1", priority, damage));

    // stack history
    stack<string> history;

    // loop
    while (playerTeam.hasAlivePokemon() && enemy.getIsAlive()) {
        Pokemon& player = playerTeam.getCurrentPokemon();

        clearScreen();
        cout << "=== BATTLE ===\n";

        cout << "\nYour Active Pokemon: ";
        player.displayPokemon();

        cout << "Enemy Pokemon: ";
        enemy.displayPokemon();

        cout << "\n1. Attack\n2. Switch\nChoose: ";
        int option;
        cin >> option;

        // swithcing pokemon
        if (option == 2) {
            playerTeam.switchPokemon();
            continue;
        }

        // move selection
        cout << "\nChoose Move:\n";

        // TODO: Replace with actual moves later
        cout << "1. [Move Slot 1]\n";
        cout << "2. [Move Slot 2]\n";

        int moveChoice;
        cin >> moveChoice;

        Move playerMove; // EMPTY muna
        Move enemyMove;  // EMPTY muna

        // TODO: Replace with actual move retrieval
        // playerMove = player.getMove(moveChoice - 1);
        // enemyMove = enemy.getMove(rand() % 2);

        // priority queue for turn order
        priority_queue<Move, vector<Move>, CompareMove> turnQueue;
        turnQueue.push(playerMove);
        turnQueue.push(enemyMove);

        cout << "\n--- Turn Start ---\n";

        while (!turnQueue.empty()) {
            Move current = turnQueue.top();
            turnQueue.pop();

            // TODO: Replace with real move comparison logic
            cout << "[Action executed here]\n";

            // Placeholder history log
            history.push("Action executed");

            break; // prevent infinite loop for now
        }

        cout << "--- Turn End ---\n";
        system("pause");

        // TEMP BREAK to avoid infinite loop since no real damage yet
        break;
    }

    // ===== RESULT PLACEHOLDER =====
    cout << "\n=== BATTLE RESULT ===\n";
    cout << "Result will depend on actual battle logic.\n";

    // ===== HISTORY DISPLAY =====
    cout << "\n=== ACTION HISTORY ===\n";
    while (!history.empty()) {
        cout << history.top() << endl;
        history.pop();
    }

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

    return 0;
}
