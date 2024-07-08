/*
Email adress: ayeletk03@gmail.com
ID: 325408409
*/

#include "Algorithms.hpp"
#include <unordered_set>//??
#include <iostream>
#include <stack>
#include <queue>
#include <limits>
#include <sstream>
#include <unordered_map>
namespace ariel{
    
    ////////////////////////////////////////////////////////////////////////////////////:is connected:
    void dfs(const vector<vector<int>>& graph, int vertex, vector<bool>& visited, stack<int>& stack) {
        visited[(unsigned int) vertex] = true;
        for (size_t i = 0; i < graph[(unsigned int) vertex].size(); ++i) {
            if (graph[(unsigned int) vertex][i] != 0 && !visited[i]) {
                dfs(graph, i, visited, stack);
            }
        }
        stack.push(vertex);
    }
        //ONLY UNDIRECTED!
    bool isConnectedUndirected(const vector<vector<int>>& graph) {
        unsigned int numVertices = graph.size();
        vector<bool> visited(numVertices, false);
        stack<int> sta;
        dfs(graph, 0, visited, sta);// Perform DFS from the first vertex
        for (bool vertexVisited : visited) {// Check if all vertices are visited
            if (!vertexVisited) return false; // Graph is not connected
        }
        return true; // Graph is connected
    }
        //DIRECTED!!!
    void dfsTranspose(const std::vector<std::vector<int>>& graphTranspose, int vertex, std::vector<bool>& visited) {
        visited[(unsigned int)vertex] = true;
        for (size_t i = 0; i < graphTranspose[(unsigned int)vertex].size(); ++i) {
            if (graphTranspose[(unsigned int)vertex][i] != 0 && !visited[i]) {
                dfsTranspose(graphTranspose, i, visited);
            }
        }
    }
    //Kosaraju-Sharir's algorithm to check strong connectivity of a graph by SCC and transposing the graph +running on it second dfs.
    bool isStronglyConnected(const vector<vector<int>>& graph) {
        unsigned int numVertices = graph.size();
        vector<bool> visited(numVertices, false);
        stack<int> stack;
        
        for (size_t  i = 0; i < numVertices; ++i) {// DFS on the original graph and filling the stack
            if (!visited[i]) {
                dfs(graph, i, visited, stack);
            }
        }

        // Transposing the graph
        vector<vector<int>> graphTranspose(numVertices, vector<int>(numVertices, 0));
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                graphTranspose[j][i] = graph[i][j];
            }
        }
        
        fill(visited.begin(), visited.end(), false);// Reset visited array

        // Perform DFS on the transposed graph
        int startVertex = stack.top();
        stack.pop();
        dfsTranspose(graphTranspose, startVertex, visited);

        for (bool vertexVisited : visited) {// Check if all vertices are visited
            if (!vertexVisited) return false; // found a vertex not reachable = Graph is not strongly connected
        }
        return true; // Graph is strongly connected
    }

    int Algorithms::isConnected(const Graph& g1){
        bool dir = g1.isDirected;
        bool isCon = (dir) ? isStronglyConnected : isConnectedUndirected;
        if (isCon == 1) return 1;
        else if (isCon == 0) return 0;
        else {
            cerr << "isConnected returns somewhere weird values.";
            return -1;
        }
    }
    //:is connected:///////////////////////////////////////////////////////////:is bipartite:
    bool colorGraph(vector<vector<int>> &G,int (&color)[],unsigned int pos, int c){
        unsigned int V = G.size();
        if(color[pos] != -1 && color[pos] !=c)
            return false;
            
        // color this pos as c and all its neighbours as 1-c
        color[pos] = c;
        bool ans = true;
        for(unsigned int i=0;i<V;i++){
            if(G[pos][i]){
                if(color[i] == -1)
                    ans &= colorGraph(G,color,i,1-c);  
                if(color[i] !=-1 && color[i] != 1-c)
                    return false;
            }
            if (!ans) return false;
        }
        return true;
    }

    string Algorithms::isBipartite(const Graph& g4) {
    unsigned int n = g4.mat.size();
    vector<int> colors(n, -1); // -1 indicates that the node is not yet colored
    vector<int> group1, group2;

    for (int start = 0; start < n; ++start) {
        if (colors[(unsigned int)start] == -1) { // Not yet colored
            queue<int> q;
            q.push(start);
            colors[(unsigned int) start] = 0;
            group1.push_back(start);

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (int neighbor = 0; neighbor < n; ++neighbor) {
                    if (g4.mat[(unsigned int)node][(unsigned int)neighbor] == 0) continue; // No edge between node and neighbor

                    if (colors[(unsigned int)neighbor] == -1) { // If the neighbor is not colored
                        colors[(unsigned int)neighbor] = 1 - colors[(unsigned int)node]; // Color with the opposite color
                        q.push(neighbor);

                        if (colors[(unsigned int)neighbor] == 0) {
                            group1.push_back(neighbor);
                        } else {
                            group2.push_back(neighbor);
                        }
                    } else if (colors[(unsigned int)neighbor] == colors[(unsigned int)node]) {
                        // If the neighbor has the same color as the current node, it's not bipartite
                        return "0";
                    }
                }
            }
        }
    }

    // If we reach here, the graph is bipartite
    stringstream result;
    result << "The graph is bipartite. ";
    result << "Group 1 = { ";
    for (int vertex : group1) {
        result << vertex << " ";
    }

    result << "}\nGroup 2 = { ";
    for (int vertex : group2) {
        result << vertex << " ";
    }
    result << "}";
    return result.str();
}

    //////////////////////////////////////////////////////////////////////////////////////:bellman ford, SP, negative cycle.
    struct Edge {
        int source, destination, weight;
    };

    vector<int> bellmanFord(const unsigned int V,  unsigned int source, vector<Edge>& negativeCycle, const vector<Edge>& edges, vector<int>& parents) {
        vector<int> distance(V, numeric_limits<int>::max());
        distance[source] = 0;

        parents.resize(V, -1);

        for (int i = 0; i < V - 1; ++i) {
            for (const auto& edge : edges) {
                int u = edge.source;
                int v = edge.destination;
                int weight = edge.weight;
                if (distance[(unsigned int)u] != numeric_limits<int>::max() && distance[(unsigned int)u] + weight < distance[(unsigned int)v]) {
                    distance[(unsigned int)v] = distance[(unsigned int)u] + weight;
                    parents[(unsigned int)v] = u;
                }
            }
        }

        // Check for negative cycles
        for (const auto& edge : edges) {
            int u = edge.source;
            int v = edge.destination;
            int weight = edge.weight;
            if (distance[(unsigned int)u] != numeric_limits<int>::max() && distance[(unsigned int)u] + weight < distance[(unsigned int)v]) {
                // Negative cycle detected
                int current = v;
                do {
                    negativeCycle.push_back({parents[(unsigned int)current], current, distance[(unsigned int)current]});
                    current = parents[(unsigned int)current];
                } while (current != v);
                return distance;
            }
        }

        return distance;
    }
