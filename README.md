# A* Puzzle Solver

This repository contains an implementation of a generic A* search algorithm for solving sliding puzzles. The solution supports custom configurations, dimensions, and heuristic approaches to explore the optimal path to the goal state.

---

## Features

- **Sliding Puzzle Solver**:
  - Works for puzzles of any dimension (e.g., 3x3, 4x4).
  - Supports both predefined depths and custom initial states.
- **Heuristics**:
  - **Uniform Cost Search**: No heuristic, cost-based search.
  - **Misplaced Tiles**: Counts the number of misplaced tiles.
  - **Manhattan Distance**: Calculates the sum of distances of tiles from their goal positions.
- **Interactive Menu**:
  - Choose predefined puzzles with specific depths or create custom cases.
  - Select desired heuristic approaches for solving.
- **Statistics**:
  - Displays details such as solution depth, number of nodes traversed, branching factor, and maximum queue size.

---

## Files

### `Puzzle.cpp`

Contains the `Puzzle` class that implements the A* search algorithm. It is a templated class capable of working with various types of states and heuristic functions.

### `main.cpp`

The main driver program that uses the `Puzzle` class to solve sliding puzzles. It includes:
- Menu for predefined or custom cases.
- Support for different heuristics.
- Displays puzzle states and statistics after solving.

---

## How to Use

### Compilation

Use a C++ compiler with support for C++11 or later.

```bash
g++ -o puzzle_solver main.cpp -std=c++11
