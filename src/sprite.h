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
    Vec2 size;
};

typedef struct Sprite Sprite;

Sprite* sprite_animated_new(Image* images[], uint_32 imageCount, uint_32 animDelay);
Sprite* sprite_new(Image* image);
void sprite_Draw(Sprite* sprite);