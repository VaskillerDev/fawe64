#include "render.h"
#include "wasm4.h"

void DrawRectangle(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t colors[4])
{
   SetDrawColor_1(colors[0]);
   SetDrawColor_2(colors[1]);
   rect(x - w / 2, y - h / 2, w , h);
}

void DrawImage(Image *img, int32_t x, int32_t y)
{
    SetDrawColor_1(img->colors[0]);
    SetDrawColor_2(img->colors[1]);
    SetDrawColor_3(img->colors[2]);
    SetDrawColor_4(img->colors[3]);

    blit(img->data, x, y, img->width, img->height, img->flags);
}

void DrawImageWithCustomColors(Image *img, int32_t x, int32_t y, uint16_t customColors[4])
{
    SetDrawColor_1(customColors[0]);
    SetDrawColor_2(customColors[1]);
    SetDrawColor_3(customColors[2]);
    SetDrawColor_4(customColors[3]);

    blit(img->data, x, y, img->width, img->height, img->flags);
}

void DrawText(char *content, int32_t x, int32_t y, uint16_t colors[4])
{
    SetDrawColor_1(colors[0]);
    SetDrawColor_2(colors[1]);
    SetDrawColor_3(colors[2]);
    SetDrawColor_4(colors[3]);
    text(content, x, y);
}

void DrawBoundingVolume(BoundingVolume *bv)
{
    SetDrawColor_1(0);
    SetDrawColor_2(3);

    if (bv->shape == SPHERE)
        oval(bv->position->x - bv->size.x, bv->position->y - bv->size.x, bv->size.x * 2, bv->size.x * 2);

    if (bv->shape == BOX || bv->shape == BOX_TRIGGER)
        rect(bv->position->x - bv->size.x / 2, bv->position->y - bv->size.y / 2, bv->size.x , bv->size.y);
}

void SetPaletteColor_1(uint32_t newColor)
{
    PALETTE[0] = newColor;
}

uint32_t GetPaletteColor_1()
{
    return PALETTE[0];
}

void SetPaletteColor_2(uint32_t newColor)
{
    PALETTE[1] = newColor;
}

uint32_t GetPaletteColor_2()
{
    return PALETTE[1];
}

void SetPaletteColor_3(uint32_t newColor)
{
    PALETTE[2] = newColor;
}

uint32_t GetPaletteColor_3()
{
    return PALETTE[2];
}

void SetPaletteColor_4(uint32_t newColor)
{
    PALETTE[3] = newColor;
}

uint32_t GetPaletteColor_4()
{
    return PALETTE[3];
}

void SetDrawColor_1(uint16_t colorId)
{
    uint16_t currentColor = *DRAW_COLORS;
    currentColor = currentColor & 0xfff0;
    currentColor = currentColor | colorId;
    *DRAW_COLORS = currentColor;
}

void SetDrawColor_2(uint16_t colorId)
{
    uint16_t colorIndex = colorId << 4;
    uint16_t currentColor = *DRAW_COLORS;
    currentColor = currentColor & 0xff0f;
    currentColor = currentColor | colorIndex;
    *DRAW_COLORS = currentColor;
}

void SetDrawColor_3(uint16_t colorId)
{
    uint16_t colorIndex = colorId << 8;
    uint16_t currentColor = *DRAW_COLORS;
    currentColor = currentColor & 0xf0ff;
    currentColor = currentColor | colorIndex;
    *DRAW_COLORS = currentColor;
}

void SetDrawColor_4(uint16_t colorId)
{
    uint16_t colorIndex = colorId << 12;
    uint16_t currentColor = *DRAW_COLORS;
    currentColor = currentColor & 0x0fff;
    currentColor = currentColor | colorIndex;
    *DRAW_COLORS = currentColor;
}

void SetDrawColors(uint16_t colors)
{
    *DRAW_COLORS = colors;
}