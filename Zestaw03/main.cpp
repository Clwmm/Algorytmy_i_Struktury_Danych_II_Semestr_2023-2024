// Mateusz Ka³wa

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class UndirectedGraphVector 
{
public:
    int numVertices;
    std::vector<std::unordered_set<int>> adjacencyList;

    UndirectedGraphVector(int vertices) : numVertices(vertices), adjacencyList(vertices) {}

    void addEdge(int vertex1, int vertex2) {
        adjacencyList[vertex1].insert(vertex2);
        adjacencyList[vertex2].insert(vertex1);
    }

    std::vector<int> getNeighbors(int vertex) {
        std::vector<int> neighbors(adjacencyList[vertex].begin(), adjacencyList[vertex].end());
        return neighbors;
    }

    int degree(int vertex) {
        return adjacencyList[vertex].size();
    }
};

class DirectedGraphVector 
{
public:
    int numVertices;
    std::vector<std::vector<int>> adjacencyMatrix;

    DirectedGraphVector(int vertices) : numVertices(vertices), adjacencyMatrix(vertices, std::vector<int>(vertices, 0)) {}

    void addEdge(int fromVertex, int toVertex) {
        adjacencyMatrix[fromVertex][toVertex] = 1;
    }

    int inDegree(int vertex) {
        int counter = 0;
        for (int i = 0; i < numVertices; i++) {
            if (adjacencyMatrix[i][vertex] == 1) {
                counter++;
            }
        }
        return counter;
    }

    int outDegree(int vertex) {
        int counter = 0;
        for (int i = 0; i < numVertices; i++) {
            if (adjacencyMatrix[vertex][i] == 1) {
                counter++;
            }
        }
        return counter;
    }

    std::vector<int> getNeighbors(int vertex) {
        std::vector<int> neighborsList;
        for (int i = 0; i < numVertices; i++) {
            if (adjacencyMatrix[vertex][i] == 1) {
                neighborsList.push_back(i);
            }
        }
        return neighborsList;
    }

    std::vector<int> getVerticesWithIncomingEdge(int vertex) {
        std::vector<int> verticesList;
        for (int i = 0; i < numVertices; i++) {
            if (adjacencyMatrix[i][vertex] == 1) {
                verticesList.push_back(i);
            }
        }
        return verticesList;
    }
};



class UndirectedGraphDictionary 
{
private:
    std::unordered_map<int, std::vector<int>> adjacencyList;

public:
    void addEdge(int vertex1, int vertex2) {
        adjacencyList[vertex1].push_back(vertex2);
        adjacencyList[vertex2].push_back(vertex1);
    }

    int degree(int vertex) {
        auto it = adjacencyList.find(vertex);
        if (it != adjacencyList.end()) {
            const auto& neighbors = it->second;
            return neighbors.size();
        }
        return 0; // Vertex not found
    }

    std::vector<int> getNeighbors(int vertex) {
        std::vector<int> neighborsList;
        auto it = adjacencyList.find(vertex);
        if (it != adjacencyList.end()) {
            const auto& neighbors = it->second;
            neighborsList.reserve(neighbors.size());
            for (int neighbor : neighbors) {
                neighborsList.push_back(neighbor);
            }
        }
        return neighborsList;
    }
};

class DirectedGraphDictionary 
{
private:
    std::unordered_map<int, std::vector<int>> adjacencyList;

public:
    void addEdge(int fromVertex, int toVertex) {
        adjacencyList[fromVertex].push_back(toVertex);
    }

    int inDegree(int vertex) {
        int counter = 0;
        for (const auto& pair : adjacencyList) {
            for (int neighbor : pair.second) {
                if (neighbor == vertex) {
                    counter++;
                    break;
                }
            }
        }
        return counter;
    }

    int outDegree(int vertex) {
        auto it = adjacencyList.find(vertex);
        if (it != adjacencyList.end()) {
            return it->second.size();
        }
        return 0;
    }

