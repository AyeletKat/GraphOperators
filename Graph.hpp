/*
Email adress: ayeletk03@gmail.com
ID: 325408409
*/
# ifndef Graph_HPP
# define Graph_HPP
#include <iostream>
#include <vector>
using namespace std;

namespace ariel {
    class Graph{
        //(private)
    public: 
        bool isDirected;
        vector<vector<int>> mat;
        Graph();
        Graph(const Graph& g){//inline
            mat = g.mat;
            isDirected = g.isDirected;
        }
        Graph(const vector<vector<int>>& g1){//inline (copy constructor?)
            mat = g1;
        }
        void loadGraph(const vector<vector<int>>& gra3);//{//outline//mat = gra3;}
        void printGraph();

        void setDirected(bool b){
            isDirected = b;
        }
    
        Graph& operator=(const Graph& other);

        Graph operator+(const Graph& other) const;
        Graph operator-(const Graph& other) const;

        Graph operator-() const;// Overload the unary - operator
        Graph operator+() const;// Overload the unary + operator

        Graph operator+=(const Graph& other);
        Graph operator-=(const Graph& other);

        Graph& operator++();
        Graph operator++(int);
        Graph& operator--();
        Graph operator--(int);

        Graph operator * (int a);//all graph edges multipication by scalar
        Graph operator* (const Graph& other) const;//garph on graph multipication

        friend ostream& operator<<(ostream& os, const Graph& graph);//friend function overloading cout's << operator

        bool operator==(const Graph& other)const;
        bool operator != (const Graph& other)const;

        bool operator < (const Graph& other)const;
        bool operator > ( const Graph& other) const;
        
        bool operator <= (const Graph& other) const;
        bool operator >= (const Graph& other) const;
        };

};
# endif
