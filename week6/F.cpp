#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Graph {
    public: 
        int vertexCount;
        std::vector < std::vector< int > > adj;

        Graph(int n){
            vertexCount = n;
            adj = std::vector < std::vector < int > > (n);
        }
        void addEdge(int u, int v){
            adj[u].push_back(v);
        }
        
};

void recursiveHelper(std::vector<int> &concurrent, std::vector<int> &possible, int units, int workers, std::vector <int> &reqWorkers){
    
}

void recursiveFindSolution(std::vector< std::vector<int> > &adjMat, int workers, int units, std::vector <int> &reqWorkers, int someIndex){
    std::vector< std::vector<int> > tmp = adjMat;
    std::vector<int> possible;
    //TODO: test if column row, right order
    for (int i = 0; i < tmp.size(); i++){
        int count = 0;
        for (int j = 0; j < tmp.size(); j++){
            if (adjMat[i][j] == 1)
                count++;
        }
        if (count == 0)
            possible.push_back(i);
    }

    std::vector<int> concurrent;
    for(int i = 0; i < possible.size(); i++){
        for (int j = i; j < possible.size(); j++){
            if (units-reqWorkers[j] >= 0)
        }
    }

    for (int i = 0; i < possible.size(); i++){
        if (units - reqWorkers[possible[i]] >= 0 && workers-reqWorkers >= 0)
            recursiveFindSolution(tmpModified, workers, units-reqWorkers[possible[i]], reqWorkers, someIndex);
        
    }
}


int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        
        /*int tasks, workers, units;
        std::cin >> tasks >> workers >> units;

        for (int j = 1; j <= tasks ; j++){
            int u, v;
            std::cin >> u >> v;

            if (v != -1){
                graph.addEdge(u,v);
            }

        }*/


        int tasks, workers, units;
        std::cin >> tasks >> workers >> units;
        std::vector< std::vector<int> > adjMat (tasks,std::vector<int>(tasks)); 
        std::vector<int> reqWorkers(tasks);

        for (int j = 0; j < tasks; j++){
            int reqWork, dep; 
            std::cin >> reqWork >> dep;
            reqWorkers[j] = reqWork;
            if (dep != -1){
                //decrease index
                //adjMat[j][dep-1] = 1;
                adjMat[dep-1][j] = 1;
            }
        }

        recursiveFindSolution(&adjMat, workers, units, reqWorkers, someIndex);

        //Accumulate the values based on the max of all previous incoming edges and the current weight.
        for (int k = 1; k < n; k++){
            int max = 0;
            //iterate from the top of the matrix to before the middle
            for (int l = 0; l < k; l++){ 
                if (adjMat[l][k] == 1 && timeunits[l] > max){
                    max = timeunits[l];
                }
            }
            timeunits[k] += max;
        }
        
        std::cout << "Case #" << i << ": " << "something" << "\n";

    }
    return 0;
}
