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
        
        int n;
        std::cin >> n;
        std::vector< std::pair<int,std::pair<int,int> > > wAdj;
        for (int j = 1; j <= n; j++){
            for (int k = 1; k <= n; k++){
                if (k <= j){
                    int ignore;
                    std::cin >> ignore;
                    continue;
                }
                int in;
                std::cin >> in;
                std::pair< int,std::pair<int,int> > temp;
                temp.first = in;
                temp.second.first = j;
                temp.second.second = k; 
                wAdj.push_back(temp);
            }
        }
        std::sort(wAdj.begin(), wAdj.end());
        UF unionF(n+1);
        std::vector< std::pair <int,int> > result;

        // Kruska
        for (int j = 0; j < wAdj.size(); j++){
            
            int u = unionF.find(wAdj[j].second.first);
            int v = unionF.find(wAdj[j].second.second);
            
            if (u != v){
                std::pair <int,int> temp;
                temp.first = wAdj[j].second.first;
                temp.second = wAdj[j].second.second;
                result.push_back(temp);
                unionF.merge(u,v);
            }
   
        }
        //http://stackoverflow.com/questions/279854/how-do-i-sort-a-vector-of-pairs-based-on-the-second-element-of-the-pair
        std::sort(result.begin(), result.end(), [](const std::pair<int,int> &left, const std::pair<int,int> &right) {
            return left.second < right.second;
        });
        std::sort(result.begin(), result.end(), [](const std::pair<int,int> &left, const std::pair<int,int> &right) {
            return left.first < right.first;
        });
        std::cout << "Case #" << i <<":\n";
        for (int j = 0; j < result.size(); j++)
            std::cout << result[j].first << " " << result[j].second << "\n";
        if (result.size() == 0)
            std::cout << "\n";

    }
    return 0;
}