    std::vector<int> getOutNeighbors(int vertex) {
        auto it = adjacencyList.find(vertex);
        if (it != adjacencyList.end()) {
            return it->second;
        }
        return std::vector<int>();
    }

    std::vector<int> getInVertices(int vertex) {
        std::vector<int> inVerticesList;
        for (const auto& pair : adjacencyList) {
            for (int neighbor : pair.second) {
                if (neighbor == vertex) {
                    inVerticesList.push_back(pair.first);
                    break;
                }
            }
        }
        return inVerticesList;
    }
};


class UndirectedIncidenceMatrix 
{
private:
    int numVertices;
    int numEdges;
    std::vector<std::vector<int>> incidenceMatrix;

public:
    UndirectedIncidenceMatrix(int vertices, int edges) : numVertices(vertices), numEdges(edges) {
        incidenceMatrix.resize(numVertices, std::vector<int>(numEdges, 0));
    }

    void addEdge(int edgeIndex, int vertex1, int vertex2) {
        if (isValidIndex(edgeIndex, vertex1) && isValidIndex(edgeIndex, vertex2)) {
            incidenceMatrix[vertex1][edgeIndex] = 1;
            incidenceMatrix[vertex2][edgeIndex] = 1;
        }
        else {
            std::cout << "Invalid edge or vertex index!" << std::endl;
        }
    }

    void printDegree(int vertex) {
        if (isValidIndex(vertex)) {
            int degree = 0;
            for (int j = 0; j < numEdges; ++j) {
                if (incidenceMatrix[vertex][j] == 1)
                    degree++;
            }
            std::cout << "Degree of vertex " << vertex << ": " << degree << std::endl;
        }
        else {
            std::cout << "Invalid vertex index!" << std::endl;
        }
    }

    void printNeighbors(int vertex) {
        if (isValidIndex(vertex)) {
            std::cout << "Neighbors of vertex " << vertex << ": ";
            for (int i = 0; i < numVertices; ++i) {
                if (i != vertex && incidenceMatrix[vertex][i] == 1)
                    std::cout << i << " ";
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "Invalid vertex index!" << std::endl;
        }
    }

private:
    bool isValidIndex(int index) const {
        return index >= 0 && index < numVertices;
    }

    bool isValidIndex(int edgeIndex, int vertexIndex) const {
        return isValidIndex(edgeIndex) && isValidIndex(vertexIndex);
    }
};

class DirectedIncidenceMatrix 
{
private:
    int numVertices;
    int numEdges;
    std::vector<std::vector<int>> incidenceMatrix;

public:
    DirectedIncidenceMatrix(int vertices, int edges) : numVertices(vertices), numEdges(edges) {
        incidenceMatrix.resize(numVertices, std::vector<int>(numEdges, 0));
    }

    void addEdge(int edgeIndex, int fromVertex, int toVertex) {
        if (isValidEdgeIndex(edgeIndex) && isValidVertexIndex(fromVertex) && isValidVertexIndex(toVertex)) {
            incidenceMatrix[fromVertex][edgeIndex] = -1;
            incidenceMatrix[toVertex][edgeIndex] = 1;
        }
        else {
            std::cout << "Invalid edge or vertex index!" << std::endl;
        }
    }

    void printOutDegree(int vertex) {
        if (isValidVertexIndex(vertex)) {
            int outDegree = 0;
            for (int j = 0; j < numEdges; ++j) {
                if (incidenceMatrix[vertex][j] == 1)
                    outDegree++;
            }
            std::cout << "Out degree of vertex " << vertex << ": " << outDegree << std::endl;
        }
        else {
            std::cout << "Invalid vertex index!" << std::endl;
        }
    }

