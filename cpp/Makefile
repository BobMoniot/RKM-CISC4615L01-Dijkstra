# Makefile for Project 3 and 4

# Add appropriate paths to these if needed.
CC		= cc $(CFLAGS)
CPP		= g++ $(CPPFLAGS)
RM		= rm -f

# Define CFLAGS, e.g. warnings if desired
CFLAGS		=

PATH_OBJS=dijkstra_path.o shortest_path.o load_graph.o
dijkstra_path: $(PATH_OBJS)
	$(CPP) -o dijkstra_path $(PATH_OBJS)

# Object file dependencies on header files
dijkstra_path.o: dijkstra_defs.h shortest_path.h load_graph.h
shortest_path.o: dijkstra_defs.h shortest_path.h
load_graph.o: dijkstra_defs.h load_graph.h

ROUTE_OBJS=dijkstra_routes.o load_graph.o find_routes.o
dijkstra_routes: $(ROUTE_OBJS)
	$(CPP) -o dijkstra_routes $(ROUTE_OBJS)

# Object file dependencies on header files
dijkstra_routes.o: dijkstra_defs.h find_routes.h load_graph.h
find_routes.o: dijkstra_defs.h find_routes.h

# Remove intermediate files that are not required after the program is built.
clean:
	-$(RM) *.o
	-$(RM) \#*
	-$(RM) *~
