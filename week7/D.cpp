#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        
        int n;
        std::cin >> n;
        
        std::vector < std::vector <int >> weights(n, std::vector<int>(n));
        for (int j = 0; j < n ; j++){
            for (int k = 0; k < n; k++){
                int weight; 
                std::cin >> weight;
                weights[j][k] = weight;
            }
        }

        std::vector <int> perms;
        for (int j = 1; j < n; j++){
            perms.push_back(j);
        }

        int min = 100000000;
        std::vector <int> order;

        do{
            int current = weights[ 0 ][ perms.front() ];
            for (int j = 0; j < perms.size()-1; j++){
                current += weights[ perms[j] ][ perms[j+1] ];
            }
            current += weights[ perms.back() ][ 0 ];

            if (current < min){
                min = current;
                order = perms;
            }
        } while (std::next_permutation(perms.begin(),perms.end()));
         
        
        
        std::cout << "Case #" << i << ": 1";
        for (int j = 0; j < order.size(); j++){
            std::cout << " " << order[j]+1;
        }
        std::cout << "\n";

    }
    return 0;
}