    void printInDegree(int vertex) {
        if (isValidVertexIndex(vertex)) {
            int inDegree = 0;
            for (int j = 0; j < numEdges; ++j) {
                if (incidenceMatrix[vertex][j] == -1)
                    inDegree++;
            }
            std::cout << "In degree of vertex " << vertex << ": " << inDegree << std::endl;
        }
        else {
            std::cout << "Invalid vertex index!" << std::endl;
        }
    }

    void printAdjacentVertices(int vertex) {
        if (isValidVertexIndex(vertex)) {
            std::cout << "Vertices adjacent to vertex " << vertex << ": ";
            for (int i = 0; i < numVertices; ++i) {
                if (i != vertex && (incidenceMatrix[vertex][i] == -1 || incidenceMatrix[vertex][i] == 1))
                    std::cout << i << " ";
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "Invalid vertex index!" << std::endl;
        }
    }

private:
    bool isValidEdgeIndex(int index) const {
        return index >= 0 && index < numEdges;
    }

    bool isValidVertexIndex(int index) const {
        return index >= 0 && index < numVertices;
    }
};


auto main() -> int 
{
    char graphType;
    int numVertices, numEdges;

    std::cout << "Is the graph directed? (y/n): ";
    std::cin >> graphType;

    std::cout << "Enter the number of vertices: ";
    std::cin >> numVertices;

    std::cout << "Enter the number of edges: ";
    std::cin >> numEdges;

    if (graphType == 'y' || graphType == 'Y') {
        DirectedGraphDictionary graphDict;
        DirectedGraphVector graphVec(numVertices);

        std::cout << "Enter pairs of vertices for edges:" << std::endl;
        for (int i = 0; i < numEdges; ++i) {
            int v, w;
            std::cin >> v >> w;
            graphDict.addEdge(v, w);
            graphVec.addEdge(v, w);
        }

        int vertexToCheck = 1;

        std::cout << "In-degree of vertex " << vertexToCheck << " (Dictionary): " << graphDict.inDegree(vertexToCheck) << std::endl;
        std::cout << "Out-degree of vertex " << vertexToCheck << " (Dictionary): " << graphDict.outDegree(vertexToCheck) << std::endl;
        std::cout << "Neighbors of vertex " << vertexToCheck << " (Dictionary): ";
        for (int neighbor : graphDict.getOutNeighbors(vertexToCheck)) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;

        std::cout << "In-degree of vertex " << vertexToCheck << " (Vector): " << graphVec.inDegree(vertexToCheck) << std::endl;
        std::cout << "Out-degree of vertex " << vertexToCheck << " (Vector): " << graphVec.outDegree(vertexToCheck) << std::endl;
        std::cout << "Neighbors of vertex " << vertexToCheck << " (Vector): ";
        for (int neighbor : graphVec.getNeighbors(vertexToCheck)) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
    else if (graphType == 'n' || graphType == 'N') {
        UndirectedGraphDictionary graphDict;
        UndirectedGraphVector graphVec(numVertices);

        std::cout << "Enter pairs of vertices for edges:" << std::endl;
        for (int i = 0; i < numEdges; ++i) {
            int v, w;
            std::cin >> v >> w;
            graphDict.addEdge(v, w);
            graphVec.addEdge(v, w);
        }

        int vertexToCheck = 1;

        std::cout << "Degree of vertex " << vertexToCheck << " (Dictionary): " << graphDict.degree(vertexToCheck) << std::endl;
        std::cout << "Neighbors of vertex " << vertexToCheck << " (Dictionary): ";
        for (int neighbor : graphDict.getNeighbors(vertexToCheck)) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;

        std::cout << "Degree of vertex " << vertexToCheck << " (Vector): " << graphVec.degree(vertexToCheck) << std::endl;
        std::cout << "Neighbors of vertex " << vertexToCheck << " (Vector): ";
        for (int neighbor : graphVec.getNeighbors(vertexToCheck)) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Invalid input for graph type. Please enter 'y' for directed or 'n' for undirected." << std::endl;
    }

    return 0;
}