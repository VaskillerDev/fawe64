#include"libs.h"

struct ImagePool
{
    void* data;
    Image** images;
    uint_32 imageCount;
    uint_32 offset;
};

typedef struct ImagePool ImagePool;

void imagePool_init(ImagePool* pool);
Image* imagePool_addImage(ImagePool* pool, void* dataPtr, uint_32 size, uint_32 w, uint_32 h, uint_16 colors[4], uint_32 flags);
Image* imagePool_getImage(ImagePool* pool, uint_32 index);