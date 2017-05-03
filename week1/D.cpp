#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>  

void recursiveLoser(std::vector<std::vector<int>> &schools, int numberMatch){
    if (numberMatch == 5)
        return;
    for (int j = 1; j < schools.size(); j++){
            for (int k = 0; k < schools.size()-j; k++){
                if (schools[k][numberMatch] == schools[k+1][numberMatch]){
                    recursiveLoser(schools, numberMatch+1);
                }
                if (schools[k][numberMatch] < schools[k+1][numberMatch]){
                    schools[k].swap(schools[k+1]);
                }
            }       
    }   
}



int main (){

    int t;
    scanf("%i", &t);
    for (int i = 1; i <= t; i++) {

        int n;
        scanf("%i", &n);
        std::vector<std::vector<int>> schools;
        for (int j = 0; j < n; j++){
            std::vector<int> skills(5);
            //scanf("%i", &skills[0]);
            scanf ("%i %i %i %i %i" , &skills[0], &skills[1], &skills[2], &skills[3], &skills[4]);
            std::sort(skills.begin(), skills.end(), std::greater<int>());

            schools.push_back(skills);
            //scanf("%i", x1);
        }
        recursiveLoser(schools, 0);
        scanf("%i", t);

    }
    scanf("%i", t);

    return 0;

}

