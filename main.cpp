#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

void simpleMenu() {
    cout << "Input number:\n";
    cout << "   0: Exit\n";
    cout << "   1: Calculate for input1.txt \n";
    cout << "   2: Input graph from console\n";
}


class Graph {
    vector<vector<int>> g, gr;
    vector<int> visited, order;


    void dfs1(int v) {
        visited[v] = 1;
        for (int to: gr[v])
            if (!visited[to])
                dfs1(to);
        order.push_back(v);
    }

    void dfs2(int v, int component) {
        visited[v] = component;
        for (int to: g[v])
            if (!visited[to])
                dfs2(to, component);

    }

public:
    int sccCount;

    Graph(int vertexCount) {
        g.resize(vertexCount);
        gr.resize(vertexCount);

    }

    void addEdge(int a, int b) {
        g[a].push_back(b);
        gr[b].push_back(a);
    }

    vector<int> findScc() {
        visited.assign(g.size(), 0);
        for (int v = 0; v < g.size(); v++)
            if (!visited[v])
                dfs1(v);
        reverse(order.begin(), order.end());

        visited.assign(g.size(), 0);
        int sccCount = 0;
        for (int v: order)
            if (!visited[v])
                dfs2(v, ++sccCount);
        Graph::sccCount = sccCount;

        return visited;
    }
};

void txtInput() {
    ifstream fin;
    fin.open("input1.txt");
    cout << "Input count of vertex and edge by SPACE: " << endl;
    int vertexCount, edgeCount;
    fin >> vertexCount >> edgeCount;

    Graph graph(vertexCount);

    for (int i = 0; i < edgeCount; i++) {
        int a, b;
        fin >> a >> b;
        graph.addEdge(a - 1, b - 1);
    }

    vector<int> scc = graph.findScc();
    cout << "Number of Vertex:                   ";
    for (int i = 0; i < scc.size(); ++i) cout << i + 1 << " ";
    cout << endl;
    cout << "Number of component for each vertex:";
    for (int color: scc)
        cout << color << " ";
    cout << "\n";
    cout << "Count of SCC: " << graph.sccCount << endl;
    system("pause");
    fin.close();

}

void consoleInput() {
    cout << "Input count of vertex and edge by SPACE: " << endl;
    int vertexCount, edgeCount;
    cin >> vertexCount >> edgeCount;

    Graph graph(vertexCount);

    for (int i = 0; i < edgeCount; i++) {
        int a, b;
        cin >> a >> b;
        graph.addEdge(a - 1, b - 1);
    }

    vector<int> scc = graph.findScc();
    cout << "Number of Vertex:                   ";
    for (int i = 0; i < scc.size(); ++i) cout << i + 1 << " ";
    cout << endl;
    cout << "Number of component for each vertex:";
    for (int color: scc)
        cout << color << " ";
    cout << "\n";
    cout << "Count of SCC: " << graph.sccCount << endl;


}

int main() {

    int k = 1;
    do {
        system("cls");
        simpleMenu();
        cin >> k;
        //system("cls");
        if (k == 1) {
            txtInput();
        } else if (k == 2) {
            consoleInput();
            system("pause");
        }
    } while (k);


    return 0;
}
