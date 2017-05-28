#include <stdio.h>
#include <iostream>
#include <sstream>
#include <queue>          
#include <vector>         
#include <functional> 
#include <algorithm>
#include <string>

int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, m;
        std::cin >> n >> m;
        //again like last time (ex E) I'm building my adjacency list as a list with the weight right after each neighbour.
        std::vector< std::vector<int> > adjList(n+1);        
        for (int j = 1; j <= m; j++){
            int n1, n2, weight;
            std::cin >> n1 >> n2 >> weight;
            //not adjusting indices
            adjList[n1].push_back(n2); adjList[n1].push_back(weight);
            adjList[n2].push_back(n1); adjList[n2].push_back(weight);
        }


        //use priority queue for dijkstra and a helper to access the corresponding weight in the queue
        std::priority_queue< std::pair<int,int>, std::vector< std::pair<int,int> >, std::greater< std::pair<int,int> > > pq;
        std::vector < int > pqHelper (n+1);
        std::vector < int > pred (n+1); 
        int dijinf = 1001;
        //a pair here is (weight, index of start node)
        pq.push(std::make_pair(0,1));
        pqHelper[1] = 0; 
        
        //assign dijinf to all other nodes
        for (int j = 2; j < adjList.size(); j++){
            pq.push(std::make_pair(dijinf,j));
            pqHelper[j] = dijinf;
        } 

        while (!pq.empty()){
            std::pair <int, int> v = pq.top();
            pq.pop();
            //now I saw that pq has no delete operation. following lazy advice from StackOverflow with attempt of flow control
            //http://stackoverflow.com/questions/9209323/easiest-way-of-using-min-priority-queue-with-key-update-in-c
            if (v.first == dijinf ) break;
            //+2 because I have the weight included
            for (int k = 0; k < adjList[v.second].size(); k+=2){
                int alt = v.first + adjList[v.second][k+1];
                if (alt < pqHelper[adjList[v.second][k]]){
                    int neighbour = adjList[v.second][k];
                    pqHelper[neighbour] = alt;
                    pred [neighbour] = v.second;
                    pq.push(std::make_pair(alt, neighbour));

                }
            }
        }
        
        std::cout << "Case #" << i << ": " << pqHelper[n] << "\n";

    }
    return 0;
}
