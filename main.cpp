#include <bits/stdc++.h>
#include "Puzzle.cpp" // Include the Puzzle class implementation file
using namespace std;

// Function to generate the goal state of the puzzle
vector<vector<int>> solutionState(int n, int m)
{
    int count = 1;
    vector<vector<int>> res;
    for (int i = 0; i < n; i++)
    {
        vector<int> row;
        for (int j = 0; j < m; j++)
        {
            if (count < n * m)
            {
                row.push_back(count);
                count++;
            }
            else
            {
                row.push_back(0); // Last element is 0 (empty space)
            }
        }
        res.push_back(row);
    }
    return res;
}

// Function to format the input into a 2D matrix
vector<vector<int>> input_format(vector<int> ip, int n, int m)
{
    vector<vector<int>> res;
    for (int i = 0; i < n; i++)
    {
        vector<int> row;
        for (int j = 0; j < m; j++)
        {
            row.push_back(ip[i * m + j]);
        }
        res.push_back(row);
    }
    return res;
}

// Function to create move operations for the puzzle
vector<function<void(vector<vector<int>>, vector<vector<int>> &, bool &)>> CreateMoves(vector<pair<int, int>> moves)
{
    vector<function<void(vector<vector<int>>, vector<vector<int>> &, bool &)>> operations;
    for (pair<int, int> move : moves)
    {
        operations.push_back([move](vector<vector<int>> cur_state, vector<vector<int>> &ret, bool &isValid)
        {
            int coordx, coordy;

            // Find the coordinates of the space (0)
            for (int i = 0; i < cur_state.size(); i++)
            {
                for (int j = 0; j < cur_state[0].size(); j++)
                {
                    if (cur_state[i][j] == 0)
                    {
                        coordx = i;
                        coordy = j;
                        break;
                    }
                }
            }

            int i = coordx + move.first, j = coordy + move.second;
            if (i < 0 || i >= cur_state.size() || j < 0 || j >= cur_state[0].size())
            {
                isValid = false;
                return;
            }
            // Swap the space (0) with the neighboring element
            isValid = true;
            int temp = cur_state[coordx][coordy];
            cur_state[coordx][coordy] = cur_state[i][j];
            cur_state[i][j] = temp;
            ret.assign(cur_state.begin(), cur_state.end());
        });
    }
    return operations;
}

// Heuristic function to evaluate the current state against the goal state
int evaluate(vector<vector<int>> &cur, vector<vector<int>> &sol)
{
    // For uniform cost search, return 0 as heuristic
    if (cur.size() != sol.size() || cur[0].size() != sol[0].size())
    {
        cout << "Error: Size mismatch between current state and goal state";
        return -1;
    }
    return 0;
}

// Heuristic function: count of misplaced tiles
int not_manhattan(vector<vector<int>> &cur, vector<vector<int>> &sol)
{
    if (cur.size() != sol.size() || cur[0].size() != sol[0].size())
    {
        cout << "Error: Size mismatch between current state and goal state";
        return false;
    }
    int count = 0;
    for (int i = 0; i < cur.size(); i++)
    {
        for (int j = 0; j < cur[0].size(); j++)
        {
            if (i == cur.size() - 1 && j == cur[0].size() - 1)
                continue;
            if (cur[i][j] != sol[i][j])
            {
                count++;
            }
        }
    }
    return count;
}

// Heuristic function: Manhattan distance
int manhattan(vector<vector<int>> &cur, vector<vector<int>> &sol)
{
    if (cur.size() != sol.size() || cur[0].size() != sol[0].size())
    {
        cout << "Error: Size mismatch between current state and goal state";
        return false;
    }
    int distance = 0;
    map<int, pair<int, int>> hash;

    // Create a mapping of numbers to their coordinates in the current state
    for (int i = 0; i < cur.size(); i++)
    {
        for (int j = 0; j < cur[0].size(); j++)
        {
            hash[cur[i][j]] = make_pair(i, j);
        }
    }

    // Calculate Manhattan distance for each number in the current state
    for (int i = 0; i < cur.size(); i++)
    {
        for (int j = 0; j < cur[0].size(); j++)
        {
            pair<int, int> cur_coordinates = hash[sol[i][j]];
            distance += abs(cur_coordinates.first - i) + abs(cur_coordinates.second - j);
        }
    }
    return distance;
}
// Function to display the puzzle state
void display(vector<vector<int>> &d)
{
    cout << endl;
    for (auto i : d)
    {
        for (auto j : i)
        {
            cout << j << " ";
        }
        cout << endl;
    }
}
// Function to check if the current state is the goal state
bool check_sol(vector<vector<int>> &cur, vector<vector<int>> &sol)
{
  

    if (cur.size() != sol.size() || cur[0].size() != sol[0].size())
    {
        cout << "Error: Size mismatch between current state and goal state";
        return false;
    }

    // Check if all elements match the goal state
    for (int i = 0; i < cur.size(); i++)
    {
        for (int j = 0; j < cur[0].size(); j++)
        {
            if (cur[i][j] != sol[i][j])
            {
                return false;
            }
        }
    }
    return true;
}



