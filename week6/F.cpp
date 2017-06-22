#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


//https://stackoverflow.com/questions/728972/finding-all-the-subsets-of-a-set
//Generate all subsets from a given vector
std::vector< std::vector<int> > getAllSubsets(std::vector<int> set){
    std::vector< std::vector<int> > subset;
    std::vector<int> empty;
    subset.push_back( empty );

    for (int i = 0; i < set.size(); i++)
    {
        std::vector< std::vector<int> > subsetTemp = subset;

        for (int j = 0; j < subsetTemp.size(); j++)
            subsetTemp[j].push_back( set[i] );

        for (int j = 0; j < subsetTemp.size(); j++)
            subset.push_back( subsetTemp[j] );
    }
    return subset;
}


//TODO: Sort by largest amount to get better performance
std::vector <std::vector<int> > filterSubsets(std::vector < std::vector<int> > subsets, int workers, std::vector <int> &reqWorkers){
    std::vector <int> amounts;
    std::vector <std::vector<int> > filteredSubsets;
    //start with 1 to skip the empty set
    for (int i = 1; i < subsets.size(); i++){
        int amount = 0;
        for (int j = 0; j < subsets[i].size(); j++){
            amount +=  reqWorkers [ subsets[i][j] ];
        }
        if (amount <= workers){
            filteredSubsets.push_back(subsets[i]);
            amounts.push_back(amount);
        }
    }
    //remove single tasks if they are included in a multiple
    for (int i = 0; i < filteredSubsets.size(); i++){
        if (filteredSubsets[i].size() > 1){
            for (int j = 0; j < filteredSubsets[i].size(); j++){
                for (int k = 0; k < filteredSubsets.size(); k++){
                    if (filteredSubsets[k].size() == 1 && filteredSubsets[i][j] == filteredSubsets[k][0]){
                        filteredSubsets.erase(filteredSubsets.begin()+k);
                        k--; 
                        if (i > 0)
                            i--;
                    }
                }
            }
        }
    }

    //workaround to sorting the list: reverse the vector. Should improve performance since biggest sets are chosen first
    std::reverse(filteredSubsets.begin(), filteredSubsets.end());
    return filteredSubsets;
}

//remove all outgoing connections of adjMat
void removeOutgoing (std::vector< std::vector<int> > &adjMat, std::vector<int> subset){
    for (int i = 0; i < subset.size(); i++){
        for ( int y = 0; y < adjMat.size(); y++){
            adjMat[ subset[i] ][y] = 0;      
                   
        }
    }
}

bool ismatrixEmpty(std::vector< std::vector<int> > &adjMat){
    for (int i = 0; i < adjMat.size(); i++){
        for ( int j = 0; j < adjMat.size(); j++){
            if (adjMat[i][j] != 0)
                return false;
        }
    } 
    return true;
}

// a bit much when it comes to parameters
bool recursiveFindSolution(std::vector< std::vector<int> > &adjMat, int workers, int units, std::vector <int> &reqWorkers, int count, std::vector<int> & finished, std::vector<int> & unitorder){

    if (count > units)
        return false;
    //Not sure if those are the correct conditions, but they seem to work
    if (finished.size() == adjMat.size())// && ismatrixEmpty(adjMat))
        return true;
    
    std::vector<int> possible;
    //first find all the tasks without dependencies
    for (int i = 0; i < adjMat.size(); i++){
        int count = 0;
        for (int j = 0; j < adjMat.size(); j++){
            if (adjMat[j][i] == 1)
                count++;
        }
        //check if they haven't been done yet
        bool unfinished = true;
        for (int j = 0; j < finished.size() && unfinished; j++){
            if (i == finished[j])
                unfinished = false;
        }
        if (count == 0 && unfinished)
                possible.push_back(i);
    }
    
    //now filter them by finding out how many of those can actually be done at the same time
    std::vector < std::vector<int> > possibleSubsets = filterSubsets(getAllSubsets(possible), workers, reqWorkers);

    for (int i = 0; i < possibleSubsets.size(); i++){
        //remove all outgoing connections from the adjMat for the possible subset
        std::vector< std::vector<int> > tmp = adjMat;
        std::vector< int > tmpfin = finished;
        std::vector< int > tmpunit = unitorder;
        
        removeOutgoing(tmp, possibleSubsets[i]);
        finished.insert(finished.end(), possibleSubsets[i].begin(), possibleSubsets[i].end());
        for(int j = 0; j < possibleSubsets[i].size(); j++){
            unitorder[ possibleSubsets[i][j] ] = count;
        }

        if(recursiveFindSolution(tmp, workers, units, reqWorkers, ++count, finished, unitorder))
            return true;
        else{
            //revert the vectors that are needed at the end and for calculating
            finished = tmpfin;
            unitorder = tmpunit;
        }
        count--;
        
    }
    return false;
}


int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {

        int tasks, workers, units;
        std::cin >> tasks >> workers >> units;
        std::vector< std::vector<int> > adjMat (tasks,std::vector<int>(tasks)); 
        std::vector<int> reqWorkers(tasks);

        for (int j = 0; j < tasks; j++){
            int reqWork, dep; 
            std::cin >> reqWork >> dep;
            reqWorkers[j] = reqWork;
            if (dep != -1){
                //decrease index
                //adjMat[j][dep-1] = 1;
                adjMat[dep-1][j] = 1;
            }
        }

        std::vector<int> finished;
        std::vector<int> unitorder(tasks);
        if(recursiveFindSolution(adjMat, workers, units, reqWorkers, 0, finished, unitorder)){
            std::cout << "Case #" << i << ":";
            for (int j = 0; j < unitorder.size(); j++)
                std::cout << " " << unitorder[j]+1;
            std::cout << "\n";
        } else 
            std::cout << "Case #" << i << ": " << "impossible" << "\n";


    }
    return 0;
}
