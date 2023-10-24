/* find_routes.h */

typedef struct {
    int dest, link;		/* Destination and link used to get there */
    int length;			/* Length of path to dest */
} route_entry;



void find_routes( int s, route_entry route_table[] );
void print_route_table( int nroutes, route_entry route_table[] );

