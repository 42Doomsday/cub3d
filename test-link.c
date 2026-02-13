#include "free_list_allocator.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

typedef struct Node {
    size_t blockSize;
    struct Node* next;
} Node;

typedef struct {
    size_t blockSize;
    size_t padding;
} AllocationHeader;

struct FreeListAllocator {
    void* start_ptr;
    size_t totalSize;
    size_t used;
    size_t peak;
    PlacementPolicy policy;
    Node* freeList;
};

static size_t calculate_padding(uintptr_t base, size_t alignment, size_t headerSize) {
    size_t multiplier = (base / alignment) + 1;
    uintptr_t alignedAddress = multiplier * alignment;
    size_t padding = alignedAddress - base;

    if (padding < headerSize) {
        size_t needed = headerSize - padding;
        size_t extra = alignment * ((needed / alignment) + 1);
        padding += extra;
    }
    return padding;
}

void fl_init(FreeListAllocator* allocator, size_t totalSize, PlacementPolicy policy) {
    allocator->totalSize = totalSize;
    allocator->policy = policy;
    allocator->used = 0;
    allocator->peak = 0;

    allocator->start_ptr = malloc(totalSize);
    fl_reset(allocator);
}

void fl_destroy(FreeListAllocator* allocator) {
    free(allocator->start_ptr);
}

void fl_reset(FreeListAllocator* allocator) {
    allocator->used = 0;
    allocator->peak = 0;

    allocator->freeList = (Node*)allocator->start_ptr;
    allocator->freeList->blockSize = allocator->totalSize;
    allocator->freeList->next = NULL;
}

static void find_first(FreeListAllocator* allocator,
                       size_t size,
                       size_t alignment,
                       Node** previous,
                       Node** found,
                       size_t* padding) {

    Node* it = allocator->freeList;
    Node* itPrev = NULL;

    while (it) {
        *padding = calculate_padding((uintptr_t)it, alignment, sizeof(AllocationHeader));
        size_t required = size + *padding;

        if (it->blockSize >= required)
            break;

        itPrev = it;
        it = it->next;
    }

    *previous = itPrev;
    *found = it;
}

void* fl_allocate(FreeListAllocator* allocator, size_t size, size_t alignment) {
    Node* previous = NULL;
    Node* found = NULL;
    size_t padding = 0;

    find_first(allocator, size, alignment, &previous, &found, &padding);

    if (!found)
        return NULL;

    size_t requiredSize = size + padding;
    size_t rest = found->blockSize - requiredSize;

    if (rest > 0) {
        Node* newNode = (Node*)((uintptr_t)found + requiredSize);
        newNode->blockSize = rest;
        newNode->next = found->next;

        if (previous)
            previous->next = newNode;
        else
            allocator->freeList = newNode;
    } else {
        if (previous)
            previous->next = found->next;
        else
            allocator->freeList = found->next;
    }

    uintptr_t headerAddress = (uintptr_t)found + (padding - sizeof(AllocationHeader));
    uintptr_t dataAddress = headerAddress + sizeof(AllocationHeader);

    AllocationHeader* header = (AllocationHeader*)headerAddress;
    header->blockSize = requiredSize;
    header->padding = padding - sizeof(AllocationHeader);

    allocator->used += requiredSize;
    if (allocator->used > allocator->peak)
        allocator->peak = allocator->used;

    return (void*)dataAddress;
}

static void coalesce(FreeListAllocator* allocator) {
    Node* it = allocator->freeList;

    while (it && it->next) {
        if ((uintptr_t)it + it->blockSize == (uintptr_t)it->next) {
            it->blockSize += it->next->blockSize;
            it->next = it->next->next;
        } else {
            it = it->next;
        }
    }
}

void fl_free(FreeListAllocator* allocator, void* ptr) {
    uintptr_t currentAddress = (uintptr_t)ptr;
    uintptr_t headerAddress = currentAddress - sizeof(AllocationHeader);

    AllocationHeader* header = (AllocationHeader*)headerAddress;

    Node* freeNode = (Node*)headerAddress;
    freeNode->blockSize = header->blockSize + header->padding;
    freeNode->next = NULL;

    Node* it = allocator->freeList;
    Node* prev = NULL;

    while (it && it < freeNode) {
        prev = it;
        it = it->next;
    }

    freeNode->next = it;

    if (prev)
        prev->next = freeNode;
    else
        allocator->freeList = freeNode;

    allocator->used -= freeNode->blockSize;

    coalesce(allocator);
}
