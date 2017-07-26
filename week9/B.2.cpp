#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


using namespace std;
 

int carAssembly(vector<int> car, vector<int> bike, vector<int> switchcosts, vector<int> entry, vector<int> exitt)
{
	vector<int> T1(car.size());
    vector<int> T2(car.size());
    int i;

	T1[0] = entry[0];//+ car[0]; // time taken to leave first station in line 1
	T2[0] = entry[1];// + bike[0]; // time taken to leave first station in line 2

	// Fill tables T1[] and T2[] using the above given recursive relations
	for (i = 0; i < T2.size(); ++i)
	{
		T1[i] = min(T1[i-1] + car[i], T2[i-1] + switchcosts[i] + car[i]);
		T2[i] = min(T2[i-1] + bike[i], T1[i-1] + switchcosts[i] + bike[i]);
	}

	// Consider exit times and retutn minimum
	return min(T1.back() + exitt[0], T2.back() + exitt[1]);
}

int main(){
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {

        vector<int> entry(2), exitt(2);

        int days, checkpoints, switchcost;
        cin >> days >> checkpoints >> switchcost;
        
        vector < int > switchcosts;
        vector <int> car;
        for (int j = 1; j <= days * (checkpoints + 1); j++){
            int tmp; 
            cin >> tmp;
            
            car.push_back(tmp);

            
            if (j % days == 0)
                switchcosts.push_back(switchcost);
            else 
                switchcosts.push_back(0);
            
            
        }
        vector <int> bike;
        for (int j = 1; j <= days * (checkpoints + 1); j++){
            int tmp; 
            cin >> tmp;
            
            bike.push_back(tmp);
        }

        int result = carAssembly(car, bike, switchcosts, entry, exitt);
        cout << result;
    }

    return 0;
}