#define MAX_NODES 26			/* maximum number of nodes */
#define INFINITY 1000000000		/* a number larger than every maximum path */


/* Shared variables */
SHARED int n, dist[MAX_NODES][MAX_NODES];	/* dist[i][j] is the distance from i to j */

SHARED int verbose;		/* control debug/informational output */

/* Macros to convert between char node name A - Z and node number 0 - 25 */

#define nodenum( nodename ) (nodename - 'A')

#define nodename( nodenum ) (nodenum + 'A')
