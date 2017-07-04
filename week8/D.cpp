#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>

std::vector<bool> generatePrimes(long n){
    std::vector<bool> check(n);
    for( long i = 2; i < n; i++){
        check[i] = 1;
    } 
    long rootN = (long) floor(sqrt((long double) n));
    for (long i = 2; i <= rootN; i++){
        if (check[i])
            for(long j = pow((long double) i, 2.0); j <= n; j+=i)
                check[j] = false;
    }
    return check;
}

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

int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        
        int n;
        std::cin >> n;
        
        std::vector <int> candies;
        for (int j = 0; j < n; j++){
            int c;
            std::cin >> c;
            candies.push_back(c);
        }

        std::vector< std::vector <int> > subsets = getAllSubsets(candies);

        //find all real values that need to be checked for the least common mulitple
        std::set< int > lcmNumbers;
        int max = 0;
        for (int j = 0; j < subsets.size(); j++){
            int number = 0;
            for (int k = 0; k < subsets[j].size(); k++){
                number +=  subsets[j][k];
            }
            if (number > 0){
                ++number;
                lcmNumbers.insert(number);
            }
            if (number > max)
                max = number;
        }
        
        generatePrimes(max);

        
        
        std::cout << "Case #" << i << ": " << "something" << "\n";

    }
    return 0;
}
