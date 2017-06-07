#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


// not copied but heavily inspired by: http://www.geeksforgeeks.org/push-relabel-algorithm-set-2-implementation/

struct Edge {
    int to;
    int capacity;
    int flow;
    int start;
};


class Graph {
    public: 
        int vertexCount;
        std::vector <int> height; 
        std::vector <int> excess;
        std::vector <Edge> edges;

        Graph(int n){
            vertexCount = n;
            height = std::vector < int > (n);
            excess = std::vector < int > (n);
        }
        void addEdge(int u, int v, int cap){
            Edge to{v, cap , 0, u};
            edges.push_back(to);
        }
        void preflow(int start);
        int overFlowVertexIndex();
        void updateReverseEdgeFlow(int i, int flow);
        void relabel(int start);
        bool push(int start);
        int getMaxFlow(int s, int t);

};


//fill edges from source outgoing and add reverse edges with negativ flow
void Graph::preflow(int start){

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
int Graph::overFlowVertexIndex(){

    for (int i = 1; i < excess.size() -1; i++)
       if (excess[i] > 0)
            return i;
 
    return -1;
}


void Graph::updateReverseEdgeFlow(int i, int flow){

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

//Push flow starting with (start)
bool Graph::push(int start){
   
    for (int i = 0; i < edges.size(); i++){
        
        if (edges[i].start == start){

            if (edges[i].flow >= edges[i].capacity)
                continue;
 
            //Check if height is bigger
            if (height[start] > height[edges[i].to]){

                //Find the possible flow
                int flow = std::min(edges[i].capacity - edges[i].flow, excess[start]);
 
                //Deal with excess flow in vertices of both sides of the edge
                excess[start] -= flow;
                excess[edges[i].to] += flow;
 
                //add residual flow and update reverse edge 
                edges[i].flow += flow;
                updateReverseEdgeFlow(i, flow);
 
                return true;
            }
        }
    }
    return false;
}

// function to relabel current vertex (start)
void Graph::relabel(int start){
    
    int maxHeight = 10000000;
 
    //Find the noighbor with minimum height
    for (int i = 0; i < edges.size(); i++){

        if (edges[i].start == start){
            
            if (edges[i].flow == edges[i].capacity)
                continue;
 
            //Update height
            if (height[edges[i].to] < maxHeight){
                maxHeight = height[edges[i].to];
 
                //updating height of current
                height[start] = maxHeight + 1;
            }
        }
    }
}


int Graph::getMaxFlow(int source, int sink){
    preflow(source);
 
    int start = this->overFlowVertexIndex();
    //until there is no overflow
    while (start != -1){
        if (!push(start))
            relabel(start);
        
        start = this->overFlowVertexIndex();
    }
 
    //excess of the sink
    return excess[sink];
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
            graph.addEdge(u-1, v-1, cap);
            graph.addEdge(v-1, u-1, cap);
        }
        
        int maxFlow = graph.getMaxFlow(0,n-1);
        if (maxFlow == 0)
            std::cout << "Case #" << i << ": " << "impossible" << "\n";
        else 
            std::cout << "Case #" << i << ": " << maxFlow << "\n";

    }
    return 0;
}
