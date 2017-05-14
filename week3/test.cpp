#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>


//Source: http://www.geeksforgeeks.org/bipartite-graph/
using namespace std;
 
 
// This function returns true if graph G[V][V] is Bipartite,
// else false
bool isBipartiteUtil(vector< vector<int> > G, int src, int colorArr[])
{
    colorArr[src] = 1;
 
    // Create a queue (FIFO) of vertex numbers and enqueue
    // source vertex for BFS traversal
    queue <int> q;
    q.push(src);
 
    // Run while there are vertices in queue (Similar to BFS)
    while (!q.empty())
    {
        // Dequeue a vertex from queue ( Refer http://goo.gl/35oz8 )
        int u = q.front();
        q.pop();
 
         // Find all non-colored adjacent vertices
        for (int v = 0; v < G.size(); ++v)
        {
            // An edge from u to v exists and
            // destination v is not colored
            if (G[u][v] && colorArr[v] == -1)
            {
                // Assign alternate color to this
                // adjacent v of u
                colorArr[v] = 1 - colorArr[u];
                q.push(v);
            }
 
            // An edge from u to v exists and destination
            // v is colored with same color as u
            else if (G[u][v] && colorArr[v] == colorArr[u])
                return false;
        }
    }
 
    // If we reach here, then all adjacent vertices can
    // be colored with alternate color
    return true;
}
 
// Returns true if G[][] is Bipartite, else false
bool isBipartite(vector< vector<int> > G)
{
    // Create a color array to store colors assigned to all
    // veritces. Vertex/ number is used as index in this
    // array. The value '-1' of  colorArr[i] is used to
    // ndicate that no color is assigned to vertex 'i'.
    // The value 1 is used to indicate first color is
    // assigned and value 0 indicates second color is
    // assigned.
    int colorArr[G.size()];
    for (int i = 0; i < G.size(); ++i)
        colorArr[i] = -1;
 
    // This code is to handle disconnected graoh
    for (int i = 0; i < G.size(); i++)
      if (colorArr[i] == -1)
        if (isBipartiteUtil(G, i, colorArr) == false)
           return false;
 
     return true;
}

int main (){
    
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, m;
        cin >> n >> m;
        vector< vector<int> > matrixG (n, vector<int>(n));
        for (int j = 1; j <= m; j++) {
            int a, b;
            cin >> a >> b;
            matrixG[a-1][b-1] = 1;
            matrixG[b-1][a-1] = 1;
        }

        string result;
        isBipartite(matrixG) ? result = "yes" : result = "no";

        cout << "Case #" << i << ": " << result << "\n";

    }
    return 0;
}