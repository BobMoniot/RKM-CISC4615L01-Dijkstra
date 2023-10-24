#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#define SHARED  /* empty here, extern in routines sharing global variables */

#include "dijkstra_defs.h"
#include "shortest_path.h"
#include "load_graph.h"




void Usage( char *myname )
{
    fprintf(stderr,"Usage: %s [-v] filename\n",myname);
    exit(1);
}

int main( int argc, char *argv[] )
{
    int iarg;
    char *filename;
    FILE *fd;

    char src, dst;
    int k, s, t;
    int path[MAX_NODES];

    verbose = 0;		/* Default is no debug output */
    filename = (char *) NULL;

    /* Collect arguments */
    if( argc < 2 || argc > 3 ) {
	Usage( argv[0] );
    }
    for( iarg = 1; iarg < argc; iarg++ ) {
	if( argv[iarg][0] == '-' ) {
	    if( strcmp(argv[iarg],"-v") == 0 )
		verbose = 1;
	    else
		Usage( argv[0] );
	}
	else {
	    filename = argv[iarg];
	}
    }
    
    if( filename == (char *) NULL ) {
	Usage( argv[0] );
    }

    fd = fopen( filename, "r" );
    if( fd == NULL ) {
	perror( filename );
	exit(errno);
    }

    
    load_graph( fd );

    if( verbose )
	print_graph();

    printf("Input source & destination nodes, separated by space, ^D to quit:\n");
    do {
	printf("? ");
	if( scanf(" %c %c",&src,&dst) != 2)
	    break;
	src = toupper( src ); /* be case insensitive */
	dst = toupper( dst );

	s = nodenum( src );
	t = nodenum( dst );

	if( t == s ) continue;
	if( s < 0 || s >= n || t < 0 || t >=n ) {
	    printf("%c %c not within graph\n",src,dst);
	    continue;
	}

	shortest_path(s,t,path);

	printf("Path from %c to %c: ",nodename(s),nodename(t));

	for( k = 0; ; k++ ) {
	    printf("%c ",nodename(path[k]));
	    if( path[k] == t ) break;
	}
	printf("\n");
    } while( 1 );
    printf("Bye\n");
    
    return 0;
}

