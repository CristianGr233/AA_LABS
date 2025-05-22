
#ifndef LAB3_5_SHORTESTPATH_H
#define LAB3_5_SHORTESTPATH_H

//! Dijkstras



vector<vector<vector<int>>> constructAdj(vector<vector<int>> &edges, int V){
    vector<vector<vector<int>>> adj(V);
    bool dir = isDirected(edges);
    for (const auto &edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int wt = edge[2];
        adj[u].push_back({v, wt});
        if(!dir)
            adj[v].push_back({u, wt});
    }
    return adj;
}
vector<int> Dijkstras(int V, vector<vector<int>> edges, int src) {
    vector<vector<vector<int>>> adj = constructAdj(edges, V);

    set<pair<int, int>> st;
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    st.insert({0, src});
    while (!st.empty()) {
        auto it = *(st.begin());
        int u = it.second;
        st.erase(it);
        for (auto x : adj[u]) {
            int v = x[0];
            int weight = x[1];
            if (dist[v] > dist[u] + weight) {
                if (dist[v] != INT_MAX) {
                    st.erase({dist[v], v});
                }
                dist[v] = dist[u] + weight;
                st.insert({dist[v], v});
            }
        }
    }
    return dist;
}

//!FloydWarshall


vector<int> floydWarshall(int V, vector<vector<int>> dist, int source) {
    int INF = 100000000;
    for(int i = 0 ;i < V; i++)
        for(int j = 0 ; j<V; j++)
            if(i != j && dist[i][j] == 0)
                dist[i][j] = INF;

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if(dist[i][k] != 1e8 && dist[k][j]!= 1e8)
                    dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);
            }
        }
    }
    return dist[source];
}







#endif //LAB3_5_SHORTESTPATH_H
