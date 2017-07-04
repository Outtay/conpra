// A Dynamic Programming based solution for 0-1 Knapsack problem
#include <stdio.h>
#include <iostream>
#include <vector>


// A utility function that returns maximum of two integers
int max(int a, int b) { return (a > b)? a : b; }

// Returns the maximum value that can be put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n)
{
    int i, w;
    int K[n+1][W+1];
    std::vector < std::vector <int> > table (n+1, std::vector<int>(W+1));


    // Build table K[][] in bottom up manner
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i==0 || w==0)
                table[i][w] = 0;
            else if (wt[i-1] <= w)
                    table[i][w] = max(val[i-1] + table[i-1][w-wt[i-1]], table[i-1][w]);
            else
                    table[i][w] = table[i-1][w];
        }
    }
    std::cout << "meh";

    return table[n][W];
}

int main()
{
	int val[] = {5, 1};
	int wt[] = {3, 1};
	int W = 10;
	int n = sizeof(val)/sizeof(val[0]);
	printf("%d", knapSack(W, wt, val, n));
	return 0;
}
