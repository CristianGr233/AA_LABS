

#ifndef LAB3_5_GRAPHTRAVERSAL_H
#define LAB3_5_GRAPHTRAVERSAL_H


//!BFS
vector<int> bfs(int V, vector<vector<int>> adj, int src)  {

    int s = 0;
    vector<int> res;
    queue<int> q;
    vector<bool> visited(V, false);
    visited[s] = true;
    q.push(s);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        res.push_back(curr);
        for (int x : adj[curr]) {
            if (!visited[x]) {
                visited[x] = true;
                q.push(x);
            }
        }
    }
    return res;
}

//!DFS

void dfsRec(vector<vector<int>> &adj, vector<bool> &visited, int s, vector<int> &res)
{
    visited[s] = true;
    res.push_back(s);
    for (int i : adj[s])
        if (visited[i] == false)
            dfsRec(adj, visited, i, res);
}


vector<int> DFS(int V, vector<vector<int>> adj, int src)
{
    vector<bool> visited(adj.size(), false);
    vector<int> res;
    dfsRec(adj, visited, 0, res);
    return res;
}





#endif //LAB3_5_GRAPHTRAVERSAL_H
