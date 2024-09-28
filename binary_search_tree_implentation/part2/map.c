#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "map.h"

// Hash function
unsigned long hash_function(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}

// Creates a new empty map on the heap
map* create_map() {
    map *mp = (map*)malloc(sizeof(map));
    if (!mp) {
        printf("Failed to allocate memory for map");
        return 0;
    }
    mp->buckets = (node**)calloc(INITIAL_BUCKETS, sizeof(node*));
    if (!mp->buckets) {
        printf("Failed to allocate memory for buckets");
        free(mp);
        return 0;
    }
    mp->map_size = 0;
    mp->num_of_buckets = INITIAL_BUCKETS;
    return mp;
}

// Helper function to free the linked list in each bucket
void free_bucket_list(node *bucket) {
    node *current = bucket;
    while (current != NULL) {
        node *next = current->link;
        free(current->key);
        free(current);
        current = next;
    }
}

// Destroys the map, and frees up its memory
void destroy_map(map *mp) {
    for (size_t i = 0; i < mp->num_of_buckets; i++) {
        free_bucket_list(mp->buckets[i]);
    }
    free(mp->buckets);
    free(mp);
}

// Rehash the map when load factor exceeds the MAX_LOAD_FACTOR
void rehash(map *mp) {
    size_t old_num_buckets = mp->num_of_buckets;
    node **old_buckets = mp->buckets;
    mp->num_of_buckets *= 2;
    mp->buckets = (node**)calloc(mp->num_of_buckets, sizeof(node*));
    for (size_t i = 0; i < old_num_buckets; i++) {
        node *current = old_buckets[i];
        while (current != NULL) {
            node *next = current->link;
            unsigned long hash_index = hash_function(current->key) % mp->num_of_buckets;
            current->link = mp->buckets[hash_index];
            mp->buckets[hash_index] = current;
            current = next;
        }
    }
    free(old_buckets);
}

// Adds the key-value pair (key, val) to the map
void define(map *mp, char *key, int val) {
    if ((double)mp->map_size / mp->num_of_buckets > MAX_LOAD_FACTOR) {
        rehash(mp);
    }
    unsigned long hash_index = hash_function(key) % mp->num_of_buckets;
    node *current = mp->buckets[hash_index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = val; 
            return;
        }
        current = current->link;
    }

    // Insert a new node
    node *new_node = (node*)malloc(sizeof(node));
    if (!new_node) {
        perror("Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    new_node->key = strdup(key);
    new_node->value = val;
    new_node->link = mp->buckets[hash_index];
    mp->buckets[hash_index] = new_node;
    mp->map_size++;
}

// Checks if the given key is in the map
_Bool contains_key(map *mp, char *key) {
    unsigned long hash_index = hash_function(key) % mp->num_of_buckets;
    node *current = mp->buckets[hash_index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return 1;
        }
        current = current->link;
    }
    return 0; 
}

// Returns the value associated with the given key;
// If the key is not there, output an error message to the
// console window, and return INT_MIN
int get_value(map *mp, char *key) {
    unsigned long hash_index = hash_function(key) % mp->num_of_buckets;
    node *current = mp->buckets[hash_index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->link;
    }
    fprintf(stderr, "Key not found\n");
    return INT_MIN;
}

// Returns the number of key-value pairs in the map
size_t map_size(map *mp) {
    return mp->map_size;
}

// Removes all of the key-value pairs from the map
void clear_map(map *mp) {
    for (size_t i = 0; i < mp->num_of_buckets; i++) {
        free_bucket_list(mp->buckets[i]);
        mp->buckets[i] = NULL;
    }
    mp->map_size = 0;
}

// Outputs the key-value pairs in the map to the console window
void print_map(map *mp) {
    for (size_t i = 0; i < mp->num_of_buckets; i++) {
        node *current = mp->buckets[i];
        if (current != NULL) {
            printf("Bucket %zu:\n", i);
        }
        while (current != NULL) {
            printf("  %s: %d\n", current->key, current->value);
            current = current->link;
        }
    }
}

// Outputs the load factor of the underlying hash table
double load_factor(map *mp) {
    return (double)mp->map_size / mp->num_of_buckets;
}

// Outputs the standard deviation of the sizes of the buckets
// in the underlying hash table
double bucket_size_stdev(map *mp) {
    double mean = (double)mp->map_size / mp->num_of_buckets;
    double variance = 0.0;

    for (size_t i = 0; i < mp->num_of_buckets; i++) {
        size_t bucket_size = 0;
        node *current = mp->buckets[i];
        while (current != NULL) {
            bucket_size++;
            current = current->link;
        }
        variance += (bucket_size - mean) * (bucket_size - mean);
    }

    variance /= mp->num_of_buckets;
    return sqrt(variance);
}
