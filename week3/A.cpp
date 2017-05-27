#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <unordered_map>

int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        
        int n, m;
        std::cin >> n >> m;

        if (m == 0){
            std::cout << "Case #" << i << ": " << "yes" << "\n";
            continue;
        }

        //std::vector< std::pair< int,std::unordered_map<int> > > adjList (n);
        std::unordered_map<int,std::vector<int> > adjList(n);
        int colorArr [n];
        std::fill_n(colorArr, n, -1);
        for (int j = 1; j <= m; j++) {
            int a, b;
            std::cin >> a >> b;
            //-1 since indices start at 1 and I'd like them to start at 0
            adjList[a-1].push_back(b-1);
            adjList[b-1].push_back(a-1);
            int test = adjList[a-1][b-1];
            int test1 = adjList[a-1].front();
        }

        std::queue<int> bfsq;
        bfsq.push(adjList.begin()->first);
        colorArr[adjList.begin()->first] = 1;
        
        bool alright = true;
        while(!bfsq.empty()){
            int el = bfsq.front();
            for (int j = 0; j < adjList[el].size(); j++){
                if(colorArr[ adjList[el][j] ] == -1 ){
                    colorArr[ adjList[el][j] ] = (colorArr[el] + 1) %2;
                    bfsq.push(adjList[el][j]);
                } else if (colorArr[ adjList[el][j] ] == colorArr[el]) {
                    alright = false;
                    break;
                    }
            }
            if (alright)
                bfsq.pop();
            else
                break;
        }
        std::string result;
        if (!alright){
            result = "no";
        } else { 
            result = "yes";
            for (int j = 0; j < (sizeof(colorArr)/sizeof(*colorArr)); j++){
                if (colorArr[j] == -1){
                    result = "no";
                    break;
                }
            }
        } 
        std::cout << "Case #" << i << ": " << result << "\n";

    }
    return 0;
}