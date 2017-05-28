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
        std::vector< std::vector<int> > adjMat (n,std::vector<int>(n)); 
        std::vector<int> timeunits;
        for (int j = 0; j < n; j++){
            int timeunit, nosuccs;
            std::cin >> timeunit >> nosuccs;
            timeunits.push_back(timeunit);
            for (int k = 0; k < nosuccs; k++){
                int suc;
                std::cin >> suc;
                //delete all outgoing edges from the first task already here
                //and decrease index
                if (j == 0)
                    adjMat[j][suc-1] = 0; 
                else
                    adjMat[j][suc-1] = 1;
            }
        }

        int result = timeunits[0];
        adjMat[0][0] = -1; //denote that this here has been dealt with
        //look at the beginning here again, not sure
        for (int j = 1; j < n; j++){
            std::vector<int> independent;
            //Find all the remaining nodes without incoming edges(dependencies)
            for (int k = j; k < n; k++){
                if (adjMat[k][k] == -1) continue;

                int count = 0;
                for (int l = 0; l < n; l++)
                    count += adjMat[l][k];

                if (count == 0)
                    independent.push_back(k);
            }

            //if there are mulitple independent tasks, choose the max amount of time and add it to the time
            int max = 0;
            for (int k = 0; k < independent.size(); k++){
                if (max < timeunits[ independent[k] ])
                    max = timeunits[ independent[k] ];
                //remove all outgoing edges but use the diagonal for denoting whether it's already been dealt with
                for (int l = 0; l < n; l ++){
                    if (l == independent[k])
                        adjMat[ independent[k] ][l] = -1;
                    else
                        adjMat[ independent[k] ][l] = 0;
                }
            }
            result += max;
        }
        
        std::cout << "Case #" << i << ": " << result << "\n";

    }
    return 0;
}
