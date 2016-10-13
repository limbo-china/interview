#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;
int	 connectedComponents(vector<vector<int> > &grid, int n);
void DFS(vector<vector<int> > &grid, vector<int> &nodes, int i, int n);

int connectedComponents(vector<vector<int> > &grid, int n){
    vector<int> nodes(n, 0);
    int num = 0;

    for (int i = 0; i < n; i++){
        if (nodes[i] == 0){
            num++;
            nodes[i] = 1;
            DFS(grid, nodes, i, n);
            cout << endl;
        }
    }

    return num;
}
void DFS(vector<vector<int> > &grid, vector<int> &nodes, int i, int n){
    cout << i << " ";
    for (int j = 0; j < n; j++){
        if ((i != j) && (nodes[j] == 0) && (grid[i][j] == 1)){
            nodes[j] = 1;
            DFS(grid, nodes, j, n);
        }
    }
}
int main(){
    const int N = 10;

    vector<vector<int> > grid(N, vector<int>(N));

    ifstream in("input.txt");
    int t;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            in >> t;
            grid[i][j] = t;
        }
    }

    in.close();
    cout << "number: " << connectedComponents(grid, N);
}
