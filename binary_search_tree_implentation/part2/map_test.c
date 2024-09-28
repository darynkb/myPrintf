#include <stdio.h>
#include "map.h"

int main() {
    map *mp = create_map();
    define(mp, "Toyota", 1);
    define(mp, "BMW", 2);
    define(mp, "Nissan", 3);
    define(mp, "Mercedes", 4);
    define(mp, "Porsche", 5);
    print_map(mp);

    printf("\nLoad factor: %f\n", load_factor(mp));
    printf("Bucket size standard deviation: %f\n", bucket_size_stdev(mp));
    printf("\nValue of 'BMW': %d\n", get_value(mp, "BMW")); 
    printf("Contains 'Mercedes': %d\n", contains_key(mp, "Mercedes"));

    clear_map(mp);
    destroy_map(mp);
    return 0;
}
