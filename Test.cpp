/*
Email adress: ayeletk03@gmail.com
ID: 325408409
*/
#include "doctest.h"
#include "Graph.hpp"
#include <sstream>

using namespace std;

TEST_CASE("Test graph addition") {
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}
    };
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}
    };

    ostringstream oss;
    oss << g3;
    CHECK(oss.str() == "0 2 1 \n2 0 3 \n1 3 0 \n");
}

TEST_CASE("Test graph multiplication") {
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}
    };
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {1, 0, 2},
        {1, 0, 1},
        {1, 0, 0}
    };

    ostringstream oss;
    oss << g4;
    CHECK(oss.str() == "1 0 2 \n1 0 1 \n1 0 0 \n");
}

TEST_CASE("Invalid operations") {
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}
    };
    g2.loadGraph(weightedGraph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}
    };
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}
    };
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}

TEST_CASE("Test unary minus operator") {
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, -2},
        {1, 0, 1},
        {-2, 1, 0}
    };
    g1.loadGraph(graph);
    ariel::Graph g2 = -g1;
    vector<vector<int>> expectedGraph = {
        {0, -1, 2},
        {-1, 0, -1},
        {2, -1, 0}
    };

    ostringstream oss;
    oss << g2;
    CHECK(oss.str() == "0 -1 2 \n-1 0 -1 \n2 -1 0 \n");
}

TEST_CASE("Test unary plus operator") {
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, -2},
        {1, 0, 1},
        {-2, 1, 0}
    };
    g1.loadGraph(graph);
    ariel::Graph g2 = +g1;

    ostringstream oss;
    oss << g2;
    CHECK(oss.str() == "0 1 -2 \n1 0 1 \n-2 1 0 \n");
}

TEST_CASE("Test increment operators") {
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, -2},
        {1, 0, 1},
        {-2, 1, 0}
    };
    g1.loadGraph(graph);

    ariel::Graph g2 = g1++;
    vector<vector<int>> expectedGraph1 = {
        {0, 1, -2},
        {1, 0, 1},
        {-2, 1, 0}
    };
    vector<vector<int>> expectedGraph2 = {
        {0, 2, -1},
        {2, 0, 2},
        {-1, 2, 0}
    };

    ostringstream oss1, oss2;
    oss1 << g2;
    oss2 << g1;
    CHECK(oss1.str() == "0 1 -2 \n1 0 1 \n-2 1 0 \n");
    CHECK(oss2.str() == "0 2 -1 \n2 0 2 \n-1 2 0 \n");

    ++g1;
    vector<vector<int>> expectedGraph3 = {
        {0, 3, 0},
        {3, 0, 3},
        {0, 3, 0}
    };

    ostringstream oss3;
    oss3 << g1;
    CHECK(oss3.str() == "0 3 0 \n3 0 3 \n0 3 0 \n");
}

TEST_CASE("Test decrement operators") {
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, -1},
        {2, 0, 2},
        {-1, 2, 0}
    };
    g1.loadGraph(graph);

    ariel::Graph g2 = g1--;
    vector<vector<int>> expectedGraph1 = {
        {0, 2, -1},
        {2, 0, 2},
        {-1, 2, 0}
    };
    vector<vector<int>> expectedGraph2 = {
        {0, 1, -2},
        {1, 0, 1},
        {-2, 1, 0}
    };

    ostringstream oss1, oss2;
    oss1 << g2;
    oss2 << g1;
    CHECK(oss1.str() == "0 2 -1 \n2 0 2 \n-1 2 0 \n");
    CHECK(oss2.str() == "0 1 -2 \n1 0 1 \n-2 1 0 \n");

    --g1;
    vector<vector<int>> expectedGraph3 = {
        {0, 0, -3},
        {0, 0, 0},
        {-3, 0, 0}
    };

    ostringstream oss3;
    oss3 << g1;
    CHECK(oss3.str() == "0 0 -3 \n0 0 0 \n-3 0 0 \n");
}

TEST_CASE("Test scalar multiplication") {
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 2},
        {1, 0, 1},
        {2, 1, 0}
    };
    g1.loadGraph(graph);

    ariel::Graph g2 = g1 * 3;
    vector<vector<int>> expectedGraph = {
        {0, 3, 6},
        {3, 0, 3},
        {6, 3, 0}
    };

    ostringstream oss;
    oss << g2;
    CHECK(oss.str() == "0 3 6 \n3 0 3 \n6 3 0 \n");
}

TEST_CASE("Test equality operators") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 1},
        {2, 1, 0}
    };
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 2},
        {1, 0, 1},
        {2, 1, 0}
    };
    g2.loadGraph(graph2);

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 2, 1},
        {2, 0, 2},
        {1, 2, 0}
    };
    g3.loadGraph(graph3);

    CHECK(g1 == g2);
    CHECK(g1 != g3);
}

TEST_CASE("Test less than and greater than operators") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 1},
        {2, 1, 0}
    };
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 2},
        {1, 0, 1},
        {2, 1, 0}
    };
    g2.loadGraph(graph2);

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1},
        {1, 0}
    };
    g3.loadGraph(graph3);

    CHECK(!(g1 < g2));
    CHECK(!(g1 > g2));
    CHECK(g3 < g1);
    CHECK(g1 > g3);
}
