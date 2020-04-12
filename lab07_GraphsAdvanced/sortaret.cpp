#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <list>
#include <vector>

#define MAX_NODES 50010
  
using namespace std;

void addEdge(vector<int> lg[], int u, int v) { 
    lg[u].push_back(v);
} 

void dfs(vector<int> lg[], int node, int N, int *visited, stack<int> *st) {
    visited[node] = 1;

    for (auto x : lg[node]) {
        if (visited[x] == 0) {
            dfs(lg, x, N, visited, st);
        }
    }

    (*st).push(node);
}
  
void topo_sort(vector<int> lg[], int N, int *visited, ofstream& out) {
    stack<int> st;

    for(int i = 1; i <= N; ++i) {
        if (visited[i] == 0) {
            dfs(lg, i, N, visited, &st);
        }
    }

    while (!st.empty()) { 
        out << st.top() << ' '; 
        st.pop(); 
    }
}

int main() { 
    ifstream in("sortaret.in");
    ofstream out("sortaret.out");

    int N, M;
    int sur, des;

    in >> N >> M;

    vector<int> lg[N+1];
    int visited[N+1] = {0};

    for (int i = 0; i < M; ++i) {
        in >> sur >> des;
        addEdge(lg, sur, des);
    }

    topo_sort(lg, N, visited, out);
 
    in.close();
    out.close();
  
    return 0; 
}