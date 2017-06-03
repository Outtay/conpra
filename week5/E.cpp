#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <stack>


struct Edge {
    int to;
    int capacity;
    int flow;
    int start; //not necessary since we're in an adj List and the index of the vector element is the start
};


class Graph {
    public: 
        int vertexCount;
        std::vector <int> level; //for the level graph
        std::vector< std::vector <Edge> > adjList;
        Graph *levelGraph;

        Graph(int n){
            vertexCount = n;
            adjList = std::vector < std::vector<Edge> > (n); 
            level = std::vector < int > (n);
        }
        void addEdge(int u, int v, int cap){
            Edge to{v, cap, 0 , u};
            Edge back{u, 0, 0 , v}; //not sure what to do with this one, but should be in there
            adjList[u].push_back(to);
            adjList[v].push_back(back); //maybe just remove this one
        }
        void assignLevel(int start);
        bool constructLevel(int start, int end);
        int maxFlow(int current, int neighbourindex, int end, int flow);
};

//use BFS to construct the Levelgraph
//if the end can't be reached, it has the value of level.size()+1
void Graph::assignLevel(int start){
    
    std::queue <int> q;

    for (int i = 0; i < level.size(); i++)
        level[i] = level.size() + 1;

    level[start] = 0;
    q.push(0);

    while(!q.empty()){
        int current = q.front();
        q.pop();

        for (int i = 0; i < adjList[current].size(); i++){
            if(level[ adjList[current][i].to ] > level[current] + 1){
                level[ adjList[current][i].to ] = level[current] + 1;
                q.push(adjList[current][i].to);
            }
        }
    }
}

//TODO: Change level dependency
//returns 0 if there is no path between start and goal and 1 if there is
//also only adds edge if it still has capacity to be of use
bool Graph::constructLevel(int start, int goal){

    bool connected = false;
    levelGraph = new Graph(vertexCount);

    std::queue <int> q;
    
    for (int i = 0; i < level.size(); i++)
        level[i] = level.size() + 1;

    level[start] = 0;

    q.push(0);

    while(!q.empty()){
        int current = q.front();
        q.pop();

        for (int i = 0; i < adjList[current].size(); i++){
            if(level[ adjList[current][i].to ] > level[current] + 1 && adjList[current][i].capacity != adjList[current][i].flow){
                if (adjList[current][i].to == goal)
                    connected = true;

                q.push(adjList[current][i].to);
                level[ adjList[current][i].to ] = level[current] + 1;
                levelGraph->addEdge(current, adjList[current][i].to, adjList[current][i].capacity);

            } else if (level[ adjList[current][i].to ] == level[current] + 1){
                levelGraph->addEdge(current, adjList[current][i].to, adjList[current][i].capacity);
            }
        }
    }
    return connected;
}

//recursive DFS traversal for determining the flow
int Graph::maxFlow(int current, int neighborIndex, int end, int flow){

    if (current == end || neighborIndex >= levelGraph->adjList[current].size())
        return flow;

    for (int i = 0; i < levelGraph->adjList[current].size(); i++){

        Edge &e = levelGraph->adjList[current][neighborIndex];
        if (e.flow < e.capacity){
            int minFlow = std::min(flow, e.capacity - e.flow);
            int recFlow = maxFlow(e.to, neighborIndex+1, end, minFlow);
            //////This is the wrong edge! This should be the edge of the original graph!!!

            if (recFlow > 0){
                e.flow += recFlow;
                return recFlow;
            }

        }
    }
    

    return 10;
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
        }
        
        int j = 0;
        int flow = 0;
        while(graph.constructLevel(0,n-1)){
            flow += graph.maxFlow(j,0, n-1, 10000000);
            if (j < n-1) j++;
            delete graph.levelGraph; //no idea if this is necessary
        }
        std::cout << "Case #" << i << ": " << "something" << "\n";

        delete graph.levelGraph; //no idea if this is necessary

    }
    return 0;
}
