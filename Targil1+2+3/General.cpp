#include <iostream>
#include <list>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <unistd.h> // for getopt

using namespace std;

/**
 * Euler algorithem based on
 * @SOURCE: https://www.geeksforgeeks.org/eulerian-path-and-circuit/
*/
// A class that represents an undirected graph
class Graph
{
    int V; // Number of vertices
    list<int> *adj; // A dynamic array of adjacency lists
public:
    // Constructor and destructor
    Graph(int V) { this->V = V; adj = new list<int>[V]; }
    ~Graph() { delete[] adj; } // To avoid memory leak

    // function to add an edge to graph
    void addEdge(int v, int w);

    // Method to check if this graph is Eulerian or not
    int isEulerian();

    // Method to check if all non-zero degree vertices are connected
    bool isConnected();

    // Function to do DFS starting from v. Used in isConnected();
    void DFSUtil(int v, bool visited[]);
};

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

// Method to check if all non-zero degree vertices are connected.
// It mainly does DFS traversal starting from
bool Graph::isConnected()
{
    // Mark all the vertices as not visited
    bool visited[V];
    int i;
    for (i = 0; i < V; i++)
        visited[i] = false;

    // Find a vertex with non-zero degree
    for (i = 0; i < V; i++)
        if (!adj[i].empty())
            break;

    // If there are no edges in the graph, return true
    if (i == V)
        return true;

    // Start DFS traversal from a vertex with non-zero degree
    DFSUtil(i, visited);

    // Check if all non-zero degree vertices are visited
    for (i = 0; i < V; i++)
        if (!visited[i] && !adj[i].empty())
            return false;

    return true;
}

/* The function returns one of the following values
0 --> If graph is not Eulerian
1 --> If graph has an Euler path (Semi-Eulerian)
2 --> If graph has an Euler Circuit (Eulerian) */
int Graph::isEulerian()
{
    // Check if all non-zero degree vertices are connected
    if (isConnected() == false)
        return 0;

    // Count vertices with odd degree
    int odd = 0;
    for (int i = 0; i < V; i++)
        if (adj[i].size() & 1)
            odd++;

    // If count is more than 2, then graph is not Eulerian
    if (odd > 2)
        return 0;

    // If odd count is 2, then semi-eulerian.
    // If odd count is 0, then eulerian
    // Note that odd count can never be 1 for undirected graph
    return (odd) ? 1 : 2;
}

// Function to print the result of Eulerian check
void printEulerianResult(Graph &g) {
    int res = g.isEulerian();
    if (res == 0)
        cout << "Graph is not Eulerian\n";
    else if (res == 1)
        cout << "Graph has an Euler path\n";
    else
        cout << "Graph has an Eulerian circuit\n";
}

// Function to generate a random graph
void generateRandomGraph(Graph &g, int V, int E, unsigned int seed) {
    srand(seed);
    for (int i = 0; i < E; ++i) {
        int v = rand() % V;
        int w = rand() % V;
        g.addEdge(v, w);
    }
}

// Driver program to test above function based on command line input
int main(int argc, char *argv[])
{
    int V = 0, E = 0;
    unsigned int seed;

    int opt;
    while ((opt = getopt(argc, argv, "v:e:s:")) != -1) {
        switch (opt) {
        case 'v':
            V = atoi(optarg);
            break;
        case 'e':
            E = atoi(optarg);
            break;
        case 's':
            seed = atoi(optarg);
            break;
        default:
            cerr << "Usage: " << argv[0] << " -v num_vertices -e num_edges [-s seed]\n";
            exit(EXIT_FAILURE);
        }
    }

    if (V <= 0 || E < 0) {
        cerr << "Invalid number of vertices or edges specified.\n";
        exit(EXIT_FAILURE);
    }

    Graph g(V);
    generateRandomGraph(g, V, E, seed);
    printEulerianResult(g);

    return 0;
}
