#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

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

int main(){

    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        int a, b, c;
        std::cin >> a >> b >> c; 
        
        //read the money from each as "peopleAmount"
        std::vector <int> peopleAmount(a-1);
        for (int j = 0; j < a-1; j++){
            std::cin >> peopleAmount[j];
        } 
        //create the UnionFind data structure
        UF relationsUF(a+1);
        for (int j = 0; j < b*2; j+=2) {
            int firstRel, secondRel;
            std::cin >> firstRel >> secondRel;
            relationsUF.merge(firstRel, secondRel);
            
        }
        //to check if someone's married, keep them all saved
        std::vector <int> marriages(c*2);
        for (int j = 0; j < c*2; j+=2) {
            std::cin >> marriages[j] >> marriages [j+1];
            relationsUF.merge(marriages[j], marriages [j+1]);
        }

        //find the highest amount of money possible
        int money = -1;
        for (int j = 1; j < a; j++){
            if (!relationsUF.connected(j,a) && money <= peopleAmount[j-1] ){
                if ( !(std::find(marriages.begin(), marriages.end(), j) != marriages.end() ))
                    money = peopleAmount[j-1];
            }
        }
        if (money == -1)
            std::cout << "Case #" << i << ": impossible" << "\n";

        else
            std::cout << "Case #" << i << ": " << money << "\n";

        if (i != t){
            std::string blankLine;
            std::getline(std::cin, blankLine);
        }        


        

    }
    return 0;
}