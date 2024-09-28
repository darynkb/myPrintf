#include <stdio.h>
#include "map.h"

int main() {
    map *mp = create_map();

    define(mp, "Toyota", 1);
    define(mp, "BMW", 2);
    define(mp, "Nissan", 3);
    printf("Map contents:\n");
    print_map(mp);

    printf("\nContains 'Nissan': %d\n", contains_key(mp, "Nissan"));  
    printf("Contains 'BMW': %d\n", contains_key(mp, "BMW"));    

    printf("\nValue of 'Nissan': %d\n", get_value(mp, "Nissan")); 
    printf("Value of 'Toyota': %d\n", get_value(mp, "Toyota"));       

    clear_map(mp);
    printf("Map size: %zu\n", map_size(mp)); 
    destroy_map(mp);
    printf("Map destroyed.\n");

    return 0;
}
