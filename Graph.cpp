
#include "Graph.hpp"
#include <sstream>
// #include <vector>
// #include <iostream>
namespace ariel
{
    Graph::Graph() : mat(), isDirected() {}

    bool directed;
    // isSymetric = is directed
    bool isSymetric(const vector<vector<int>> &ee){
        using vector_size_type = typename vector<vector<int>>::size_type;
        for (vector_size_type i = 0; i < ee.size(); ++i)
        {
            for (vector_size_type j = 0; j < ee.size(); ++j)
            {
                if (ee[i][j] != ee[j][i])
                    return false;
            }
        }
        return true;
    }

    void Graph::loadGraph(const vector<vector<int>> &gra3){
        if (gra3.size() != gra3[0].size())
        {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
        else
        {
            bool symetric = (isSymetric(gra3) == true) ? true : false;
            isDirected = symetric;
            mat = gra3; // actual load of matrix
        }
    }
    int countEdges(vector<vector<int>> graph, bool directed)
    {
        int numEdges = 0;
        int numRows = graph.size();
        int numCols = graph[0].size();

        for (unsigned int i = 0; i < numRows; ++i)
        {
            for (unsigned int j = 0; j < numCols; ++j)
            {
                if (graph[i][j] != 0)
                {
                    if (!directed && j <= i)
                        continue; // For undirected graphs, count only one direction
                    numEdges++;
                }
            }
        }
        return numEdges;
    }
    void Graph::printGraph(){
        int n = Graph::mat.size();
        int num_edge = countEdges(mat, isDirected);
        cout << "Graph with " << n << " vertices and " << num_edge << " edges" << endl; // check with gpt
    }

    Graph& Graph::operator=(const Graph& other) {
        if (this == &other) {
            return *this;  // Check for self-assignment
        }
        mat = other.mat;
        isDirected = other.isDirected;
        return *this;
    }

    Graph Graph::operator+(const Graph& other) const {
        if (mat.size() != other.mat.size() || (mat.size() > 0 && mat[0].size() != other.mat[0].size())) {
            throw runtime_error("Graphs must have the same dimensions to be added.");
        }

        vector<vector<int>> resultMat = mat;  // Start with a copy of the first graph's matrix

        for (size_t i = 0; i < mat.size(); i++) {
            for (size_t j = 0; j < mat[i].size(); j++)
                resultMat[i][j] += other.mat[i][j];
        }
        Graph g;
        g.loadGraph(resultMat);
        return g;
    }

    Graph Graph::operator-(const Graph& other) const {
        if (mat.size() != other.mat.size() || (mat.size() > 0 && mat[0].size() != other.mat[0].size())) {//???second part?!......
            throw runtime_error("Graphs must have the same dimensions to be subtract.");
        }

        vector<vector<int>> resultMat = mat;  // Start with a copy of the first graph's matrix

        for (size_t i = 0; i < mat.size(); i++) {//changes both loops to i++ from ++i......
            for (size_t j = 0; j < mat[i].size(); j++)
                resultMat[i][j] -= other.mat[i][j];
        }
        Graph g;
        g.loadGraph(resultMat);
        return g;
    }

    Graph Graph::operator-() const {//unary -
        vector<vector<int>> resultMat = mat;  // Start with a copy of the graph's matrix

        for (size_t i = 0; i < mat.size(); ++i) {
            for (size_t j = 0; j < mat[i].size(); ++j)
                resultMat[i][j] = -mat[i][j];//check if it understands to multiply indices by -1 or causes problems....
        }
        Graph g;
        g.loadGraph(resultMat);
        return g;
        //return Graph(resultMat);
    }

    Graph Graph::operator+() const {//unary +
        Graph g;
        g.loadGraph(mat);
        return g;
    }

    Graph Graph::operator+=(const Graph& other) {
        if (mat.size() != other.mat.size() || (mat.size() > 0 && mat[0].size() != other.mat[0].size())) {
            throw runtime_error("Graphs must have the same dimensions to be added.");
        }

        for (size_t i = 0; i < mat.size(); ++i) {
            for (size_t j = 0; j < mat[i].size(); ++j) {
                mat[i][j] += other.mat[i][j];
            }
        }
        return *this;
    }

    Graph Graph::operator-=(const Graph& other) {
        if (mat.size() != other.mat.size() || (mat.size() > 0 && mat[0].size() != other.mat[0].size())) {
            throw runtime_error("Graphs must have the same dimensions to be subtracted.");
        }

        for (size_t i = 0; i < mat.size(); ++i) {
            for (size_t j = 0; j < mat[i].size(); ++j) {
                mat[i][j] -= other.mat[i][j];
            }
        }
        return *this;
    }

    Graph& Graph::operator++() {// Prefix ++ operator, works on the graph itself
        for (auto& row : mat) {
            for (auto& val : row) {
                if (val != 0) {++val;}
            }
        }
        return *this;
    }

    Graph& Graph::operator--() {// Prefix -- operator, works on the graph itself
        for (auto& row : mat) {
            for (auto& val : row) {
                if (val != 0) {--val;}
            }
        }
        return *this;
    }

    Graph Graph::operator++(int) {// Postfix ++ operator, works on a copy of the graph
        Graph temp = *this;
        ++(*this);
        return temp;
    }

    Graph Graph::operator--(int) {// Postfix -- operator, works on a copy of the graph
        Graph temp = *this;
        --(*this);
        return temp;
    }

    Graph Graph::operator* (int a){//creates new graph which is the base graph where all edges are multiplyed by an int
        vector<vector<int>> m = mat;
        for (auto& row : m) {
            for (auto& val : row) {
                val = val*a;
            }
        }
        Graph g;
        g.loadGraph(m);
        return g;
    }

    Graph Graph::operator* (const Graph& other) const{
        if (mat.size() != other.mat.size() || (mat.size() > 0 && mat[0].size() != other.mat[0].size())) {
            throw runtime_error("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }
        vector<vector<int>> res = mat;
        for (size_t i = 0; i < mat.size(); ++i) {
            for (size_t j = 0; j < other.mat[0].size(); ++j) {
                for (size_t k = 0; k < mat[0].size(); ++k) {
                    res[i][j] += mat[i][k] * other.mat[k][j];
                }
            }
        }
        Graph newg;
        newg.loadGraph(res);
        return newg;
    }

    ostream& operator<<(ostream& os, const Graph& graph) {
        for (const auto& row : graph.mat) {
            for (int val : row) {
                os << val << " ";
            }
            os << endl;
        }
        return os;
    }

    bool sameEdges (const Graph& a, const Graph& other){
        if (a.mat.size() != other.mat.size() || (a.mat.size() > 0 && a.mat[0].size() != other.mat[0].size())) {
            throw runtime_error("Matrix dimensions do not match for multiplication.");
        }
        for(size_t i=0; i < a.mat.size(); i++){
            for (size_t j=0; j < a.mat.size(); j++){
                if ((a.mat[i][j]!=0 && other.mat[i][j]==0) || (a.mat[i][j]==0 && other.mat[i][j]!=0)) {return false;}
            }
        }
        return true;//same dimensions and same edges
    }
    bool Graph::operator==(const Graph& other)const{
        if (sameEdges(*this, other) == true) return true;
        if (((*this > other) == false) && (*this < other) == false) return true;
        return false;
    }

    bool Graph::operator != (const Graph& other)const{
        bool res = (*this == other) ? false : true;
        return res;
    }
    bool isSubmatrix(const Graph& original, const Graph& subgraph) {
        size_t numRows = original.mat.size();
        size_t numCols = original.mat[0].size();
        size_t subRows = subgraph.mat.size();
        size_t subCols = subgraph.mat[0].size();

        for (size_t i = 0; i <= numRows - subRows; ++i) {
            for (size_t j = 0; j <= numCols - subCols; ++j) {
                bool match = true;
                for (size_t sub_i = 0; sub_i < subRows && match; ++sub_i) {
                    for (size_t sub_j = 0; sub_j < subCols; ++sub_j) {
                        if (original.mat[i + sub_i][j + sub_j] != subgraph.mat[sub_i][sub_j]) {
                            match = false;
                            break;
                        }
                    }
                }
                if (match) {
                    return true;
                }
            }
        }
        return false;
    }

    bool Graph::operator < (const Graph& other)const{
        bool this_is_sub_other = isSubmatrix(other, *this);
        if (this_is_sub_other == true) return true;

        bool other_is_sub_this = isSubmatrix(*this, other);
        if (other_is_sub_this == true) return false;

        if (this_is_sub_other == false && other_is_sub_this == false){
            bool samedges = sameEdges(*this, other);
            if (samedges == true) return false;
            else {//not subGraphs of each other and the graphs dont have the same edges (same structure practically)
                int edgesthis = countEdges(this->mat, this->isDirected);
                int edgesother = countEdges (other.mat, other.isDirected);
                if (edgesthis < edgesother) return true;
                else if (edgesthis > edgesother) return false;
                else{//same num edges
                    if (this->mat.size() < (other.mat.size())) return true;
                    else return false;
                }
            }
        }
        return false;
    }
    bool Graph::operator > ( const Graph& other) const{
        bool this_is_sub_other = isSubmatrix(other, *this);
        if (this_is_sub_other == true) return false;

        bool other_is_sub_this = isSubmatrix(*this, other);
        if (other_is_sub_this == true) return true;

        if (this_is_sub_other == false && other_is_sub_this == false){
            bool samedges = sameEdges(*this, other);
            if (samedges == true) return false;
            else {//not subGraphs of each other and the graphs dont have the same edges (same structure practically)
                int edgesthis = countEdges(this->mat, this->isDirected);
                int edgesother = countEdges (other.mat, other.isDirected);
                if (edgesthis < edgesother) return false;
                else if (edgesthis > edgesother) return true;
                else{//same num edges
                    if (this->mat.size() > (other.mat.size())) return true;
                    else return false;
                }
            }
        }
        return false;
    }

    bool Graph::operator <= (const Graph& other) const{
        if (*this < other || *this == other) return true;
        else return false;
    }
    bool Graph::operator >= (const Graph& other) const{
        if (*this > other || *this == other) return true;
        else return false;
    }
}
