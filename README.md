# echoes-of-eldoria
A DSA-based fantasy adventure game demonstrating seven data structures in C++ implementing the concepts of Arrays, LinkedList, Stacks, Queues, Binary Trees and Binary Search Trees.

# Echoes of Eldoria ⚔️

**A C++ Data Structures Adventure Game | CSC211**

## 📖 About the Project

Echoes of Eldoria is a text-based fantasy adventure game developed as part of the CSC211 – Data Structures course project.

The player enters a fantasy world where the Dawn Crystal has been stolen from the village of Eldoria. Their mission is to explore different locations, fight enemies, collect items, complete quests, and ultimately recover the crystal.

Throughout the adventure, players make decisions that influence their journey and lead to three different endings.

The main purpose of this project is to demonstrate the practical implementation of fundamental data structures through an interactive game.

## 🎯 Project Objectives

- Implement fundamental data structures using C++.
- Understand how data structures work in real-world applications.
- Apply recursion and tree traversal techniques.
- Develop a structured and maintainable project using Object-Oriented Programming.
- Practice collaborative software development using Git and GitHub.

## 🧩 Data Structures Used

The project demonstrates seven major data structures:

| Data Structure | Application in the Game |
|---|---|
| Array | Player inventory and game statistics |
| Singly Linked List | Active quest management |
| Stack | Player movement and path history |
| Queue | Battle turn management |
| Circular Queue | In-game message history |
| N-ary Tree | Story navigation and scene management |
| Binary Search Tree | Item and monster codex |

### Tree Concepts

The project also demonstrates:

- Root, parent, child, and leaf nodes.
- Recursive tree height calculation.
- Recursive leaf counting.
- Pre-order style recursion.
- Post-order traversal for memory cleanup.
- In-order traversal for sorted codex entries.
- Tree structure versus graph structure.

## ⚙️ Technologies

- **Programming Language:** C++
- **Version Control:** Git
- **Repository Hosting:** GitHub
- **Development Environment:** VS Code / Code::Blocks

## 📁 Project Structure

```text
echoes-of-eldoria/
│
├── README.md
│
├── docs/
│   ├── project-proposal.md
│   ├── game-story.md
│   ├── architecture.md
│   ├── data-structures.md
│   ├── class-diagram.md
│   └── CONTRIBUTING.md
│
├── src/
│   ├── main.cpp
│   ├── game.h
│   │
│   ├── structures/
│   │   ├── inventory.h
│   │   ├── quest-list.h
│   │   ├── path-stack.h
│   │   ├── battle-queue.h
│   │   ├── message-queue.h
│   │   ├── story-tree.h
│   │   └── codex-bst.h
│   │
│   └── gui/
│
├── tests/
│   └── README.md
│
└── assets/
    ├── images/
    └── icons/
```

## 🎮 Game Features

- Interactive fantasy storyline.
- Multiple locations and branching story paths.
- Player inventory and item collection.
- Quest tracking and completion.
- Enemy battles and turn-based combat.
- Navigation through previous scenes.
- Three different story endings.
- Item and monster codex.

## 📌 Important Implementation Rules

1. Each story scene can have a maximum of three children.
2. Rewards, damage, and quest effects should apply only once per scene.
3. Returning to a previous scene must not duplicate rewards.
4. Gold should only be charged when the player first visits the purchase destination.
5. Game logic must remain independent of the GUI.
6. No STL containers will be used for implementing the required data structures.
7. Dynamically allocated tree nodes must be properly deleted to prevent memory leaks.

## 👥 Team Collaboration

This project is developed collaboratively using GitHub.

All team members are expected to:

- Work on their assigned features.
- Create separate feature branches.
- Write readable and properly organized code.
- Test their implementations before submitting changes.
- Create Pull Requests for code review and integration.
- Keep the `main` branch stable.

### Git Workflow

```text
main
  |
  └── dev
       |
       ├── feature/inventory
       ├── feature/quest-system
       ├── feature/story-tree
       └── feature/battle-system
```

Refer to `docs/CONTRIBUTING.md` for detailed collaboration guidelines.

## 🚀 Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/YOUR-USERNAME/echoes-of-eldoria.git
```

### 2. Navigate to the Project

```bash
cd echoes-of-eldoria
```

### 3. Compile the Project

Once the source files and build configuration are ready, compilation instructions will be added here.

## 📚 Documentation

Detailed project documentation will be maintained in the `docs/` directory.

It will include:

- Project proposal and overview.
- Complete game storyline.
- System architecture.
- Data structure implementations.
- Class responsibilities and diagrams.
- Team contribution guidelines.

## 📊 Project Information

| Detail | Description |
|---|---|
| Project Name | Echoes of Eldoria |
| Course | CSC211 – Data Structures |
| Language | C++ |
| Project Type | Academic Group Project |
| Repository | GitHub |
| Data Structures | 7 |

---

**Echoes of Eldoria — Every Choice Shapes Your Journey.**
