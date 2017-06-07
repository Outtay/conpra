#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctype.h>
#include <set>
#include <queue>


// not copied but heavily inspired by: http://www.geeksforgeeks.org/push-relabel-algorithm-set-2-implementation/

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

std::string numberExtent(std::string input, int &k){
    std::string tmpStr;
    while(k < input.size() && isdigit(input[k])){
        tmpStr.push_back(input[k]);
        k++;
    }
    return tmpStr;

}

//important
void parseJob(std::vector<int> &job, std::string input, int &k){
    for ( ; k < input.size(); k++){
        std::string tmpStr;
        tmpStr = numberExtent(input, k);

        int page = std::stoi(tmpStr);
        if ( k >= input.size()){
            job.push_back(page);
            return;
        }

        if (input[k] == ','){
            job.push_back(page);
        } else if (input[k] == '-'){
            ++k;
            int endPage = std::stoi(numberExtent(input, k));
            for (int i = page; i <= endPage; i++) 
                job.push_back(i);
        }
        
    }

}

int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        int printers, pages;
        std::cin >> printers >> pages;
        
        Graph graph(printers+pages+2);
        std::vector <std::vector <int> > printJobs (printers);
        for (int j = 0; j < printers; j++){
            std::string input;
            std::ws(std::cin);
            std::getline (std::cin,input);
            std::vector<int> job;
            int k = 0;
            parseJob(job, input, k);
            
            printJobs[j] = job;
            
        }
        //all pages can't be printed if there are not enough printers
        if(printers < pages){
            std::cout << "Case #" << i << ": " << "no" << "\n";
            continue;
        }
        

        //index-wise: 1 to pages are the pages
        //pages+1 to pages+printers are the printjobs
        //0 is the source and printers+pages+1 is the sink
        for (int j = 1; j <= pages; j++){
            //from source to every page
            graph.addEdge(0,j,1);
        }

        std::set<int> pagesinPrinters; //use to determine if all pages appear at least once in the printJobs
        for (int j = 0; j < printJobs.size(); j++){
            
            //from every job to the sink
            graph.addEdge(pages+j+1,pages+printers+1,1);

            for (int k = 0; k < printJobs[j].size(); k++){
                //between page and printerjobs
                graph.addEdge(printJobs[j][k], pages+j+1, 1);

                pagesinPrinters.insert(printJobs[j][k]);
            }
        }

        if (pagesinPrinters.size() != pages){
            std::cout << "Case #" << i << ": " << "no" << "\n";
            continue;
        }
        
        int maxFlow = graph.getMaxFlow(0,printers+pages+1);
        if (maxFlow >= pages)
            std::cout << "Case #" << i << ": " << "yes" << "\n";
        else 
            std::cout << "Case #" << i << ": " << "no" << "\n";

    }
    return 0;
}
