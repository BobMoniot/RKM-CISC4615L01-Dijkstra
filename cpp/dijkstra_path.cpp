#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <vector>

using namespace std;

#define MAIN			// home for shared variables
#include "dijkstra_defs.h"
#include "shortest_path.h"
#include "load_graph.h"

// Routines to convert between external alphabetic names and internal numbers

inline int nodenum(char nodename) {
    return nodename - 'A';
}

inline char nodename(int nodenum) {
    return nodenum + 'A';
}

void Usage(const char* myname) {
    cerr << "Usage: " << myname << " [-v] filename" << endl;
    exit(1);
}

int main(int argc, char* argv[]) {
    int iarg;
    const char* filename;
    ifstream file;

    char src, dst;
    int k, s, t;
    vector<int> path(MAX_NODES);

    verbose = 0;		// Default is no debug output
    filename = nullptr;

    // Collect arguments [-v] filename
    if (argc < 2 || argc > 3) {
        Usage(argv[0]);
    }

    for (iarg = 1; iarg < argc; iarg++) {
        if (argv[iarg][0] == '-') {
            if (strcmp(argv[iarg], "-v") == 0)
                verbose = 1;
            else
                Usage(argv[0]);
        }
        else {
            filename = argv[iarg];
        }
    }

    if (filename == nullptr) {
        Usage(argv[0]);
    }

    file.open(filename);
    if (!file) {
        perror(filename);
        exit(errno);
    }

    load_graph(file);

    if (verbose)
        print_graph();

    cout << "Input source & destination nodes, separated by space, Ctrl+D to quit:" << endl;

    do {
        cout << "? ";
        if (!(cin >> src >> dst))
            break;
        src = toupper(src);	// be case insensitive
        dst = toupper(dst);

        s = nodenum(src);
        t = nodenum(dst);

        if (t == s) continue;
        if (s < 0 || s >= n || t < 0 || t >= n) {
            cout << src << " " << dst << " not within the graph" << endl;
            continue;
        }

        shortest_path(s, t, path);

        cout << "Path from " << nodename(s) << " to " << nodename(t) << ": ";
        for (k = 0; ; k++) {
            cout << nodename(path[k]) << " ";
            if (path[k] == t) break;
        }
        cout << endl;
    } while (true);

    cout << "Bye" << endl;

    return 0;
}
