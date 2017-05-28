#include <stdio.h>
#include <iostream>
#include <sstream>
#include <queue>          
#include <vector>         
#include <functional> 
#include <algorithm>
#include <string>

void dijkstra(std::vector<int> &finalweights, std::vector< std::vector<int> > &adjList, int start, int n){
    //use priority queue for dijkstra and a helper to access the corresponding weight in the queue
    std::priority_queue< std::pair<int,int>, std::vector< std::pair<int,int> >, std::greater< std::pair<int,int> > > pq;
    std::vector < int > pred (n+1); 
    int dijinf = 101 + 1002;
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
        //now I saw that pq has no delete operation. following lazy advice from StackOverflow with attempt of flow control
        //http://stackoverflow.com/questions/9209323/easiest-way-of-using-min-priority-queue-with-key-update-in-c
        if (v.first == dijinf ) break;
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

        int n, m, nosuper, start, goal;
        std::cin >> n >> m >> nosuper >> start >> goal;

        if (m == 0){
            if (nosuper != 0){
                for (int j = 0; j < nosuper; j++){
                    int ign;
                    std::cin >> ign >> ign;
                }
            }
            std::cout << "Case #" << i << ": " << "impossible" << "\n";
            continue;
        }
        if (nosuper == 0){
            for (int j = 0; j < m; j++){
                int ign;
                std::cin >> ign >> ign >> ign;
            }
            std::cout << "Case #" << i << ": " << "impossible" << "\n";
            continue;
        }

        //again like last time (week 3 ex E) I'm building my adjacency list as a list with the weight right after each neighbour.
        std::vector< std::vector<int> > adjList(n+1);

        for (int j = 0; j < m; j++){
            int n1, n2, min;
            std::cin >> n1 >> n2 >> min;

            if (adjList[n1].size() != -1 ){
                adjList[n1].push_back(n2); adjList[n1].push_back(min);
                adjList[n2].push_back(n1); adjList[n2].push_back(min);
                continue;
            }

            //weed out if there are multiple roads from one city to another. Matrix representation should be faster here.
            /*int limit = adjList[n1].size();
            for(int k = 0; k < limit; k+=2){
                if (n2 == adjList[n1][k] && adjList[n1][k+1] > min){
                    for (int l = 0; l <= adjList[n2].size(); l+2){
                        if(n1 == adjList[n2][l]){
                            adjList[n1][k+1] = min; 
                            adjList[n2][l+1] = min;
                            break;
                        }
                    }
                } else if (k == adjList[n1].size() - 2){
                    adjList[n1].push_back(n2); adjList[n1].push_back(min);
                    adjList[n2].push_back(n1); adjList[n2].push_back(min);
                } 
            }*/
        }

        std::vector< std::pair<int,int> > supermarkets;

        for (int j = 0; j < nosuper; j++){
            int n, min;
            std::cin >> n >> min;
            
            //weed out if there are multiple supermarkets in a city. Could maybe done more efficiently?
            /*int limit = supermarkets.size();
            for(int k = 0; k < limit; k++){
                if (supermarkets[k].first == n && supermarkets[k].second > min){
                    supermarkets.push_back(std::make_pair(n,min));
                }
                else if (k == supermarkets.size()-1){
                    supermarkets.push_back(std::make_pair(n,min));
                }
            }*/
            if(supermarkets.size() != -1){
                supermarkets.push_back(std::make_pair(n,min));
            }
        }

        //perform djikstra from the supermarkets and then choose the minimum
        std::vector <int> finalweights(n+1);
        int min = 101+1001;
        for (int j = 0; j < supermarkets.size(); j++){
            dijkstra(finalweights, adjList, supermarkets[j].first, n);
            int minutes = finalweights[start] + finalweights[goal] + supermarkets[j].second;
            if (minutes < min) 
                min = minutes;
        }

        //could otherwise probably be constructed if the graph is not connected
        if (min == 101+1001) {
            std::cout << "Case #" << i << ": " << "impossible" << "\n";
            continue;
        }

        //formatting
        std::stringstream resultStream;
        int hour = min/60;
        min = min % 60;
        if (min / 10 == 0)
            resultStream << hour << ":" << "0" << min;
        else 
            resultStream << hour << ":" << min;
        
        std::cout << "Case #" << i << ": " << resultStream.str() << "\n";

    }
    return 0;
}
