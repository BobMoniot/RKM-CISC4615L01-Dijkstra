// find_routes.h

struct Route {
    int dest, link;		/* Destination and link used to get there */
    int length;			/* Length of path to dest */
};



void find_routes( int s, vector<Route>& route_table );

void print_route_table( int nroutes, vector<Route> route_table );

