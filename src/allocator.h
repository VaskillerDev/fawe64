#pragma once
#include "stdlib.h"
#include "string.h"
#include "wasm4.h"
#include "stdbool.h"

typedef struct AllocatorNode
{
    struct AllocatorNode* nextNode;
    unsigned long size;
    bool free;
} AllocatorNode;

void allocator_init();
void* allocate(unsigned long size);
void alloc_free(void* ptr);