#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


/*int knapSack(int W, std::vector < int > &weights, std::vector < int > &utils, int n){

   std::vector < std::vector <int> > table (n+1, std::vector<int>(W+1));
 
   // Build table K[][] in bottom up manner
   for (int i = 0; i <= n; i++)
   {
       for (int w = 0; w <= W; w++)
       {
           if (i==0 || w==0)
               table[i][w] = 0;
           else if (weights[i-1] <= w)
                 table[i][w] = std::max(utils[i-1] + table[i-1][w-weights[i-1]],  table[i-1][w]);
           else
                 table[i][w] = table[i-1][w];
       }
   }

    // dp[i] is going to store maximum value
    // with knapsack capacity i.
    int dp[W+1];
    std::vector < int > sack(W+1);
 
    int ans = 0;
 
    for (int i=1; i<=W; i++){
        for (int j=0; j<n; j++)
            if (weights[j] <= i){
                int a = sack[i];
                int b = sack [ i - weights[j] ] + utils[j];
                sack[i] = std::max(sack[i], sack[ i-weights[j] ] + utils[j]);
            }
    }
 
    
    std::cout << "meh";
    return table[n][W];
}*/



void print_int_knap(int c, std::vector<int>& R, std::vector<int>& M, std::vector<int>& weights)
{

    if(c==0) {
        return;
    }
    if (R[c] == -1)
        print_int_knap(c - 1, R, M, weights);
    else
	    print_int_knap(c - weights[ R[c] ], R, M, weights);
	
    if (R[c] != -1)
	    std::cout << " " << R[c]+1;
}


int knapsack_int(int C, std::vector < int > &weights, std::vector < int > &utils, int n, int caseid) {
    
	//stores the profit for each capacity level
	std::vector<int> M(C+1, 0);
	//keeps track of which item number chosen for capacity c
	std::vector<int> R(C+1, -1);			

	//for each capacity c \in C
	for(int c=1; c<=C; c++)
	{
		M[c] = M[c-1];

		//try for each item to take with capacity c
		for(int i=0; i<n; i++)
		{
			int tmp=0;

			if (c >= weights[i])
				tmp = M[c-weights[i]] + utils[i];

			if (tmp > M[c])
			{
				M[c] = tmp;
				R[c] = i;
			}
		}
	} 


    std::cout << "Case #" << caseid << ":";
    // I have no idea what the optimal value should be
    if (M[C] >= C/2){
	    print_int_knap(C, R, M, weights);
    }
    std::cout << "\n";

	return M[C];
}


 
int main(){

    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {

        int cap, n;
        std::cin >> cap >> n;

        std::vector < int > weights;
        std::vector < int > utils;
        
        for (int j = 0; j < n; j++){
            int weight, util;
            std::cin >> weight >> util;
            weights.push_back(weight);
            utils.push_back(util);
        }

        

        int val[] = {60, 100, 120};
        int wt[] = {10, 20, 30};
        int  W = 50;
        //int result = knapSack(cap, weights, utils, n);
        int result2 = knapsack_int(cap,weights,utils,n, i);
    }
    return 0;
}