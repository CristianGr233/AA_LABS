

#ifndef LAB3_5_MST_H
#define LAB3_5_MST_H

int k = 0;

void writeMSTToFile(vector<vector<int>> edges, const string& filename) {
    ofstream outfile("../MSTs/" + filename);
    if (!outfile.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

        int edgeCount = edges.size();

        bool directed = isDirected(edges);
        if (!directed) {
            edgeCount /= 2;
        }
        for (int i = 0; i < edgeCount; ++i) {
            int from = edges[i][0];
            int to = edges[i][1];
            int weight = edges[i][2];
            bool reverseExists = false;

            if (directed) {

                for (int j = 0; j < edgeCount; ++j) {
                    if (edges[j][0] == to && edges[j][1] == from) {
                        reverseExists = true;
                        break;
                    }
                }

                if (reverseExists) {
                    outfile << from << "<(" << weight << ")-" << to << endl;
                } else {
                    outfile << from << "-(" << weight << ")>" << to << endl;
                }
            } else {

                if (from < to) {
                    outfile << from << "-(" << weight << ")-" << to << endl;
                }
            }
        }

    outfile.close();
}







//! Kruskal
class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int find(int i) {
        return (parent[i] == i) ? i : (parent[i] = find(parent[i]));
    }

    void unite(int x, int y) {
        int s1 = find(x), s2 = find(y);
        if (s1 != s2) {
            if (rank[s1] < rank[s2]) parent[s1] = s2;
            else if (rank[s1] > rank[s2]) parent[s2] = s1;
            else parent[s2] = s1, rank[s1]++;
        }
    }
};
bool comparator(vector<int> &a,vector<int> &b){
    if(a[2]<=b[2])return true;
    return false;
}
void printMST(const vector<vector<int>> &mstEdges) {
    cout << endl << "Edge \tWeight\n";
    for (const auto &e : mstEdges) {
        cout << e[0] << " - " << e[1] << " \t" << e[2] << " \n";
    }
    cout<<endl;
}



vector<int> kruskalsMST(int V, vector<vector<int>> edges, int src) {
    sort(edges.begin(), edges.end(),comparator);
    DSU dsu(V);
    int cost = 0;
    vector<vector<int>> mstEdges;
    for (auto &e : edges) {
        int x = e[0], y = e[1], w = e[2];
        if (dsu.find(x) != dsu.find(y)) {
            dsu.unite(x, y);
            cost += w;
            mstEdges.push_back(e);
        }
        if (mstEdges.size() == V - 1) {
            break;
        }
    }
    string filename = "mst_edges" + to_string(k + 1) + ".txt";
    writeMSTToFile(mstEdges, filename);
    k++;
    if(show_results)
        printMST(mstEdges);


    return {cost};
}

//! Prim's

int minKey(vector<int> &key, vector<bool> &mstSet) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < mstSet.size(); v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}


void printMST(vector<int> &parent, vector<vector<int>> &graph) {
    cout << endl << "Edge \tWeight\n";
    for (int i = 1; i < graph.size(); i++)
        cout << parent[i] << " - " << i << " \t"
             << graph[parent[i]][i] << " \n";
    cout<<endl;
}


vector<int> primMST(int V, vector<vector<int>> graph, int src) {
    vector<int> parent(V);
    vector<int> key(V);
    vector<bool> mstSet(V);
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
    key[0] = 0;
    parent[0] = -1;
    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = true;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == false
                && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
    if(show_results)
        printMST(parent, graph);

    return {};
}




#endif //LAB3_5_MST_H