/////////////////////
    string Algorithms::shortestPath(const Graph& g2, const int start, const int end){
        int V = g2.mat.size();
        vector<Edge> negativeCycle;
        vector <int> parents;
        vector<Edge> edges;
        for (size_t h =0; h<V; h++){//filling up edges vector with all matrix enteries != 0
            for (size_t r =0; r<V;r++){
                if(g2.mat[h][r]!=0) edges.push_back({(int)h,(int)r,g2.mat[h][r]});
            }
        }

        vector<int> distances = bellmanFord((unsigned int)V, (unsigned int)start, negativeCycle, edges, parents);
        string result = "-1"; 
        if(distances[(unsigned int)end]==numeric_limits<int>::max()) return result;//is ==operator working???
        if (!negativeCycle.empty()) {
          return result; // Negative cycle detected
        } 
        else {
            int dis = distances[(unsigned int)end];
            cout << "Shortest path weight: " << distances[(unsigned int)end] << ". Path: ";
            // Reconstruct path from end to start
            vector<int> path;
            int current = end;
            while (current != start) {
                path.push_back(current);
                current = parents[(unsigned int)current];
            }
            path.push_back(start);
            // Print path in reverse order
            string my_path;
            for (int i = path.size() - 1; i > 0; --i) {
                //cout << path[(unsigned int)i] << "->";
                my_path += to_string(path[(unsigned int)i]) + "->";
            }
            // cout << path[0]<<endl;
            my_path += to_string(path[0]);
            result = my_path;
        }

        return result;/////////////just for return
    }//returns the SP or vertices or -1.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int Algorithms::negativeCycle(const Graph& g5){//in helper function have an array or vector to return the actual cycle
        int V = g5.mat.size();
        vector<Edge> negativeCycle;
        vector<Edge> edges;
        for (size_t h =0; h<V; h++){//filling up edges vector with all matrix enteries != 0
            for (size_t r =0; r<V;r++){
                if(g5.mat[h][r]!=0) edges.push_back({(int)h, (int)r,g5.mat[h][r]});
            }
        }
        vector <int> parents;
        for(unsigned int l=0; l<V; l++){
            for(unsigned int k=0; k<V; k++){//unsigned..
                bellmanFord((unsigned int)V, l, negativeCycle, edges, parents);
                if (!negativeCycle.empty()) {
                    for (const auto& edge : negativeCycle) {
                        cout << edge.source << " -> " << edge.destination;
                    }
                   return 1;//SUCCESS, NS FOUND 
                } 
            }
        }
        cout << "No negative cycle detected." << endl;
        return -1;
    }