// Main function
int main()
{
    while (1)
    {
        int choice;
        cout << "\n\tMenu\n1.Default Case\n2.Custom Case\n3.Exit\nEnter Choice:";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            int d;
            cout << "Enter Depth (0, 2, 4, 8, 12, 20, 24): ";
            cin >> d;
            vector<vector<int>> solS = solutionState(3, 3);
            vector<pair<int, int>> moves = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
            vector<vector<int>> initState;
            switch (d)
            {

            case 0:
                initState = input_format({1, 2, 3, 4, 5, 6, 7, 8, 0}, 3, 3);
                break;
            case 2:
                initState = input_format({1, 2, 3, 4, 5, 6, 0, 7, 8}, 3, 3);
                break;
            case 4:
                initState = input_format({1, 2, 3, 5, 0, 6, 4, 7, 8}, 3, 3);
                break;
            case 8:
                initState = input_format({1, 3, 6, 5, 0, 2, 4, 7, 8}, 3, 3);
                break;
            case 12:
                initState = input_format({1, 3, 6, 5, 0, 7, 4, 8, 2}, 3, 3);
                break;
            case 16:
                initState = input_format({1, 6, 7, 5, 0, 3, 4, 8, 2}, 3, 3);
                break;
            case 20:
                initState = input_format({7, 1, 2, 4, 8, 5, 6, 3, 0}, 3, 3);
                break;
            case 24:
                initState = input_format({0, 7, 2, 4, 6, 1, 3, 5, 8}, 3, 3);
                break;
            default:
                cout << "Wrong choice";
                continue;
            }
            cout << "\nInitial State:";
            display(initState);
            cout << "\nGoal State:";
            display(solS);
            Puzzle<vector<vector<int>>> Obj(&initState, &solS, CreateMoves(moves), evaluate, check_sol);
            Puzzle<vector<vector<int>>> Obj2(&initState, &solS, CreateMoves(moves), not_manhattan, check_sol);
            Puzzle<vector<vector<int>>> Obj3(&initState, &solS, CreateMoves(moves), manhattan, check_sol);
            cout << "\nUniform Cost Search\n";
            Obj.A_star();
            cout << "\nMisplaced\n";
            Obj2.A_star();
            cout << "\nManhattan\n";
            Obj3.A_star();
            break;
        }
        case 2:
        {
            int n, m;
            cout << "Enter dimensions (space separated): ";
            cin >> n >> m;
            vector<int> nums(n * m);
            cout << "Enter the cells from top left to bottom right (space separated): ";
            for (int i = 0; i < n * m; i++)
            {
                cin >> nums[i];
            }
            vector<vector<int>> solS = solutionState(n, m);
            vector<pair<int, int>> moves = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
            vector<vector<int>> initState = input_format(nums, n, m);
            cout << "\nInitial State:";
            display(initState);
            cout << "\nGoal State:";
            display(solS);

            int ch;
            cout << "Enter the Approach:\n1. Uniform Cost Search,\n2. Misplaced,\n3. Manhattan,\n4. All,\n5. Misplaced & Manhattan\n: ";
            cin >> ch;
            switch (ch)
            {
            case 1:
            {
                Puzzle<vector<vector<int>>> Obj(&initState, &solS, CreateMoves(moves), evaluate, check_sol);
                Obj.A_star();
                break;
            }
            case 2:
            {
                Puzzle<vector<vector<int>>> Obj(&initState, &solS, CreateMoves(moves), not_manhattan, check_sol);
                Obj.A_star();
                break;
            }
            case 3:
            {
                Puzzle<vector<vector<int>>> Obj(&initState, &solS, CreateMoves(moves), manhattan, check_sol);
                Obj.A_star();
                break;
            }
            case 4:
            {
                Puzzle<vector<vector<int>>> Obj(&initState, &solS, CreateMoves(moves), evaluate, check_sol);
                cout << "\nUniform Cost Search\n";
                Obj.A_star();
            }
            case 5:
            {
                Puzzle<vector<vector<int>>> Obj2(&initState, &solS, CreateMoves(moves), not_manhattan, check_sol);
                Puzzle<vector<vector<int>>> Obj3(&initState, &solS, CreateMoves(moves), manhattan, check_sol);
                cout << "\nMisplaced\n";
                Obj2.A_star();
                cout << "\nManhattan\n";
                Obj3.A_star();
                break;
            }
            default:
                cout << "Wrong choice";
            }
            break;
        }
        case 3:
            return 0; // Exit the program
        default:
            cout << "Wrong choice";
            break;
        }
    }
    return 0;
}
