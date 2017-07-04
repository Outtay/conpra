#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main (){

    std :: ios_base :: sync_with_stdio ( false );
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        long ntrees, nsaws;
        std::cin >> ntrees >> nsaws;

        std::vector<long long> trees(ntrees);
        std::vector<long long> saws(nsaws);
        for (int j = 0; j < ntrees; j++){
            long long length;
            std::cin >> length;

            trees[j] = length;
        }

        std::sort(trees.begin(), trees.end(), std::greater<long long>());

        for (long j = 0; j < trees.size(); j++){
            
            long saw = 0;
            //find the saw with minimal work
            if ( j < saws.size())
                saw = j;
            else {
                for (int k = 0; k < saws.size(); k++){
                    if ( saws[saw] > saws[k] )
                        saw = k;
                }
            }
            //add tree to this saw
            saws[saw] += trees[j];
        }


        long max = 0;
        for (int j = 0; j < saws.size(); j++){
            if (saws[j] > max)
                max = saws[j];
        }
        
        std::cout << "Case #" << i << ": " << max << "\n";

    }
    return 0;
}
