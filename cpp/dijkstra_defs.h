// dijkstra_defs.h

const int MAX_NODES = 26;
const int INFINITY = 1000000000;

#ifndef MAIN
extern		// all non-main routines declare, main defines shared variables
#endif
int n,				// n=number of nodes
    verbose;		        // controls amount of extra output

#ifndef MAIN
extern		// all non-main routines declare, main defines shared variables
#endif
vector< vector<int> > dist     // dist[i][j] is the distance from i to j
#ifdef MAIN
(MAX_NODES, vector<int>(MAX_NODES, 0))
#endif
;


// Routines to convert between external alphabetic names and internal numbers

inline int nodenum(char nodename) {
    return nodename - 'A';
}

inline char nodename(int nodenum) {
    return nodenum + 'A';
}
