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

        int days, checkpoints, switchcost;
        std::cin >> days >> checkpoints >> switchcost;

        std::vector <int> car;
        for (int j = 1; j <= days * (checkpoints + 1); j++){
            int tmp; 
            std::cin >> tmp;
            car.push_back(tmp);
        }
        std::vector <int> bike;
        for (int j = 1; j <= days * (checkpoints + 1); j++){
            int tmp; 
            std::cin >> tmp;
            bike.push_back(tmp);
        }
        
        int result = 0;
        //now build a graph as an adjacency list with weight after it for my dijkstra
        //between each other, they are connected with the switching costs
        //make a graph for each day and then add the result together
        for(int j = 1; j <= days; j++){
            int n = 2*checkpoints+2;
            std::vector< std::vector <int> > adjList(n);

            //car gets 1 to k+1
            for(int k = 0; k < checkpoints+1; k++){
                //begin at 0
                adjList[k].push_back(k+1); adjList[k].push_back(car[k+(checkpoints+1)*(j-1)]); 
            }
            //for(int k = (checkpoints+1)*(j-1); k < (checkpoints+1)*j; k++)
            
            
            //bike gets k+1 to k
            //the +2 comes from including start and end node
            //checkpoints+1 comes from the last node of the cars being the goal node
            //for(int k = (checkpoints+1)*(j-1); k < (checkpoints+1)*j; k++){
            for(int k = 0; k < (checkpoints+1); k++){
                int bikeStart = k+(checkpoints+2);
                if (k == 0){
                    adjList[0].push_back(bikeStart); adjList[0].push_back(bike[k+(checkpoints+1)*(j-1)]);
                } else if (k == checkpoints) {
                    adjList[bikeStart-1].push_back(checkpoints+1); adjList[bikeStart-1].push_back(bike[k+(checkpoints+1)*(j-1)]);
                } else {
                    adjList[bikeStart-1].push_back(bikeStart); adjList[bikeStart-1].push_back(bike[k+(checkpoints+1)*(j-1)]);
                }
            }

            /*int min = 0;
            int tmp = 0;
            for (int k = (checkpoints+1)*(j-1); k < (checkpoints+1)*j; k++){
                min += car[k];
                tmp += bike[k];
            }
            if (tmp < min)
                min = tmp;

            for (int c = 0; c < checkpoints; c++){    
                for (int k = (checkpoints+1)*(j-1); k < (checkpoints+1)*j; k++){
                    
                }
            }*/

            std::vector<int> finalweights (n);
            dijkstra(finalweights, adjList, 0, n);
            int min = finalweights[(checkpoints+1)];
            for (int k = 1; k <= checkpoints; k++){
                //add edges between the checkpoints
                adjList[k].push_back(k+(checkpoints+1)); adjList[k].push_back(switchcost); 
                adjList[k+(checkpoints+1)].push_back(k); adjList[k+(checkpoints+1)].push_back(switchcost);

                dijkstra(finalweights, adjList, 0, n);

                if (finalweights[(checkpoints+1)] < min){
                    min = finalweights[(checkpoints+1)];
                }

                //remove edges again
                adjList[k].erase(adjList[k].end()-2, adjList[k].end());
                adjList[k+(checkpoints+1)].erase(adjList[k+(checkpoints+1)].end()-2, adjList[k+(checkpoints+1)].end());
            }
            result += min;
        }
        
        std::cout << "Case #" << i << ": " << result << "\n";

    }
    return 0;
}
