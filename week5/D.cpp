#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include <sstream>


int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, m;
        std::cin >> n >> m;
        
        std::vector < std::pair<int,int> > matchesAr;
        std::vector <int> wins (n+1);
        for (int j = 1; j <= n; j++){
            int win;
            std::cin >> win;
            wins[j] = win;
        }

        for (int j = 1; j <= m; j++){
            int u, v;
            std::cin >> u >> v;
            matchesAr.push_back(std::make_pair(u,v));

        }
        
        std::vector < int > result(n+1); 
        
        //okay... this now is a really stupid algorithm
        //first find for the current team the best possible outcome
        //then find for all other teams their worst outcome in regards to letting the current team win
        //which is basically playing rather balanced
        //and finally check whether the wins of the current team are equal or bigger than the others
        for (int k = 1; k <= n; k++){
            std::vector < std::pair <int,int> > tmp;
            std::vector < int > tmpwin = wins;
            for (int j = 0; j < matchesAr.size(); j++){
                if(matchesAr[j].first == k || matchesAr[j].second == k){
                    tmpwin[k] += 1;
                } else {
                    tmp.push_back(matchesAr[j]);
                }
            }
            for (int j = 0; j < tmp.size(); j++){
                if (tmpwin[tmp[j].first] < tmpwin[tmp[j].second])
                    tmpwin[tmp[j].first]++;
                else
                    tmpwin[tmp[j].second]++;
            }
            for (int j = 1; j <= n; j++){
                if (tmpwin[k] < tmpwin[j]){
                    result[k] = -1;
                    break;
                }
                if (j == n && result[k] != -1){
                    result[k] = 1;
                }
            }

        }

        std::stringstream resultStream;
        
        for (int j = 1; j < result.size(); j++){
            if (result[j] == -1)
                resultStream << " " << "no";
            else 
                resultStream << " " << "yes";
        }
        std::string res = resultStream.str();

        std::cout << "Case #" << i << ":" << res << "\n";


    }
    return 0;
}
