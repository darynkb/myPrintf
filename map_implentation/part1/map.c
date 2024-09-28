#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "map.h"

// Creates a new tree node
tree_node* create_tree_node(const char* key, int value) {
    tree_node* new_node = (tree_node*)malloc(sizeof(tree_node));
    if (!new_node) {
        printf("Failed to allocate memory for new node");
        return 0;
    }
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Creates a new empty map on the heap
map* create_map() {
    map* mp = (map*)malloc(sizeof(map));
    if (!mp) {
        perror("Failed to allocate memory for map");
        exit(EXIT_FAILURE);
    }
    mp->root = NULL;
    mp->map_size = 0;
    return mp;
}

// Recursion for BST insertion
tree_node* insert(tree_node* root, const char* key, int value) {
    if (root == NULL) {
        return create_tree_node(key, value);
    }

    int cmp = strcmp(key, root->key);
    if (cmp < 0) {
        root->left = insert(root->left, key, value);
    } else if (cmp > 0) {
        root->right = insert(root->right, key, value);
    } else {
        root->value = value; 
    }
    return root;
}

// Adds the key-value pair (key, val) to the map
void define(map *mp, char *key, int val) {
    mp->root = insert(mp->root, key, val);
    mp->map_size++;
}

// Recursive search for a node by key
tree_node* search(tree_node* root, const char* key) {
    if (root == NULL) return NULL;

    int cmp = strcmp(key, root->key);
    if (cmp == 0) {
        return root;
    } else if (cmp < 0) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

// Checks if the given key is in the map
_Bool contains_key(map *mp, char *key) {
    return search(mp->root, key) != NULL;
}

// Returns the value associated with the given key;
// If the key is not there, output an error message to the
// console window, and return INT_MIN
int get_value(map *mp, char *key) {
    tree_node* node = search(mp->root, key);
    if (node == NULL) {
        fprintf(stderr, "Key not found\n");
        return INT_MIN;
    }
    return node->value;
}

// To recursively free the nodes in the tree
void free_tree(tree_node* root) {
    if (root == NULL) return;

    free(root->key);
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

// Destroy the map and free its memory
void destroy_map(map *mp) {
    free_tree(mp->root);
    free(mp);
}

// Returns the number of key-value pairs in the map
size_t map_size(map *mp) {
    return mp->map_size;
}

// Removes all of the key-value pairs from the map
void clear_map(map *mp) {
    free_tree(mp->root);
    mp->root = NULL;
    mp->map_size = 0;
}

// Recursive print of the key-value pairs
void print_in_order(tree_node* root) {
    if (root == NULL) return;

    print_in_order(root->left);
    printf("%s: %d\n", root->key, root->value);
    print_in_order(root->right);
}

// Outputs the key-value pairs in the map to the console window
void print_map(map *mp) {
    print_in_order(mp->root);
}
