#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#define SHARED  /* empty here, extern in routines sharing global variables */

#include "dijkstra_defs.h"
#include "find_routes.h"
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

    char src;
    int k, s;
    route_entry route_table[MAX_NODES];

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

    printf("Input routing host, ^D to quit:\n");

    do {
	printf("? ");
	if( scanf(" %c",&src ) != 1 )
	    break;
	src = toupper( src );  /* be case insensitive */
	s = nodenum( src );
	
	find_routes( s, route_table );

	printf("Routing table for %c:\n",nodename(s));
	print_route_table( n, route_table );
	
    } while( 1 );
    printf("Bye\n");

    return 0;
}

