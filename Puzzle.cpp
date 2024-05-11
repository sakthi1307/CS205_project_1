#include <bits/stdc++.h>
using namespace std;

template <typename T>
class State{
public:
    T currentState; // Current state of the puzzle
    double g; // Cost from the initial state to this state
    double h; // Heuristic cost from this state to the goal state

    // Constructors
    State();
    State(T i);
};

// Default constructor definition
template <typename T>
State<T>::State(){
    g = 0;
    h = 0;
}

// Parameterized constructor definition
template <typename T>
State<T>::State(T i){
    currentState = i;
    g = 0;
    h = 0;
}

// Puzzle class definition
template <typename T>
class Puzzle
{
    T *init_state; // Initial state of the puzzle
    T *sol_state;  // Goal state of the puzzle
    set<T> unique; // Set to store unique states encountered during the search
    vector<function<void(T, T &, bool &)>> operations; // Vector of operations to perform on the puzzle state
    function<int(T &, T &)> evaluate; // Heuristic evaluation function
    function<bool(T &, T &)> isSolution; // Function to check if a state is the goal state

public:
    // Constructor
    Puzzle(T *curr, T *sol, vector<function<void(T, T &, bool &)>> _operations, function<int(T &, T &)> f, function<bool(T &, T &)> isSolution);
    
    // A* Search Algorithm
    void A_star();
};

// Constructor definition
template <typename T>
Puzzle<T>::Puzzle(T *curr, T *sol, vector<function<void(T, T &, bool &)>> _operations, function<int(T &, T &)> f, function<bool(T &, T &)> _isSolution)
{
    init_state = curr;
    sol_state = sol;
    evaluate = f;
    isSolution = _isSolution;
    operations = _operations;
    unique.insert(*init_state);
}

// A* Search Algorithm definition
template <typename T>
void Puzzle<T>::A_star()
{
    auto comp = [&](State<T> a, State<T> b)
    {
        return (a.g+a.h) > (b.g+b.h); // Priority queue comparator
    };

    // Priority queue to store states based on their f value (g + h)
    priority_queue<State<T>, vector<State<T>>, decltype(comp)> pq(comp);

    // Initialize with the initial state
    State<T> initial_state(*init_state);
    pq.push(initial_state);

    // Check if the initial state is the goal state
    if (isSolution(initial_state.currentState, *sol_state))
    {
        cout << "\nSolution state found:\n";
        cout<<"solution depth = "<<initial_state.g<<endl;
        cout<<"no of nodes in frontier = "<<pq.size()<<endl;
        return;
    }

    // Variables to store statistics
    long long no_of_nodes = 0;
    long long max_queue_size = 1;
    double branching_factor = 0;
    int max_depth_traversed = 0;

    // A* Search algorithm
    while (pq.size() > 0)
    {
        no_of_nodes++;
        State<T> top_element = pq.top();
        pq.pop();
        int no_of_branches = 0;
        
        // Perform operations on the current state
        for (int i = 0; i < operations.size(); i++)
        {
            State<T> newState;
            bool isValid = false;
            operations[i](top_element.currentState, newState.currentState, isValid);
            if (isValid && unique.find(newState.currentState)==unique.end() )
            {
                if (isSolution(newState.currentState, *sol_state))
                {
                    cout << "\nSolution state found:\n";
                    cout << "no of nodes Traversed = " << no_of_nodes << endl;
                    cout<<"max queue size = "<<max_queue_size<<endl;
                    cout<<"branching Factor = "<<branching_factor<<endl;
                    cout<<"solution depth = "<<top_element.g+1<<endl;
                    cout<<"max depth traversed = "<<max(max_depth_traversed,(int)(top_element.g+1))<<endl;
                    cout<<"no of nodes in frontier = "<<pq.size()<<endl;
                    return;
                }
                newState.g = top_element.g+1;
                max_depth_traversed = max(max_depth_traversed,(int)newState.g);
                newState.h = evaluate(newState.currentState,*sol_state);
                pq.push(newState);
                unique.insert(newState.currentState);
            }
            if(isValid){
                no_of_branches++;
            }
        }
        branching_factor = (branching_factor*(no_of_nodes-1)+no_of_branches)/no_of_nodes;
        max_queue_size = max(max_queue_size,(long long )pq.size());
    }
    cout<<"\n Solution not found";
}