//forward declaration to avoid errors
string isContainsCycleDFS(const Graph& g, size_t src, vector<int>& colors, vector<int>& parents, vector<int>& path);
string constructCyclePath(const vector<int>& path, int start);

string Algorithms::isContainsCycle(const Graph& g) {
    vector<int> colors(g.mat.size(), 0);
    vector<int> parents(g.mat.size(), -1);
    vector<int> path;

    for (size_t i = 0; i < g.mat.size(); i++) {
        if (colors[i] == 0) {
            string cycle = isContainsCycleDFS(g, i, colors, parents, path);
            if (!cycle.empty()) {
                return cycle;
            }
        }
    }
    return "-1";
}

    
string isContainsCycleDFS(const Graph& g, size_t src, vector<int>& colors, vector<int>& parents, vector<int>& path) {
    colors[src] = 1;//1 as grey, visited
    path.push_back(src);  // add the vertex to the path

    for (size_t v = 0; v < g.mat.size(); v++) {
        if(g.mat[src][v] != 0){
            if (colors[v] == 0) {//0 as whute, unvisited
                parents[v] = static_cast<int>(src);
                string cycle = isContainsCycleDFS(g, v, colors, parents, path);
                if (!cycle.empty()) {
                    return cycle;
                }
            } else if (colors[v] == 1) {// 1 as grey, visited
                if (!g.isDirected && parents[src] == v) {
                    continue;
                }
                return constructCyclePath(path, v);
            }
        }
    }

    colors[src] = 2;//mark as visited, as black, here 2
    path.pop_back();
    return "";
}

string constructCyclePath(const vector<int>& path, int start) {
    string cycle;
    size_t v = 0;
    for (v = 0; v < path.size(); v++) {
        if (path[v] == start) {
            break;
        }
    }
    for (size_t i = v; i < path.size(); i++) {
        cycle += std::to_string(path[i]) + "->";
    }
    // Add the starting vertex to close the cycle
    cycle += std::to_string(start);
    return cycle;
}
}

