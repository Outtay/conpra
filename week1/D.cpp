#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>  

void recursiveLoser(std::vector<std::vector<int> > &schools, int numberMatch, int latestGroup){
    if (numberMatch == 5)
        return;
    
    //janky stuff to fix it, just to get it to work, after I saw that my test cases didn't work
    if (numberMatch != 0){
        if (schools[latestGroup][numberMatch] < schools[latestGroup+1][numberMatch])
            schools[latestGroup].swap(schools[latestGroup+1]);
        else
            recursiveLoser(schools, numberMatch+1, latestGroup);
        
        return;
    }

    //always compare two schools, but only the first opponent. If they're equally strong, find the winner with "recursion"
    for (int j = 1; j < schools.size(); j++){
            for (int k = 0; k < schools.size()-j; k++){
                if (schools[k][numberMatch] == schools[k+1][numberMatch]){
                    recursiveLoser(schools, numberMatch+1, k);
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

        std::string result = "";

        int n;
        scanf("%i", &n);
        std::vector<std::vector<int> > schools;
        for (int j = 0; j < n; j++){

            std::vector<int> skills(5);
            scanf ("%i %i %i %i %i" , &skills[0], &skills[1], &skills[2], &skills[3], &skills[4]);

            //sort since that makes it easier to compare and is needed anyway
            std::sort(skills.begin(), skills.end(), std::greater<int>());

            schools.push_back(skills);
        }
        //Sort all the vectors in a more or less recursive fashion
        recursiveLoser(schools, 0, 0);

        //Construct the resulting string
        for (int j = 0; j < schools.size(); j++){
            for (int k = 0; k < 5; k++){
                if (k == 4)
                    result += std::to_string(schools[j][k]) + "\n";
                else
                    result += std::to_string(schools[j][k]) + " ";
            }
        }
        printf("Case #%i:\n", i);
        printf("%s", result.c_str());
        printf("\n");
        //scanf("%i", n);

    }

    
    return 0;

}

