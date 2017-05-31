#include <stdio.h>
#include <iostream>
#include <vector>

int main (){
    
    int t;
    std::cin >> t;
    
    for (int i = 1; i <= t; i++) {
        int n;
        std::cin >> n;
        std::vector< std::vector<int> > adjMat (n,std::vector<int>(n)); 
        std::vector<int> timeunits;
        for (int j = 0; j < n; j++){
            int timeunit, nosuccs;
            std::cin >> timeunit >> nosuccs;
            timeunits.push_back(timeunit);
            for (int k = 0; k < nosuccs; k++){
                int suc;
                std::cin >> suc;
                //decrease index
                adjMat[j][suc-1] = 1;
            }
        }

        //Accumulate the values based on the max of all previous incoming edges and the current weight.
        for (int k = 1; k < n; k++){
            int max = 0;
            //iterate from the top of the matrix to before the middle
            for (int l = 0; l < k; l++){ 
                if (adjMat[l][k] == 1 && timeunits[l] > max){
                    max = timeunits[l];
                }
            }
            timeunits[k] += max;
        }
        std::cout << "Case #" << i << ": " << timeunits[n-1] << "\n";
    }
    return 0;
}
