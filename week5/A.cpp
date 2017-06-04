#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Edge {
    int to;
    int capacity;
    int flow;
    int start; //not necessary since we're in an adj List and the index of the vector element is the start
};


class Graph {
    public: 
        int vertexCount;
        std::vector <int> height; 
        std::vector <int> excess;
        std::vector< std::vector <Edge> > adjList;
        std::vector <Edge> edges;
        Graph *levelGraph;

        Graph(int n){
            vertexCount = n;
            adjList = std::vector < std::vector<Edge> > (n); 
            height = std::vector < int > (n);
            excess = std::vector < int > (n);
        }
        void addEdge(int u, int v, int cap){
            Edge to{v, cap , 0, u};
            adjList[u].push_back(to);
        }
        void addEdge2(int u, int v, int cap){
            Edge to{v, cap , 0, u};
            edges.push_back(to);
        }
        void preflow(int start);
        void preflow2(int start);
        int overFlowVertex();
        void updateReverseEdgeFlow(int i, int j, int flow);
        void updateReverseEdgeFlow2(int i, int flow);
        void relabel(int start);
        bool push2(int start);
        int getMaxFlow(int s, int t);

                        
};

void Graph::preflow(int start)
{
    
    height[start] = vertexCount;
 
    //put maximum flow in from source outgoing edges
    //set flow to capacity and create reverse edge
    //TODO: check why reverse edge necessary
    for (int i = 0; i < adjList.size(); i++)
    {
        for (int j = 0; j < adjList[i].size(); j++){
            Edge &e = adjList[i][j];

            if (e.start == start){
                e.flow = e.capacity;
                excess[ e.to ] += e.capacity; //+= or =  ?

                Edge back{start, 0 , -e.flow, e.to};
                adjList[start].push_back(back);
            } 
        }
    }
}


void Graph::preflow2(int start){

    height[start] = vertexCount;

    for (int i = 0; i < edges.size(); i++){
        if (edges[i].start == start){
            edges[i].flow = edges[i].capacity;
            excess[ edges[i].to ] += edges[i].capacity;

            Edge back{start, 0 , -edges[i].flow, edges[i].to};
            edges.push_back(back);
        }
    }
}

// returns index of overflowing Vertex
int Graph::overFlowVertex()
{
    for (int i = 0; i < excess.size(); i++)
       if (excess[i] > 0)
            return i;
 
    return -1;
}

// Update reverse flow for flow added on its Edge
void Graph::updateReverseEdgeFlow(int i, int j, int flow)
{
    //int u = edge[i].v;
    //int v = edge[i].u;
    int u = adjList[i][j].to;
    int v = adjList[i][j].start;
 
    for (int n = 0; n < adjList.size(); n++)
    {
        for (int m = 0; m < adjList[n].size(); m++){
            if (adjList[n][m].to == v && adjList[n][m].start == u){
                adjList[n][m].flow -= flow;
                return;
            }
        }
    }

    // adding reverse Edge in residual graph
    Edge back{v, 0 , flow, u};
    adjList[u].push_back(back);


}

void Graph::updateReverseEdgeFlow2(int i, int flow)
{
    int u = edges[i].to;
    int v = edges[i].start;

    for (int j = 0; j < edges.size(); j++)
    {
        if (edges[j].to == v && edges[j].start == u)
        {
            edges[j].flow -= flow;
            return;
        }
    }

    // adding reverse Edge in residual graph... why?
    Edge back{v, 0 , flow, u};
    edges.push_back(back);

}

// To push flow from overflowing vertex u
bool Graph::push2(int start)
{
   
    for (int i = 0; i < edges.size(); i++)
    {
        
        if (edges[i].start == start)
        {
            if (edges[i].flow >= edges[i].capacity)
                continue;
 
            // Push is only possible if height of adjacent
            // is smaller than height of overflowing vertex
            if (height[start] > height[edges[i].to])
            {
                // Flow to be pushed is equal to minimum of
                // remaining flow on edge and excess flow.
                int flow = std::min(edges[i].capacity - edges[i].flow, excess[start]);
 
                // Reduce excess flow for overflowing vertex
                excess[start] -= flow;
 
                // Increase excess flow for adjacent
                excess[edges[i].to] += flow;
 
                // Add residual flow (With capacity 0 and negative
                // flow)
                edges[i].flow += flow;
 
                updateReverseEdgeFlow2(i, flow);
 
                return true;
            }
        }
    }
    return false;
}

// function to relabel vertex u
void Graph::relabel(int start)
{
    // Initialize minimum height of an adjacent
    int maxHeight = 10000000;
 
    // Find the adjacent with minimum height
    for (int i = 0; i < edges.size(); i++){

        if (edges[i].start == start){
            // if flow is equal to capacity then no
            // relabeling
            if (edges[i].flow == edges[i].capacity)
                continue;
 
            // Update minimum height
            if (height[edges[i].to] < maxHeight){
                maxHeight = height[edges[i].to];
 
                // updating height of u
                height[start] = maxHeight + 1;
            }
        }
    }
}
// main function for printing maximum flow of graph
int Graph::getMaxFlow(int s, int t){
    preflow2(s);
 
    // loop until none of the Vertex is in overflow
    while (this->overFlowVertex() != -1){
        int start = this->overFlowVertex();
        if (!push2(start))
            relabel(start);
    }
 
    // ver.back() returns last Vertex, whose
    // e_flow will be final maximum flow
    return excess[t];
}

int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, m;
        std::cin >> n >> m;
        
        Graph graph(n);
        for (int j = 1; j <= m; j++){
            int u,v,cap;
            std::cin >> u >> v >> cap;
            //adjust indices
            graph.addEdge2(u-1, v-1, cap);
            graph.addEdge2(v-1, u-1, cap);
        }
        

        std::cout << "Case #" << i << ": " << graph.getMaxFlow(0,n-1) << "\n";

    }
    return 0;
}
