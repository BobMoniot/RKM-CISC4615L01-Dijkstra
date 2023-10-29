#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <vector>

using namespace std;

#define MAIN			// home for shared variables

#include "dijkstra_defs.h"
#include "find_routes.h"
#include "load_graph.h"

void Usage( char *myname )
{
    cerr << "Usage: " << myname << " [-v] filename" << endl;
    exit(1);
}

int main( int argc, char *argv[] )
{
    int iarg;
    const char *filename;
    ifstream file;

    char src;
    int k, s;
    vector<Route> route_table(MAX_NODES);

    verbose = 0;		/* Default is no debug output */
    filename = nullptr;

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
    
    if( filename == nullptr ) {
	Usage( argv[0] );
    }

    file.open(filename);
    if (!file) {
        perror(filename);
        exit(errno);
    }

    load_graph( file );

    if( verbose )
	print_graph();

    cout << "Input routing host, ^D to quit:\n";

    do {
	cout << "? ";
	if( !(cin >> src) )
	    break;
	src = toupper( src );  /* be case insensitive */
	s = nodenum( src );
	
	find_routes( s, route_table );

	cout << "Routing table for " << nodename(s) << endl;
	print_route_table( n, route_table );
	
    } while( 1 );

    cout << "Bye" << endl;

    return 0;
}

