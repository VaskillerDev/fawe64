#include "image.h"
#include "vec2.h"

struct Sprite
{
    uint_32 currentImageIndex;
    Image* currentImage;
    Image** images;
    uint_32 imageCount;
    uint_32 frameCounter;
    uint_32 animDelay;

    Vec2 pos;
};

typedef struct Sprite Sprite;

Sprite* sprite_new(Image* images[], uint_32 imageCount, uint_32 animDelay);
void sprite_Draw(Sprite* sprite);