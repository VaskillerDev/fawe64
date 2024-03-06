#include "libs.h"

#define allocatorPoolSize (34000)

static AllocatorNode* allocator = NULL;
static unsigned long freeMemory = allocatorPoolSize - sizeof(AllocatorNode);

void allocator_init()
{
    allocator = (AllocatorNode*)malloc(allocatorPoolSize);
    memset(allocator, 0, allocatorPoolSize);

    allocator->nextNode = NULL;
    allocator->free = true;
    allocator->size = (allocatorPoolSize - sizeof(AllocatorNode));
}

void *allocate(unsigned long size)
{
    AllocatorNode *currentAllocatorNode = allocator;
    while (currentAllocatorNode != NULL)
    {
        if (currentAllocatorNode->free && currentAllocatorNode->size >= size)
        {
            currentAllocatorNode->free = false;

            if (currentAllocatorNode->size - size >= sizeof(AllocatorNode))
            {
                AllocatorNode* newAllocatorNode = (AllocatorNode*)(((char*)currentAllocatorNode) + size + sizeof(AllocatorNode));
                newAllocatorNode->free = true;
                newAllocatorNode->nextNode = currentAllocatorNode->nextNode;
                newAllocatorNode->size = currentAllocatorNode->size - size - sizeof(AllocatorNode);

                currentAllocatorNode->nextNode = newAllocatorNode;
                currentAllocatorNode->size = size;

                freeMemory -= sizeof(AllocatorNode);
            }

            void* ptr = (void*)(((char*)currentAllocatorNode) + sizeof(AllocatorNode));
            memset(ptr, 0, size);
            freeMemory -= size;
            //tracef("alloc: %d, %d", (int)size, (int)freeMemory);
            return ptr;
        }
        else
        {
            currentAllocatorNode = currentAllocatorNode->nextNode;
        }
    }

    return NULL;
}

void alloc_free(void* ptr)
{
    AllocatorNode* currentNode = (AllocatorNode*)(((char*)ptr) - sizeof(AllocatorNode));
    currentNode->free = true;
    memset(ptr, 0, currentNode->size);
    freeMemory += currentNode->size;
    //tracef("free: %d, %d", (int)currentNode->size, (int)freeMemory);
    currentNode = allocator;

    while (currentNode != NULL)
    {
        if(currentNode->free)
            if(currentNode->nextNode && currentNode->nextNode->free)
            {
                currentNode->size += currentNode->nextNode->size + sizeof(AllocatorNode);
                currentNode->nextNode = currentNode->nextNode->nextNode;
                  freeMemory += sizeof(AllocatorNode);
                continue;
            }

        currentNode = currentNode->nextNode;
    }
    
}