# PokeQueue: Pokémon Battle Turn Manager

A C++ console-based application that simulates a Pokémon-inspired turn-based battle system, demonstrating the practical use of Stack, Queue, and Priority Queue data structures.

---

## 📌 Problem Description

### What problem are we solving?

In a Pokémon battle, moves don't just happen randomly — there is a strict order to everything that happens each turn. The game must decide:

- **Who moves first?** Based on move priority level and Pokémon speed.
- **What happens when a priority move comes in?** Moves like Fake Out or Extreme Speed always go before normal moves, regardless of who acted first.
- **How are status effects like burn and poison handled?** They deal damage at the end of every turn, after all moves have been executed.
- **How do we track everything that happened in a battle?** Every action needs to be recorded so it can be reviewed after the battle ends.

PokeQueue simulates this exact turn management engine — modeling a real Pokémon battle using data structures that mirror the actual game's mechanics.

---

## 🗂️ Data Structures Used

### 1. Queue — Move Turn Order

**What it is:**
A Queue is a linear data structure that follows the **First-In, First-Out (FIFO)** principle. The first element added is the first one to be processed — similar to a real-life line or queue.

**Why we used it:**
Every turn, moves from both the player and the enemy are added to a `queue<MoveAction>`. They are then processed in the order they were inserted — which reflects how a Pokémon turn actually resolves. The Queue also naturally accommodates additional actions like status effect damage (burn, poison) that are appended at the end of each turn's action list, making it fill up meaningfully beyond just two moves per turn.

**In the code:**
```cpp
queue<MoveAction> moveQueue;
moveQueue.push(playerMA);   // player move added
moveQueue.push(enemyMA);    // enemy move added
// status damage queued at end of turn if applicable
```

---

### 2. Priority Queue — Move Priority Resolution

**What it is:**
A Priority Queue processes elements based on their **priority level**, not the order they were added. Higher priority elements are processed first.

**Why we used it:**
In Pokémon, certain moves have priority values (e.g., Fake Out = +3, Extreme Speed = +2, Sucker Punch = +1, Dragon Tail = -6). These moves **always execute before or after** normal moves regardless of which Pokémon is faster. The `PriorityMoveQueue()` function compares priority levels first, then falls back to Speed as a tiebreaker — mirroring real Pokémon battle mechanics exactly.

**In the code:**
```cpp
void PriorityMoveQueue(const Move &playerMove, const Move &enemyMove,
                       const Pokemon &player, const Pokemon &enemy, bool &playerFirst) {
    if (playerMove.getPriority() > enemyMove.getPriority())
        playerFirst = true;
    else if (playerMove.getPriority() < enemyMove.getPriority())
        playerFirst = false;
    else
        playerFirst = player.getSpeed() >= enemy.getSpeed();
}
```

---

### 3. Stack — Battle History

**What it is:**
A Stack is a linear data structure that follows the **Last-In, First-Out (LIFO)** principle. The most recently added element is the first one retrieved.

**Why we used it:**
Every action that occurs during the battle — moves used, status effects triggered, KOs — is pushed onto a `stack<string>`. At the end of the battle, the Stack is popped to display the **full battle history in reverse chronological order** (most recent action first, all the way back to turn 1). LIFO is the reason this works naturally — no sorting or reordering needed.

**In the code:**
```cpp
stack<string> history;

// every action gets pushed
history.push(player.getName() + " used " + playerMove.getMoveName());

// at end of battle, pop to display in reverse
while (!history.empty()) {
    cout << history.top() << endl;
    history.pop();
}
```

---

## ⚙️ Algorithm Explanation

### Move Submission Flow
- Player selects a move from their moveset (1–4)
- Enemy randomly selects a move from their moveset
- Both moves are wrapped in a `MoveAction` struct containing actor name, move data, priority, and speed

### Priority Resolution
- `PriorityMoveQueue()` compares the priority levels of both selected moves
- Higher priority move goes first
- If priority is equal, the Pokémon with higher Speed goes first
- Moves are then inserted into the `queue<MoveAction>` in the resolved order

### Turn Execution (Queue Processing)
- The queue is processed front-to-back (FIFO)
- Each action is dequeued and executed one at a time
- Special conditions are checked per action:
  - **Flinch** — target cannot move if flinched this turn
  - **Sleep** — sleeping Pokémon's move is skipped
  - **Fake Out** — only works on Turn 0 (first turn), fails after
  - **Focus Punch (FAIL_IF_HIT)** — fails if the user was hit before it executes
- If a KO occurs mid-queue, remaining actions are cleared and the loop breaks
- Status damage (burn, poison) is applied at the **end of the turn**, after all moves resolve

