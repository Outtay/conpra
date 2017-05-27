#include <stdio.h>
#include <iostream>
#include <sstream>
#include <queue>          
#include <vector>         
#include <functional> 
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
        std::vector< std::vector<int> > reducedEdges(n+1);

        for (int j = 0; j < wAdj.size(); j++){

            unionF.merge(wAdj[j].second.first, wAdj[j].second.second);
            //build adjacency list with entry after neighbour being the weight
            reducedEdges[wAdj[j].second.first].push_back(wAdj[j].second.second);
            reducedEdges[wAdj[j].second.first].push_back(wAdj[j].first);

            reducedEdges[wAdj[j].second.second].push_back(wAdj[j].second.first);
            reducedEdges[wAdj[j].second.second].push_back(wAdj[j].first);

            std::pair <int,int> temp;
            temp.first = wAdj[j].second.first;
            temp.second = wAdj[j].second.second;
            result.push_back(temp);
            if (unionF.connected(1,n)) {    
                break;
            }
        }
        //use priority queue for dijkstra and a helper to access the corresponding weight in the queue
        std::priority_queue< std::pair<int,int>, std::vector< std::pair<int,int> >, std::greater< std::pair<int,int> > > pq;
        std::vector < int > pqHelper (n+1);
        std::vector < int > pred (n+1); 
        int dijinf = 160000;
        pq.push(std::make_pair(0,1));
        pqHelper[1] = 0; 
        //important: really not sure about the bound of the loops from here on out
        for (int j = 2; j < reducedEdges.size(); j++){
            pq.push(std::make_pair(dijinf,j));
            pqHelper[j] = dijinf;
        } 

        while (!pq.empty()){
            std::pair <int, int> v = pq.top();
            pq.pop();
            //now I saw that pq has no delete operation. following lazy advice from StackOverflow with attempt of flow control
            //http://stackoverflow.com/questions/9209323/easiest-way-of-using-min-priority-queue-with-key-update-in-c
            if (v.first == dijinf ) break;
            for (int k = 0; k < reducedEdges[v.second].size(); k+=2){
                int alt = v.first + reducedEdges[v.second][k+1];
                if (alt < pqHelper[reducedEdges[v.second][k]]){
                    int neighbour = reducedEdges[v.second][k];
                    pqHelper[neighbour] = alt;
                    pred [neighbour] = v.second;
                    pq.push(std::make_pair(alt, neighbour));

                }
            }
        }

        int prev = n;
        std::stringstream resultStream;
        resultStream << n ;
        while (prev != 1){
            prev = pred[prev];
            resultStream << " " << prev;
        }
        std::string res = resultStream.str();
        std::reverse( res.begin(), res.end());

       
        std::cout << "Case #" << i <<": " << res <<  "\n";

    }
    return 0;
}
