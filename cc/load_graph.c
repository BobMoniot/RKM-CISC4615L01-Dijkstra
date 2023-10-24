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

#include <stdio.h>
#include <stdlib.h>

/* Shared global variables: n, dist[][] */
#define SHARED extern
#include "dijkstra_defs.h"
#include "load_graph.h"

void load_graph( FILE *fd )
{
    int d, j, k;
    char node1, node2;

    fscanf(fd,"%d",&n);

    /* Initialize graph with no connections between nodes */
    for (k = 0; k < n; k++) {
	for (j = 0; j < n; j++) { 
	    dist[j][k] = INFINITY;
	}
    }
    /* Except each node has distance 0 to itself */
    for (k = 0; k < n; k++) {
	dist[k][k] = 0;
    }
    
    while( fscanf(fd," %c %c %d",&node1,&node2,&d) == 3 ) {

	j = nodenum(node1);
	k = nodenum(node2);

	if( j < 0 || j >= n || k < 0 || k >= n ) {
	    fprintf(stderr,"Error: %c %c not within graph\n",node1,node2);
	    exit(1);
	}

	dist[j][k] = dist[k][j] = d;
    }
}

void print_graph( void )
{
    int j, k;
    printf("distance matrix:\n");
    printf("%6s","");
    for ( j = 0; j < n; j++ ) printf("%4c ",nodename(j));
    printf("\n");
    for (k = 0; k < n; k++) {
	printf(" %3c: ",nodename(k));
	for (j = 0; j < n; j++) {
	    if( dist[j][k] == INFINITY )
		printf("%4s ","--");
	    else
		printf("%4d ",dist[j][k]);
	}
	printf("\n");
    }
}
