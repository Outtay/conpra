#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>


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

        //check if v is connected to all of the members in the existing result 
        bool isConnectedToAll(int v, std::set<int> & subset){
            int count = 0;
            for (std::set<int>::iterator it = subset.begin(); it != subset.end(); ++it){
                for(int j = 0; j < adj[v].size(); j++){
                    if(adj[v][j] == *it)
                        count++;
                }
            }
            if (count == subset.size())
                return true;
            else
                return false;
        }
        
};


int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        
        int n, m;
        std::cin >> n >> m;
        
        Graph graph(n);
        for (int j = 0; j < m; j++){
            int v1, v2;
            std::cin >> v1 >> v2;
            //check for duplicates
            bool alone = true;
            for (int k = 0; k < graph.adj[v1-1].size(); k++){
                if (graph.adj[v1-1][k] == v2-1)
                    alone = false;
            }
            if (alone){
                graph.addEdge(v1-1, v2-1); //adjust indices
                graph.addEdge(v2-1, v1-1);
            }
        }
        
        int max = 0;
        std::set <int> result;
        for(int j = 0; j < n; j++){
            
            //iterate over neighbours
            for(int k = 0; k < graph.adj[j].size(); k++){
                std::set <int> tmp;
                tmp.insert(j);
                //iterate again for every neighbour. Subsequent neighbours can still form maximal clique with starting vertex
                //even without the previous vertex
                for (int y = k; y < graph.adj[j].size(); y++ ){
                    if ( tmp.size() <= 1 || graph.isConnectedToAll(graph.adj[j][y],tmp))
                        tmp.insert(graph.adj[j][y]);
                }
                if (tmp.size() > max){
                    max = tmp.size();
                    result = tmp;
                    if(max == n)
                        break;
                    
                }

            }

            if (max == n)
                break;
            
        }

        std::cout << "Case #" << i << ":";
        for (std::set<int>::iterator it = result.begin(); it != result.end(); ++it){
            std::cout << ' ' << *it + 1;
        }
        std::cout << "\n";        

    }
    return 0;
}
