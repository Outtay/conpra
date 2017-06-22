#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

bool recursiveDepthSearch(std::vector<int> &players, int &count, std::vector<int> &team){
    std::vector<int> tmpteam = team;

    //in this case the team is full and can be evaluated
    if(team[ team.size()-1 ] != 0){
        //check for the number on the jerseys not adding up to 13
        if ( !( team[1] == team[10] || team[2] == team[9] || team[3] == team[8] ||
            team[0] == team[11] || team[4] == team[7] || team[5] == team[6] ) ){

            //check if there is a goalie here
            bool goalie = false;
            for(int i = 0; i < team.size(); i++){
                if (team[i] == 1){
                    goalie = true;
                    break;
                }
            }
            if (goalie)
                count++;
            return true;
        } else {
            return false;
        }
    }

    //find first empty place in roster
    for(int i = 0; i < team.size(); i++){
        //if players can only have one place in the roster
        if (team[i] == 0 && (players[i] == 1 || players[i] == 2 || players[i] == 4 || players[i] == 8)){
            
            if (players[i] & 1){
                bool goalie = false;
                for (int j = 0; j < i; j++){
                    if(team[j] == 1)
                        goalie = true;
                }
                if (!goalie){
                    team[i] = 1;
                    recursiveDepthSearch( players, count,  team);
                    team = tmpteam;
                } 
            } else {
                team[i] = players[i];
                recursiveDepthSearch( players, count,  team);
                team = tmpteam;
            }
            break;
        // if there are multiple places on the roster
        } else if (team[i] == 0){
            
            if (players[i] & 1){
                bool goalie = false;
                for (int j = 0; j < team.size(); j++){
                    if(team[j] == 1)
                        goalie = true;
                }
                if (!goalie){
                    team[i] = 1;
                    recursiveDepthSearch( players, count,  team);
                    team = tmpteam;
                }
            }
            if (players[i] & 2){
                team[i] = 2;
                recursiveDepthSearch( players, count,  team);
                team = tmpteam;
            }
            if (players[i] & 4){
                team[i] = 4;
                recursiveDepthSearch( players, count,  team);
                team = tmpteam;
            }
            if (players[i] & 8){
                team[i] = 8;
                recursiveDepthSearch( players, count,  team);
                team = tmpteam;
            }
            break;
        }
    }
    return true;
}

int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {

        std::vector<int> players(11);
        for (int j = 0; j < 11; j++){
            std::string input;
            std::ws(std::cin);
            std::getline (std::cin,input);
            for (int k = 0; k < input.size(); k++){

                if (input[k] == 'G')
                    players[j] += 1;
                if (input[k] == 'D')
                    players[j] += 2;
                if (input[k] == 'M')
                    players[j] += 4;
                if (input[k] == 'S')
                    players[j] += 8;
            }
        }

        int count = 0;
        
        std::vector<int> team(11);
        recursiveDepthSearch(players, count, team);


        
        std::cout << "Case #" << i << ": " << count << "\n";

    }
    return 0;
}
