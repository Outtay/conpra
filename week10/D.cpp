#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <math.h>

#define PI 3.14159265358979323846

// A directed graph using adjacency list representation
class Graph
{
    int V;    // No. of vertices in graph
    std::list<int> *adj; // Pointer to an array containing adjacency lists
    std::list<double> *area;
 
    // A recursive function used by printAllPaths()
    void printAllPathsUtil(int , int , bool [], int [], int &);
 
public:
    Graph(int V);   // Constructor
    void addEdge(int u, int v,double area);
    void printAllPaths(int s, int d);
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new std::list<int>[V];
    area = new std::list<double>[V];
}
 
void Graph::addEdge(int u, int v, double area);
{
    adj[u].push_back(v); // Add v to u’s list.
    area[u].push_back(area);
    
}
 
// Prints all paths from 's' to 'd'
void Graph::printAllPaths(int s, int d)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
 
    // Create an array to store paths
    int *path = new int[V];
    int path_index = 0; // Initialize path[] as empty
 
    // Initialize all vertices as not visited
    for (int i = 0; i < V; i++)
        visited[i] = false;
 
    // Call the recursive helper function to print all paths
    printAllPathsUtil(s, d, visited, path, path_index);
}
 
// A recursive function to print all paths from 'u' to 'd'.
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_index is current
// index in path[]
void Graph::printAllPathsUtil(int u, int d, bool visited[],
                              int path[], int &path_index)
{
    // Mark the current node and store it in path[]
    visited[u] = true;
    path[path_index] = u;
    path_index++;
 
    // If current vertex is same as destination, then print
    // current path[]
    if (u == d)
    {
        for (int i = 0; i<path_index; i++)
            cout << path[i] << " ";
        cout << endl;
    }
    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        list<int>::iterator i;
        for (int i = adj[u].begin(); i != adj[u].end(); ++i)
            if (!visited[*i])
                printAllPathsUtil(*i, d, visited, path, path_index);
    }
 
    // Remove current vertex from path[] and mark it as unvisited
    path_index--;
    visited[u] = false;
}


int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        
        int n, m;
        std::cin >> n >> m;
        
        std::vector< std::vector<int> > adjList(n+1);  
        std::vector<int> kpol(n+1);
        std::vector<double> length(n+1);
        Graph g(5);
        for (int 6j = 1; j <= m; j++){
            int x,y;
            double k,a;
            std::cin >> x >> y >> k >> a;
            //should really make a graph class here
            double S=a*a*k/(4*tan(PI/k));
            g.addEdge(x,y,S); g.addEdge(y,x, S);
            
        }
        
        std::cout << "Case #" << i << ": " << "something" << "\n";

    }
    return 0;
}
