#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctype.h>
#include <set>
#include <queue>


// Code from Problem C from Last week

struct Edge {
    int to;
    int capacity;
    int flow;
    //int start;
};


class Graph {
    public: 
        int vertexCount;
        std::vector <int> height; 
        std::vector <int> excess;
        //std::vector <Edge> edges;
        std::vector < std::vector< Edge > > adj;
        std::queue <int> flowq; //for selection

        Graph(int n){
            vertexCount = n;
            height = std::vector < int > (n);
            excess = std::vector < int > (n);
            adj = std::vector < std::vector <Edge> > (n);
        }
        void addEdge(int u, int v, int cap){
            Edge to{v, cap , 0};
            //edges.push_back(to);
            adj[u].push_back(to);
        }
        void preflow(int start);
        int overFlowVertexIndex();
        void updateReverseEdgeFlow(int i, int j, int flow);
        void relabel(int start);
        bool push(int start);
        int getMaxFlow(int s, int t);

};


//fill edges from source outgoing and add reverse edges with negativ flow
void Graph::preflow(int start){

    height[start] = vertexCount;

    for (int i = 0; i < adj[start].size(); i++){
        
        adj[start][i].flow =  adj[start][i].capacity;
        excess[ adj[start][i].to ] +=  adj[start][i].capacity;
        excess[start] -=  adj[start][i].capacity;

        flowq.push( adj[start][i].to);

        //for self loops
        if (start !=  adj[start][i].to){
            Edge back{start, 0 , - adj[start][i].flow};
            adj[ adj[start][i].to ].push_back(back);
        
        }
    }
}


void Graph::updateReverseEdgeFlow(int i, int j, int flow){

    int u =  adj[i][j].to;
    int v = i;

    for (int i = 0; i < adj[u].size(); i++){
        if (adj[u][i].to == v){
            adj[u][i].flow -= flow;
        }
    } 

    // adding reverse Edge in residual graph. necessary?
    Edge back{v, 0 , flow};
    adj[u].push_back(back);

}

//Push flow starting with (start)
bool Graph::push(int start){


    for (int i = 0; i < adj[start].size(); i++){
        
        if (adj[start][i].flow == adj[start][i].capacity)
            continue;
        
    //Check if height is bigger
        if (height[start] > height[ adj[start][i].to ]){

            //Find the possible flow
            //if (edge[i].capacity == 0){}
            int flow = std::min(adj[start][i].capacity - adj[start][i].flow, excess[start]);
            if (flow < 0) flow *= -1; //I think... this should work?
            //Deal with excess flow in vertices of both sides of the edge
            excess[start] -= flow;
            excess[ adj[start][i].to ] += flow;
            if (excess[ adj[start][i].to ] > 0) flowq.push(adj[start][i].to);

            //add residual flow and update reverse edge 
            adj[start][i].flow += flow;
            updateReverseEdgeFlow(start, i, flow);

            return true;
        }
    }

    return false;
}

// function to relabel current vertex (start)
void Graph::relabel(int start){
    
    int maxHeight = 10000000;
 
    //Find the neighbor with minimum height
    for (int i = 0; i < adj[start].size(); i++){
            
        if (adj[start][i].flow == adj[start][i].capacity)
            continue;

        //Update height
        if (height[ adj[start][i].to ] < maxHeight){
            maxHeight = height[ adj[start][i].to ];

            //updating height of current
            height[start] = maxHeight + 1;
        }
        
    }
}


int Graph::getMaxFlow(int source, int sink){
    preflow(source);
    
    int start = source;
    int count = 0;
    //while there aren't any nodes with excess flow larger than 0
    while (!flowq.empty()){
        count++;
        start = flowq.front();
        if (count >= 41) 
            start = flowq.front();

        if (excess[start] > 0 && !push(start) && start != sink)
            relabel(start);
        
        if(excess[start] <= 0 || start == vertexCount - 1)
            flowq.pop();
        
    }
 
    //excess of the sink
    return excess[sink];
}


int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        int bakers, judges;
        std::cin >> bakers >> judges;

        Graph graph(bakers*2+judges+2);

        std::vector <std::vector <int> > judgePrefs (judges);
        for (int j = 0; j < judges; j++){
            
            int pref;
            std::cin >> pref;
            while(pref != 0){
                //convert into indexed nodes
                if(pref < 0){
                    pref *= -2;
                } else {
                    pref = pref * 2 - 1;
                }

                judgePrefs[j].push_back(pref);
                std::cin >> pref;
            }         
        }

        //index-wise: 1 to bakers*2 are the recipes
        //bakers*2+1 to bakers*2+judges are the judges
        //0 is the source and bakers*2+judges+1 is the sink
        for (int j = 1; j <= bakers; j++){
            //from source to every recipe of the bakers. One baker has two recipes
            graph.addEdge(0,j*2-1,1);
            graph.addEdge(0,j*2,1);
        }

        for (int j = 0; j < judgePrefs.size(); j++){
            
            //from every judge to the sink
            graph.addEdge(bakers*2+j+1,bakers*2+judges+1,1);

            for (int k = 0; k < judgePrefs[j].size(); k++){
                //between page and printerjobs
                graph.addEdge(judgePrefs[j][k], bakers*2+j+1, 1);
            }
        }

        //judges can't be satisfied if they get nothing 
        //needs to be changed, since judges don't need to have a preference
        int realJudges = 0;
        for (int j = 0; j < judgePrefs.size(); j++){
            if (judgePrefs[j].size() > 0){
                realJudges++;
            }
        }
        if(bakers < realJudges){
            std::cout << "Case #" << i << ": " << "no" << "\n";
            continue;
        }

        
        int maxFlow = graph.getMaxFlow(0,bakers*2+judges+1);
        if (maxFlow >= realJudges)
            std::cout << "Case #" << i << ": " << "yes" << "\n";
        else 
            std::cout << "Case #" << i << ": " << "no" << "\n";

    }
    return 0;
}
