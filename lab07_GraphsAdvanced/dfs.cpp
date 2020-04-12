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
    lg[v].push_back(u);
} 

void dfs(vector<int> lg[], int node, int *visited) {
    visited[node] = 1;
    
    for (auto x : lg[node]) {
        if (visited[x] == 0) {
            dfs(lg, x, visited);
        }
    }
}

void connected_components(vector<int> lg[], int N, int *visited, int *components) {
    for (int i = 1; i <= N; ++i) {
        if (visited[i] == 0) {
            (*components)++;
            dfs(lg, i, visited);
        }
    }
}
  
int main() { 
    ifstream in("dfs.in");
    ofstream out("dfs.out");

    int N, M;
    int sur, des, components = 0;

    in >> N >> M;

    vector<int> lg[N+1];
    int visited[N+1] = {0};

    for (int i = 0; i < M; ++i) {
        in >> sur >> des;
        addEdge(lg, sur, des);
    }

    connected_components(lg, N, visited, &components);

    out << components;

    in.close();
    out.close();
  
    return 0; 
}