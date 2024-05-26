### Email adress: ayeletk03@gmail.com
### ID: 325408409


# cpp_task_2 : operators on Graphs
software programming 2 course, cpp, second task, operators on Graphs

## Overview
This exercise was about the `Graph` data structure class and implementing different operators for this type of objects. These Graphs support both directed and undirected graphs.

## Graph Class
- **Constructor**
  - `Graph()`: Initializes an empty graph.
  - `Graph(const Graph& g)` : A copy constructor.

- **Member Functions**
  - `void loadGraph(const std::vector<std::vector<int>>& gra3)`: Loads a graph from a square adjacency matrix. Throws an error if the matrix is not square.
  - `void printGraph()`: Prints the graph's adjacency matrix, number of vertices, and number of edges.

### Operators

- **Assignment Operator**
  - `Graph& operator=(const Graph& other)`: Assigns one graph to another.

- **Arithmetic Operators**
  - `Graph operator+(const Graph& other) const`: Adds two graphs by adding corresponding edges.
  - `Graph operator-(const Graph& other) const`: Subtracts one graph from another by subtracting corresponding edges.
  - `Graph operator*(int a)`: Multiplies all edges of the graph by an integer.
  - `Graph operator*(const Graph& other) const`: Multiplies two graphs using matrix multiplication.

- **Unary Operators**
  - `Graph operator-() const`: Negates all edges of the graph.
  - `Graph operator+() const`: Returns a copy of the graph.

- **Compound Assignment Operators**
  - `Graph& operator+=(const Graph& other)`: Adds another graph to the current graph.
  - `Graph& operator-=(const Graph& other)`: Subtracts another graph from the current graph.

- **Increment and Decrement Operators**
  - `Graph& operator++()`: Prefix increment; increases all non-zero edges by 1.
  - `Graph& operator--()`: Prefix decrement; decreases all non-zero edges by 1.
  - `Graph operator++(int)`: Postfix increment; increases all non-zero edges by 1.
  - `Graph operator--(int)`: Postfix decrement; decreases all non-zero edges by 1.

- **Stream Insertion Operator**
  - `friend std::ostream& operator<<(std::ostream& os, const Graph& graph)`: Outputs the adjacency matrix of the graph to a stream.


- **Comparison Operators**
  - `bool operator==(const Graph& other) const`: Compares two graphs for equality.
  - `bool operator!=(const Graph& other) const`: Compares two graphs for inequality.
  - `bool operator<(const Graph& other) const`: Checks if the current graph is a subgraph of another graph or has fewer edges.
  - `bool operator>(const Graph& other) const`: Checks if the current graph is a supergraph of another graph or has more edges.
  - `bool operator<=(const Graph& other) const`: Checks if the current graph is less than or equal to another graph.
  - `bool operator>=(const Graph& other) const`: Checks if the current graph is greater than or equal to another graph.


### Utility Functions
- `bool isSymetric(const std::vector<std::vector<int>>& ee)`: Checks if a given adjacency matrix is symmetric.
- `int countEdges(std::vector<std::vector<int>> graph, bool directed)`: Counts the number of edges in the graph.
- `bool sameEdges(const Graph& a, const Graph& other)`: Checks if two graphs have the same edges.
- `bool isSubmatrix(const Graph& original, const Graph& subgraph)`: Checks if one graph is a submatrix of another.


