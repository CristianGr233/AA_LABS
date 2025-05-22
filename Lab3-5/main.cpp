#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <climits>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <map>
#include <fstream>

using namespace std;
using namespace std::chrono;


bool show_results = 1;


bool isDirected(const vector<vector<int>>& adjList) {
    for (int u = 0; u < adjList.size(); ++u) {
        if (u >= adjList.size()) continue;

        for (int v : adjList[u]) {
            if (v >= adjList.size()) continue;

            bool reverseEdgeExists = false;
            for (int neighbor : adjList[v]) {
                if (neighbor == u) {
                    reverseEdgeExists = true;
                    break;
                }
            }


            if (!reverseEdgeExists) {
                return true;
            }
        }
    }
    return false;
}





#include "GraphTraversal.h"
#include "MST.h"
#include "ShortestPath.h"

struct input{
    int V;
    vector<vector<int>> adj_list;
    bool is_directed;
};

#include "input.h"
#include "w_input.h"
#include "w_input_sp.h"


vector<vector<int>> toWAdjMatrix(int V, vector<vector<int>> adjList, bool is_directed)
{

    vector<vector<int>> matrix(V, vector<int>(V, 0));;
    for(auto edge : adjList)
    {
        matrix[edge[0]][edge[1]] = edge[2];
        if(!is_directed)
            matrix[edge[1]][edge[0]] = edge[2];
    }
    return matrix;
}
vector<vector<int>> toAdjMatrix(int V, vector<vector<int>> adjList, bool is_directed)
{

    vector<vector<int>> matrix(V, vector<int>(V, 0));;
    for(int i = 0 ; i<adjList.size();i++)
    {
        for(int j=0; j<adjList[i].size();j++)
        {
            matrix[i][adjList[i][j]] = 1;
            if(!is_directed)
                matrix[adjList[i][j]][i] = 1;
        }


    }
    return matrix;
}

int countEdges(const vector<vector<int>> adjacencyList, bool isDirected) {
    int edgeCount = 0;

    for (int i = 0; i < adjacencyList.size(); ++i) {
        edgeCount += adjacencyList[i].size();
    }

    if (!isDirected) {
        edgeCount /= 2;
    }

    return edgeCount;
}

void printGraphData(input list, string method_name)
{
    cout<<endl;
    cout<<"Vertices: "<<list.V;
    cout<<" Edges: ";
    if(method_name == "Breadth-First Search" || method_name == "Depth-First Search")
        cout<<countEdges(list.adj_list, list.is_directed);
    else
        cout<<list.adj_list.size();
    cout<<" Directed: ";
    if(list.is_directed)
        cout<<"yes";
    else
        cout<<"no";
    cout<<"\t";
}


void GetDuration(input array, vector<int> (*function)(int, vector<vector<int>>, int), string name)
{
    auto start = high_resolution_clock::now();
    vector<int> output = function(array.V, array.adj_list, 0);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    float n_duration = duration.count();



    string unit = "ms";

    n_duration/=1000;
    if(n_duration > 1000)
    {
        n_duration/=1000;
        unit = "s";
    }
    if(show_results && output.size()>1)
    {
        cout<<endl<<"Result: ";
        for(auto vertex : output)
            cout<< vertex << " ";
        cout<<endl;
    }

    cout<<(float)n_duration<<" "<<unit<<" ";
}

void Time(vector<input> arrays, vector<vector<int> (*)(int,vector<vector<int>>, int)> methods, vector<string> names)
{
    for(int k=0;k<methods.size();k++){
        string name = names[k];

        cout<<name<<endl;
        for(int i=0;i<arrays.size();i++)
        {
            printGraphData(arrays[i], name);

            vector<vector<int>> array = arrays[i].adj_list;
            if(name == "Prim's" )
                array = toWAdjMatrix(arrays[i].V, array, arrays[i].is_directed);
            if(name == "FloydWarshall")
            {
                array = toWAdjMatrix(arrays[i].V, array, arrays[i].is_directed);

            }
            GetDuration({arrays[i].V, array, arrays[i].is_directed}, methods[k], names[k]);
            cout<<"  ";
        }
        cout<<endl<<endl;
    }
}

void writeGraphToFile(const input& graph, const string& filename, bool isweighted) {
    ofstream outfile("../input_graphs/" + filename);
    if (!outfile.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    if (isweighted) {

        vector<vector<int>> edges = graph.adj_list;
        int edgeCount = edges.size();
        bool directed = graph.is_directed;
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
    } else {

        set<pair<int, int>> printedEdges;

        for (int u = 0; u < graph.V; ++u) {
            for (int v : graph.adj_list[u]) {
                if (graph.is_directed) {

                    outfile << u << ">" << v << endl;
                } else {

                    if (printedEdges.count({v, u}) == 0) {
                        outfile << u << "-" << v << endl;
                        printedEdges.insert({u, v});
                    }
                }
            }
        }
    }

    outfile.close();
    //cout << "Graph edges written to " << filename << endl;
}







int main()
{
    vector<vector<int> (*)(int,vector<vector<int>>, int)> gt_methods;
    vector<vector<int> (*)(int,vector<vector<int>>, int)> mst_methods;
    vector<vector<int> (*)(int,vector<vector<int>>, int)> sp_methods;

    gt_methods.push_back(bfs);
    gt_methods.push_back(DFS);
    mst_methods.push_back(kruskalsMST);
    mst_methods.push_back(primMST);
    sp_methods.push_back(Dijkstras);
    sp_methods.push_back(floydWarshall);

    vector<string> gt_methods_names = {
            "Breadth-First Search",
             "Depth-First Search"
    };
    vector<string> mst_methods_names={
            "Kruskal's",
            "Prim's"
    };
    vector<string> sp_methods_names = {
            "Dijkstras",
            "FloydWarshall"
    };


    vector<input> input_traversal = {
            list1, list2, list3, list4, list5, list6, list7, list8};
    for (int i = 0; i < input_traversal.size(); ++i) {
        string filename = "graph_edges_" + to_string(i + 1) + ".txt";
        writeGraphToFile(input_traversal[i], filename, 0);
    }

    vector<input> input_mst = {
             w_list1, w_list2, w_list3, w_list4, w_list5,  w_list6, w_list7
    };


    vector<input> input_sp = {w_list6, w_list7, w_list8, w_list9, w_list10, w_list11, w_list12};

    vector<input> input_w={
            w_list1, w_list2, w_list3, w_list4, w_list5, w_list6, w_list7, w_list8, w_list9, w_list10,
            w_list11, w_list12
    };

    for (int i = 0; i < input_w.size(); ++i) {
        string filename = "graph_w_edges_" + to_string(i + 1) + ".txt";
        writeGraphToFile(input_w[i], filename, 1);
    }

    Time(input_traversal, gt_methods, gt_methods_names);
    Time(input_mst, mst_methods, mst_methods_names);
    Time(input_sp, sp_methods, sp_methods_names);


    return 0;
}