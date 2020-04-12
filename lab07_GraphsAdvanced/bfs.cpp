#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <queue>
#include <list>
#include <vector>

#define MAX_NODES 100010
  
using namespace std;

void addEdge(vector<int> lg[], int u, int v) { 
    lg[u].push_back(v);  
}

void bfs_graph(vector<int> lg[], int nodes, int sursa, int *visited, int *d) {
    queue <int> q;
    int i, node2;

    /* initializare */
    for (i = 1; i <= nodes; ++i) {
        visited[i] = 0;
        d[i] = -1;
    }

    visited[sursa] = 1;
    d[sursa] = 0;
    q.push(sursa);

    while (!q.empty()) {
        node2 = q.front();
        q.pop();

        for (auto x : lg[node2]) {
           if (visited[x] == 0) {
               visited[x] = 1;
               d[x] = d[node2] + 1;
               q.push(x);
           }
        }
    }
}
  
int main() { 
    ifstream in("bfs.in");
    ofstream out("bfs.out");

    int N, M, S;
    int sur, des;

    in >> N >> M >> S;

    vector<int> lg[N+1];
    int visited[N+1], d[N+1];

    for (int i = 0; i < M; ++i) {
        in >> sur >> des;
        addEdge(lg, sur, des);
    }
 
    bfs_graph(lg, N, S, visited, d);

    for (int i = 1; i <= N; ++i) {
        out << d[i] << ' ';
    }

    in.close();
    out.close();
  
    return 0; 
} 