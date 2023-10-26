/* Dijkstra's algorithm for finding shortest path between two nodes.
   This is taken from Fig 5-8 of Tanenbaum, Computer Networks, 6th Ed.
   Converted to C++ by ChatGPT 3.5.
   The global declarations are moved to dijkstra_defs.h.
 */

#include <vector>
using namespace std;

#include "dijkstra_defs.h"
#include "shortest_path.h"

struct State {
    int predecessor;    // previous node
    int length;         // length from source to this node
    enum { permanent, tentative } label; // label state
};

void shortest_path(int s, int t, vector<int>& path) {
    vector<State> state(MAX_NODES);
    for (State& s : state) {
        s.predecessor = -1;
        s.length = INFINITY;
        s.label = State::tentative;
    }

    state[t].length = 0;
    state[t].label = State::permanent;

    int k = t;
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
    } while (k != s);

    int i = 0;
    k = s;
    do {
        path[i++] = k;
        k = state[k].predecessor;
    } while (k >= 0);
}
