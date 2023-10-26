/* load_graph reads input specifying the distance graph, and fills the distance matrix.
   print_graph prints the distance matrix.
 */

/* Format of input:

   First line, decimal number of nodes in graph
   Subsequent lines, two letters (names of nodes A thru Z) then distance

   Distance matrix is assumed symmetric, so each pair of nodes need only
   be given once, in either order.  If the pair appears more than once,
   the last spec will be used.
*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// Shared global variables: n, dist[][]
#include "dijkstra_defs.h"
#include "load_graph.h"

void load_graph(ifstream& file) {
    int d, j, k;
    char node1, node2;

    file >> n;

    // Initialize graph with no connections between nodes
    for (k = 0; k < n; k++) {
        for (j = 0; j < n; j++) {
            dist[j][k] = INFINITY;
        }
    }
    // Except each node has distance 0 to itself
    for (k = 0; k < n; k++) {
        dist[k][k] = 0;
    }

    while (file >> node1 >> node2 >> d) {
        j = nodenum(node1);
        k = nodenum(node2);

        if (j < 0 || j >= n || k < 0 || k >= n) {
            cerr << "Error: " << node1 << " " << node2 << " not within the graph" << endl;
            exit(1);
        }

        dist[j][k] = dist[k][j] = d;
    }
}

void print_graph() {
    cout << "distance matrix:" << endl;
    cout << setw(5) << "";
    for (int j = 0; j < n; j++) {
        cout << setw(4) << nodename(j) << " ";
    }
    cout << endl;

    for (int k = 0; k < n; k++) {
        cout << setw(3) << nodename(k) << ": ";
        for (int j = 0; j < n; j++) {
            if (dist[j][k] == INFINITY)
                cout << setw(4) << "--" << " ";
            else
                cout << setw(4) << dist[j][k] << " ";
        }
        cout << endl;
    }
}
