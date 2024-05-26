#include "Algorithms.hpp"
#include <unordered_set>//??
#include <iostream>
#include <stack>
#include <limits>
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
        unsigned int numVertices = graph.size();//CHANGED HERE TO UNSIGNED INT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
    
    template <typename S> ostream& operator<<(ostream& os,const vector<S>& vector){// Printing all the elements of a vector usingo operator <<
        for (auto element : vector) {
            os << element << ", ";//chose separetor ", " as in the demo
        }
        return os;
    }

    int Algorithms::isBipartite(const Graph& g4){//prints two vertexs groups and returns 1 or prints and returns 0
        vector<vector<int>> our_mat = g4.mat;
        unsigned int V = our_mat.size();
        int color[V];
        for(unsigned int i=0;i<V;i++)
            color[i] = -1;
        unsigned int pos = 0; //start from vertex 0;
        bool colorable = colorGraph(our_mat,color,pos,1);
        vector<int> group1, group2;

        if(colorable==true){
            for(size_t d=0; d<sizeof(color);d++){//go through all "color" and separate to the two groups, then print them.
                if(color[d]==0) group1.push_back(color[d]);
                else if(color[d]==1) group2.push_back(color[d]);
                else {
                    cerr << "color vector from bepartipe contains weird content" << endl;
                    break;
                }
            }
            cout << "The graph is bipartite: A={" << group1 << "}, B={" << group2 << "}" << endl;
            return 1;
        }
        else {
            cout << "0. Graph isn't bipartite" << endl;
            return 0;
        }
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
    int Algorithms::shortestPath(const Graph& g2, const int start, const int end){
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
        if(distances[(unsigned int)end]==numeric_limits<int>::max()) return -1;//is ==operator working???
        if (!negativeCycle.empty()) {
          return -1;
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
        for (int i = path.size() - 1; i > 0; --i) {
            cout << path[(unsigned int)i] << "->";
        }
        cout << path[0]<<endl;
        }

        return 1;/////////////just for return
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

    bool hasCycleDFS(const vector<vector<int>>& adjMatrix, unsigned int V, unsigned int v, vector<bool>& visited, vector<int>& parent) {
    visited[v] = true;

    // Recursive DFS for all adjacent vertices
    for (unsigned int i = 0; i < V; ++i) {
        if (adjMatrix[v][i] != 0) {
            if (!visited[i]) {
                parent[i] = (int)v;
                if (hasCycleDFS(adjMatrix, V, i, visited, parent)) {
                    return true;
                }
            } else if (parent[v] != (int)i) { 
                // Check if it forms a cycle other than the parent-child relationship
                return true;
            }
        }
    }
    return false;
}

int Algorithms::isContainsCycle(const Graph &g) {
    vector<vector<int>> adjMatrix = g.mat;
    unsigned int V = adjMatrix.size();
    vector<bool> visited(V, false);
    vector<int> parent(V, -1);

    // Check for cycle from each vertex
    for (unsigned int i = 0; i < V; ++i) {
        if (!visited[i] && hasCycleDFS(adjMatrix, V, i, visited, parent)) {
            cout << "Cycle detected!" << endl;
            return 1;
        }
    }
    cout << "No cycle detected." << endl;
    return 0;
}

}


