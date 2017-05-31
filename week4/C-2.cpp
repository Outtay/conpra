#include <stdio.h>
#include <iostream>
#include <sstream>
#include <queue>          
#include <vector>         
#include <functional> 
#include <algorithm>
#include <string>

int main (){
    std :: ios_base :: sync_with_stdio ( false );

    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        int n;
        std::cin >> n;
        //again like last time (week 3 ex E) I'm building my adjacency list as a list with the weight right after each neighbour.
        std::vector<int> timeunits;
        std::vector< std::vector<int> > adjList(n+1); 
        for (int j = 1; j <= n; j++){
            int timeunit, nosuccs;
            std::cin >> timeunit >> nosuccs;
            timeunits.push_back(timeunit);
            for (int k = 0; k < nosuccs; k++){
                int suc;
                std::cin >> suc;
                adjList[j].push_back(suc); 
                adjList[j].push_back(0); //weight
            }
        }

        //fill in the weights for the adjList
        for (int j = 1; j < adjList.size(); j++){
            for (int k = 0; k < adjList[j].size(); k+=2){
                adjList[j][k+1] = - timeunits[ adjList[j][k] - 1 ]; //-1 since indices are shifted, and - since we want the longest path with dijkstra
            }
        }


        int start = 1;
        //use priority queue for dijkstra and a helper to access the corresponding weight in the queue
        std::priority_queue< std::pair<int,int>, std::vector< std::pair<int,int> >, std::greater< std::pair<int,int> > > pq;
        std::vector < int > pred (n+1);
        std::vector <int> finalweights(n+1);
        //pretty sure this is necessary to ignore already finished nodes 
        std::vector < bool > seen(n+1);
        int dijinf = 1000002;
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

            //oh wow... this is not working, why would I even think this?
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
        //find the longest (reverse shortest) path
        int result = timeunits[0];
        int min = 0;
        for (int j = 1; j < finalweights.size(); j++){
            if (finalweights[j] < min)
                min = finalweights[j];
        }
        result -= min;

        std::cout << "Case #" << i << ": " << result << "\n";


    }  

    return 0;
}
