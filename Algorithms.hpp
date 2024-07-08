#ifndef Algorithms_HPP
#define Algorithms_HPP
#include <string>
#include "Graph.hpp"

using namespace ariel;

namespace ariel {
    //class Graph;
    class Algorithms{
        public:
            static int isConnected(const Graph& g1);
            static string shortestPath(const Graph& g2, const int start, const int end);//returns the SP or vertices or -1.
            static string isContainsCycle(const Graph& g3);//prings cycle or 0
            static string isBipartite(const Graph& g4);//returns two groups of vertices or 0
            static int negativeCycle(const Graph& g5);//find negative cycle or print if there is not
        private:
            Algorithms(){}
    };
};
#endif