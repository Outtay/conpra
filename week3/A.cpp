#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        
        int n, m;
        std::cin >> n >> m;
        std::vector< std::vector <int> > adjList(n);
        for (int j = 1; j <= m; j++) {
            //make the case for m being 0 separately
            int a, b;
            std::cin >> a >> b;
            //-1 since indices start at 1 and I'd like them to start at 0
            adjList[a-1].push_back(b-1);
            adjList[b-1].push_back(a-1);

        }

        
        std::cout << "Case #" << i << ": " << "money" << "\n";

    }
    return 0;
}


bool isBipartite{
    
}