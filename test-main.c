#include "free_list_allocator.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    FreeListAllocator* allocator = malloc(sizeof(FreeListAllocator));

    fl_init(allocator, 1024, FIND_FIRST);

    printf("Allocate 100 bytes\n");
    void* p1 = fl_allocate(allocator, 100, 8);

    printf("Allocate 200 bytes\n");
    void* p2 = fl_allocate(allocator, 200, 8);

    printf("Free first block\n");
    fl_free(allocator, p1);

    printf("Allocate 50 bytes\n");
    void* p3 = fl_allocate(allocator, 50, 8);

    printf("Free all\n");
    fl_free(allocator, p2);
    fl_free(allocator, p3);

    fl_destroy(allocator);
    free(allocator);

    return 0;
}
