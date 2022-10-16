#pragma once
#include "libs.h"

typedef struct AllocatorNode
{
    struct AllocatorNode* nextNode;
    unsigned long size;
    bool free;
} AllocatorNode;

void allocator_init();
void* allocate(unsigned long size);
void alloc_free(void* ptr);