### Status Effect System
- Each move has a `StatusType` and a `statusChance` (percentage)
- On hit, a random roll determines if the status is applied
- Status conditions tracked: `BURN`, `POISON`, `SLEEP`, `PARALYZE`, `FLINCH`, `SHIELD_BREAK`, `FAIL_IF_HIT`
- Each status has a turn counter (`statusTurnsRemaining`) that decrements each turn
- Burn and Poison deal 1/8 max HP damage at end of turn
- Sleep prevents the affected Pokémon from moving while `statusTurnsRemaining > 0`

### Battle History (Stack)
- Every executed action string is pushed onto the `stack<string> history`
- After the battle ends, the Stack is popped until empty
- Result: full battle recap displayed in reverse order — latest action shown first

---

## 🔄 Iterative vs. Recursive Comparison

### Iterative Approach
**Used for:** Displaying the move selection menu, processing the action queue, rendering the HP bar, and displaying the battle roster.

```cpp
// HP bar display - iterative loop
for (int i = 0; i < 20; i++) {
    if (i < bars) cout << "#";
    else cout << "-";
}
```

- **Speed:** Faster — no function call overhead, constant memory usage O(1)
- **Readability:** More straightforward for sequential and repetitive tasks
- **Best for:** Traversal, display, and processing tasks with a clear start and end

### Recursive Approach
**Used for:** Searching for a specific move by name across the active roster.

```cpp
// Recursive move search
bool searchMove(Pokemon &poke, string target, int index) {
    if (index >= 4) return false;   // base case: no more moves
    if (poke.getMove(index).getMoveName() == target) return true; // found
    return searchMove(poke, target, index + 1); // recurse on next
}
```

- **Speed:** Slightly slower due to function call stack overhead O(n)
- **Readability:** More elegant for search and divide-and-conquer problems
- **Best for:** Searching, tree traversal, and problems that naturally break into smaller subproblems

### Which is faster?
**Iterative** is generally faster due to no call stack overhead.

### Which is easier to understand?
**Iterative** is easier to read for sequential tasks. Recursive is more intuitive for search logic once you understand base and recursive cases.

---

## 🧠 Design Decisions & Trade-offs

### Why Queue for move turn order?
A Queue guarantees fairness and correct ordering — moves are executed in the order they are resolved. Using a Stack here would wrongly execute the most recently added move first, which completely breaks turn logic. The Queue also scales naturally when status damage actions are appended at the end of each turn.

### Why Priority Queue logic instead of STL `priority_queue`?
We implemented priority resolution manually through `PriorityMoveQueue()` rather than using C++'s built-in `priority_queue` container. This is because Pokémon's priority system has a specific tiebreaker (Speed) when two moves share the same priority level — something the STL container cannot handle without complex custom comparators. Manual resolution is cleaner and more readable for this use case.

### Why Stack for battle history?
The Stack's LIFO behavior is the exact reason the battle history feature works — the most recent action is naturally on top, so popping the Stack produces a reverse chronological recap without any additional sorting. No other data structure achieves this as cleanly.

### Why an enum for status types instead of strings?
Using `enum StatusType { NONE, FLINCH, SLEEP, BURN, POISON, PARALYZE, SHIELD_BREAK, FAIL_IF_HIT }` instead of raw strings prevents typos, makes comparisons faster, and keeps the code readable. It also makes adding new status types straightforward.

### Trade-off: 1v1 format vs. larger teams
A full 6v6 format would have made the Queue feel more natural with more moves per turn, but it would have significantly increased code complexity for HP tracking, switching logic, and faint management. We chose a 1v1 format with a roster of 4 selectable Pokémon, and compensated for the shallow queue by appending status damage actions at the end of each turn — making the Queue fill meaningfully without adding complexity.

### Trade-off: Random enemy AI vs. decision-based AI
The enemy selects moves randomly from their moveset. A smarter AI would make the game more challenging but would shift the project's focus away from data structures toward game AI logic. The random AI keeps the scope appropriate for CC 103 while still demonstrating all required data structure behaviors.

---

## 👥 Team Members

| Name | Contribution |
|---|---|
| Denver Banayado | BattleSystem logic, turn loop, priority resolution, enemy generation |
| Joseph Arby Mercado | Move and Pokemon class implementation, status effect system, queue integration |
| James Andrey Quito | Battle history Stack, UI formatting, documentation, README |

---

## 🙏 Acknowledgement

The group would like to sincerely thank our instructor for the clear project guidelines and constructive feedback throughout the semester — particularly for pushing us to think critically about our design decisions rather than just making things work. The feedback on our initial Stack implementation (undo mechanic) led us to a much stronger and more genuine use case in the battle history system.

We would also like to thank Batangas State University — The National Engineering University and the College of Informatics and Computing Sciences for the opportunity to apply data structures concepts in a project we genuinely enjoyed building.

Special thanks to the Pokémon franchise for the inspiration. No copyright infringement intended — this is a purely academic project.

---

*PokeQueue — CC 103 Data Structures and Algorithms | 2nd Semester, AY 2025–2026 | Batangas State University*
