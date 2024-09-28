
#ifndef MAP_H_
#define MAP_H_

#include <stdlib.h>

#define INITIAL_BUCKETS 4
#define MAX_LOAD_FACTOR 3.0

typedef struct _node {
	char *key;
	int   value;
	struct _node *link;
} node;

typedef struct {
	size_t map_size;
	size_t num_of_buckets;
	node **buckets;
} map;


// Creates a new empty map on the heap
map* create_map();

// Destroys the map, and frees up its memory
void destroy_map(map *mp);

// Adds the key-value pair (key, val) to the map
void define(map *mp, char *key, int val);

// Checks if the given key is in the map
_Bool contains_key(map *mp, char *key);

// Returns the value associated with the given key;
// If the key is not there, output an error message to the
// console window, and return INT_MIN
int get_value(map *mp, char *key);

// Returns the number of key-value pairs in the map
size_t map_size(map *mp);

// Removes all of the key-value pairs from the map
void clear_map(map *mp);

// Outputs the key-value pairs in the map to the console window
void print_map(map *mp);

// Outputs the load factor of the underlying hash table
double load_factor(map *mp);

// Outputs the standard deviation of the sizes of the buckets
// in the underlying hash table
double bucket_size_stdev(map *mp);

#endif /* MAP_H_ */
