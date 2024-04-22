// Mateusz Kałwa

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
using namespace std;

class GraphMatrix {
private:
    vector<vector<int>> adjMatrix;
    bool directed;

public:
    GraphMatrix(int vertices, bool isDirected) : directed(isDirected) {
        adjMatrix.resize(vertices, vector<int>(vertices, 0));
    }

    void addEdge(int from, int to) {
        adjMatrix[from][to] = 1;
        if (!directed) {
            adjMatrix[to][from] = 1;
        }
    }

    vector<int> getNeighbors(int vertex) {
        vector<int> neighbors;
        for (int i = 0; i < adjMatrix.size(); ++i) {
            if (adjMatrix[vertex][i] == 1) {
                neighbors.push_back(i);
            }
        }
        return neighbors;
    }

    void printMatrix() {
        for (const auto& row : adjMatrix) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    }
    
    int inDegree(int vertex) {
        int count = 0;
        for (int i = 0; i < adjMatrix.size(); ++i) {
            if (adjMatrix[i][vertex] == 1) count++;
        }
        return count;
    }

    int outDegree(int vertex) {
        int count = 0;
        for (int val : adjMatrix[vertex]) {
            if (val == 1) count++;
        }
        return count;
    }

    vector<int> getInNeighbors(int vertex) {
        vector<int> inNeighbors;
        for (int i = 0; i < adjMatrix.size(); ++i) {
            if (adjMatrix[i][vertex] == 1) inNeighbors.push_back(i);
        }
        return inNeighbors;
    }

    // Metoda dla grafu nieskierowanego
    int degree(int vertex) {
        int count = 0;
        for (int val : adjMatrix[vertex]) {
            count += val;
        }
        return count;
    }
};

class GraphList {
private:
    unordered_map<int, list<int>> adjList;
    bool directed;

public:
    GraphList(bool isDirected) : directed(isDirected) {}

    void addEdge(int from, int to) {
        adjList[from].push_back(to);
        if (!directed) {
            adjList[to].push_back(from);
        }
    }

    list<int> getNeighbors(int vertex) {
        return adjList[vertex];
    }

    // Metody dla grafu skierowanego
    int inDegree(int vertex) {
        int count = 0;
        for (auto& pair : adjList) {
            for (int neigh : pair.second) {
                if (neigh == vertex) {
                    count++;
                }
            }
        }
        return count;
    }

    int outDegree(int vertex) {
        return adjList[vertex].size();
    }

    list<int> getInNeighbors(int vertex) {
        list<int> inNeighbors;
        for (auto& pair : adjList) {
            for (int neigh : pair.second) {
                if (neigh == vertex) {
                    inNeighbors.push_back(pair.first);
                }
            }
        }
        return inNeighbors;
    }

    // Metoda dla grafu nieskierowanego
    int degree(int vertex) {
        return adjList[vertex].size();
    }
};


int main() {
    // Przykład dla grafu skierowanego z wykorzystaniem macierzy sąsiedztwa
    cout << "Graf skierowany (macierz sasiedztwa):" << endl;
    GraphMatrix directedGraphMatrix(5, true);
    directedGraphMatrix.addEdge(0, 1);
    directedGraphMatrix.addEdge(1, 2);
    directedGraphMatrix.addEdge(2, 3);
    directedGraphMatrix.addEdge(3, 4);
    directedGraphMatrix.addEdge(4, 0);

    // Wyświetlenie macierzy sąsiedztwa
    directedGraphMatrix.printMatrix();

    // Stopień wchodzący i wychodzący dla wierzchołka 2
    cout << "Stopien wchodzacy wierzcholka 2: " << directedGraphMatrix.inDegree(2) << endl;
    cout << "Stopien wychodzacy wierzcholka 2: " << directedGraphMatrix.outDegree(2) << endl;

    // Przykład dla grafu nieskierowanego z wykorzystaniem listy sąsiedztwa
    cout << "\nGraf nieskierowany (lista sasiedztwa):" << endl;
    GraphList undirectedGraphList(false);
    undirectedGraphList.addEdge(0, 1);
    undirectedGraphList.addEdge(1, 2);
    undirectedGraphList.addEdge(2, 3);
    undirectedGraphList.addEdge(3, 4);
    undirectedGraphList.addEdge(4, 0);

    // Stopień wierzchołka 2
    cout << "Stopien wierzcholka 2: " << undirectedGraphList.degree(2) << endl;

    // Lista sąsiadów dla wierzchołka 2
    cout << "Sasiedzi wierzcholka 2: ";
    for (int neighbor : undirectedGraphList.getNeighbors(2)) {
        cout << neighbor << " ";
    }
    cout << endl;

    return 0;
}