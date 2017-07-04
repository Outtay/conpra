#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

void dijkstra(std::vector<int> &finalweights, std::vector< std::vector<int> > &adjList, int start, int n){
    //use priority queue for dijkstra and a helper to access the corresponding weight in the queue
    std::priority_queue< std::pair<int,int>, std::vector< std::pair<int,int> >, std::greater< std::pair<int,int> > > pq;
    std::vector < int > pred (n+1);
    //pretty sure this is necessary to ignore already finished nodes 
    std::vector < bool > seen(n+1);
    int dijinf = 10000002;
    //a pair here is (weight, index of start node)
    pq.push(std::make_pair(0,start));
    finalweights[start] = 0; 
    
    //assign dijinf to all other nodes
    for (int j = 1; j < adjList.size(); j++){
        if (start != j){
            pq.push(std::make_pair(dijinf,j));
            finalweights[j] = dijinf;
        }
    } 

    while (!pq.empty()){
        std::pair <int, int> v = pq.top();
        pq.pop();
        //early break?
        if(v.second == n){
            break;
        }

        if (!seen[v.second])
            seen[v.second] = true;
        else
            continue;
            
        //now I saw that pq has no decrease key  operation. following lazy advice from StackOverflow with attempt of flow control
        //http://stackoverflow.com/questions/9209323/easiest-way-of-using-min-priority-queue-with-key-update-in-c
        if (v.first >= dijinf ) break;
        //+2 because I have the weight included
        for (int k = 0; k < adjList[v.second].size(); k+=2){
            int alt = v.first + adjList[v.second][k+1];
            if (alt < finalweights[adjList[v.second][k]]){
                int neighbour = adjList[v.second][k];
                finalweights[neighbour] = alt;
                pred [neighbour] = v.second;
                pq.push(std::make_pair(alt, neighbour));

            }
        }
    }
}

int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, lights, radius;
        std::cin >> n >> lights >> radius;

        //model everything like a shortest path algorithm with the nodes being every distance step
        //and edges going from the beginning of the cone to the end and every distance step in between
        //then use dijkstra to find the shortest distance to the end
        std::vector< std::vector<int> > adjList(n+1);
        for (int j = 0; j < lights; j++){
            int pos;
            std::cin >> pos;
            int p1,p2;
            (pos-radius >= 0) ? p1 = pos-radius : p1 = 0;
            (pos+radius <= n) ? p2 = pos+radius : p2 = n;
            for (int k = 0; k < p2-p1; k++){
                adjList[p1].push_back(p2-k); adjList[p1].push_back(1);
                adjList[p2-k].push_back(p1); adjList[p2-k].push_back(1);
            }
        }

        std::vector <int> finalweights(n+1);
        
        dijkstra(finalweights, adjList, 0, n);
        
        if (finalweights.back() >= 10000002){
            std::cout << "Case #" << i << ": " << "impossible" << "\n";
        } else
            std::cout << "Case #" << i << ": " << finalweights.back() << "\n";

        
    }
    return 0;
}
