#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

//source: http://stackoverflow.com/questions/8300125/union-find-data-structure
class UF {
  int *id, cnt, *sz;
  public:
// Create an empty union find data structure with N isolated sets.
UF(int N) {
    cnt = N; id = new int[N]; sz = new int[N];
    for (int i = 0; i<N; i++)  id[i] = i, sz[i] = 1; }
~UF() { delete[] id; delete[] sz; }

// Return the id of component corresponding to object p.
int find(int p) {
    int root = p;
    while (root != id[root])    root = id[root];
    while (p != root) { int newp = id[p]; id[p] = root; p = newp; }
    return root;
}
// Replace sets containing x and y with their union.
void merge(int x, int y) {
    int i = find(x); int j = find(y); if (i == j) return;
    // make smaller root point to larger one
    if (sz[i] < sz[j]) { id[i] = j, sz[j] += sz[i]; }
    else { id[j] = i, sz[i] += sz[j]; }
    cnt--;
}
// Are objects x and y in the same set?
bool connected(int x, int y) { return find(x) == find(y); }
// Return the number of disjoint sets.
int count() { return cnt; }
};

int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        int cities, roads;
        std::cin >> cities >> roads;
        std::vector< std::pair<int,std::pair<int,int> > > wAdj;

        for (int j = 1; j <= roads; j++){
            int start, end, length, lanes;
            std::cin >> start >> end >> length >> lanes;
            
            std::pair< int,std::pair<int,int> > temp;
            temp.first = length * lanes;
            temp.second.first = start;
            temp.second.second = end; 
            wAdj.push_back(temp);
        }

        if (roads < cities -1){
            std::cout << "Case #" << i << ": " << "impossible" <<"\n";
            continue;
        }

        //reverse order
        std::sort(wAdj.rbegin(), wAdj.rend());
        UF unionF(cities+1);
        int result = 0;

        // Kruska
        for (int j = 0; j < wAdj.size(); j++){
            
            int u = unionF.find(wAdj[j].second.first);
            int v = unionF.find(wAdj[j].second.second);
            
            if (u != v){
                unionF.merge(u,v);
            } else {
                result += wAdj[j].first;
            }
   
        }

        bool connected = true;
        //check whether graph is connected
        for (int j = 1; j <= cities; j++){
            for (int k = 1; j <= cities; j++){
                if (!unionF.connected(j,k)){
                    connected = false;
                    break;
                }
            }
            if (!connected) break;
        }
        
        if (connected)
            std::cout << "Case #" << i << ": " << result <<"\n";
        else
            std::cout << "Case #" << i << ": " << "impossible" <<"\n";

        

    }
    return 0;
}
