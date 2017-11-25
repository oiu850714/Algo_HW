#include <vector>
#include <iostream>
#include <algorithm>

using std::cin; using std::cout;
using std::vector;
using std::abs;



void push_bikes(vector<int64_t> &bikes, int n)
{
    for(int i = 0; i < n; i++)
    {
        int bike;
        cin >> bike;
        bikes.push_back(bike);
    }
}

int64_t DP(int parent, int node, vector<int64_t> &DP_table, vector< vector<int>> &tree_edges,
        vector<int64_t> &before_move, vector<int64_t> &after_move)
{
    if(DP_table[node] != INT64_MAX)
        return DP_table[node];

    if(tree_edges[node].size() == 1) // this node is leaf node, that has one edge pointing to its parent
        return (DP_table[node] = after_move[node] - before_move[node]);
    
    int64_t capacity = 0;

    for(auto dest : tree_edges[node])
    {
        if(dest != parent)//do not count parent's capacity
            capacity +=
                DP(node, dest, DP_table, tree_edges, before_move, after_move);
    }
    capacity += after_move[node] - before_move[node];
    //the node itself's transfer should also count
    return (DP_table[node] = capacity);
}

int main()
{
    std::ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;

    vector<int64_t> capacity_for_every_node(n, INT64_MAX);
    vector<int64_t> num_of_bikes_now;
    vector<int64_t> num_of_bikes_goal;

    push_bikes(num_of_bikes_now, n);
    push_bikes(num_of_bikes_goal, n);

    vector< vector<int>> tree_edges(n, vector<int>());

    for(int i = 0; i < n-1; i++)
    {
        //now input edge is 1-based, store it to 0-based
        int u, v;
        cin >> u >> v;

        tree_edges[u-1].push_back(v-1);
        tree_edges[v-1].push_back(u-1);
        //if not add line above
        //and test case is like this:
        //6 node
        //1 0
        //2 0
        //3 0
        //4 0
        //5 0
        //it will fail if your initial call is DP(0)
    }

    int64_t capacity_for_root = 
        DP(-1, 0, capacity_for_every_node, tree_edges,
            num_of_bikes_now, num_of_bikes_goal);
    //just use a variable to catch DP's return value
    //but what we need is not the root's capacity
    //what we need is the maximum capacity of every node;
    //and first parent means root's parent, which doesn't exist
    //and in DP's for loop, it will not count root's parent's capacity
    //because it doesn't exist!!!!!

    int64_t max_capacity = 0;
    for(int i = 0; i < n; i++)
    {
        if(abs(capacity_for_every_node[i]) > max_capacity)
            max_capacity = abs(capacity_for_every_node[i]);
    }

    cout << max_capacity << "\n";
}