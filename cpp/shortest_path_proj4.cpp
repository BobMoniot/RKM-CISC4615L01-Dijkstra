/* Dijkstra's algorithm for finding shortest path between two nodes.
   This is taken from Fig 5-8 of Tanenbaum, Computer Networks, 6th Ed.
   Converted to C++ by ChatGPT 3.5.
   The global declarations are moved to dijkstra_defs.h.

   This version is modified to do a complete exploration of the
   network graph, rather than stopping when the endpoint of the path
   is reached.

   This version includes printing of state table.
 */


#include <iostream>
#include <iomanip>

#include <vector>
using namespace std;

#include "dijkstra_defs.h"
#include "shortest_path.h"

struct State {
    int predecessor;    // previous node
    int length;         // length from source to this node
    enum { permanent, tentative } label; // label state
};

void print_state_table( vector<State> state );

void shortest_path(int s, int t, vector<int>& path) {
    vector<State> state(MAX_NODES);
    for (int i = 0; i < n; i++) {
        state[i].predecessor = -1;
        state[i].length = INFINITY;
        state[i].label = State::tentative;
    }

    state[t].length = 0;
    state[t].label = State::permanent;

    int k = t;
    int ntentative = n;		// count of tentative nodes for termination
    
    do {
        for (int i = 0; i < n; i++) {
            if (dist[k][i] != 0 && state[i].label == State::tentative) {
                if (state[k].length + dist[k][i] < state[i].length) {
                    state[i].predecessor = k;
                    state[i].length = state[k].length + dist[k][i];
                }
            }
        }

        k = 0;
        int min = INFINITY;
        for (int i = 0; i < n; i++) {
            if (state[i].label == State::tentative && state[i].length < min) {
                min = state[i].length;
                k = i;
            }
        }

        state[k].label = State::permanent;
	//	print_state_table(state);
    } while (--ntentative > 0);


    if( verbose ) print_state_table( state );
    
    int i = 0;
    k = s;
    do {
        path[i++] = k;
        k = state[k].predecessor;
    } while (k >= 0);
}

// Routine to print the state table.  The special length INFINITY is
// printed as INF.  The label is printed as p for permanent or t for tentative.
// Format is node(dist,predecessor,label)

void print_state_table( vector<State>state )
{
    int i;

    printf("State array:\n");
    for (i = 0; i < n; i++ ) {
	cout <<
	    nodename(i) << "(";
	if( state[i].length == INFINITY )
	    cout << "INF";
	else
	    cout << state[i].length;
	cout << "," <<
	    nodename(state[i].predecessor) << ",";
	switch( state[i].label ) {
	    case State::permanent:
	    cout << "p";
	    break;
	    case State::tentative:
	    cout << "t";
	    break;
	}
	cout << ")" << endl;
    }
}

