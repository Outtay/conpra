#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        
        int n, amount;
        std::cin >> n >> amount;

        std::vector <int> values;
        for (int j = 1; j <= n; j++){
            int z;
            std::cin >> z;
            values.push_back(z);
        }

        std::vector<int> table (amount+1);
        std::vector<int> coins (amount+1);

        //find the minimum amount of coins that make up an increasing sum up to the amount
        for (int j = 1; j <= amount; j++){

            int min = 1000000000;
            for (int k = 0; k < values.size() && values[k] <= j; k++){
                
                int tmp = table[j-values[k]];
                if(tmp < min){
                    table[j] = tmp + 1;
                    coins[j] = values[k];
                    min = tmp;
                }

            }

        }

        //now track back the coins that were used to get that minimum
        std::vector <int> results(n);
        int j = amount;
        //can be improved, by extracting for-loop
        while (j != 0){
            
            for(int k = 0; k < values.size(); k++){
                if(values[k] == coins[j]){
                    results[k]++;
                    break;
                }
            }

            j -= coins[j];
        }
        
        std::cout << "Case #" << i << ":";
        for (int j = 0; j < results.size(); j++){
            std::cout << " " << results[j];
        }
        std::cout << "\n";

    }
    return 0;
}
