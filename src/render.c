#include "render.h"
#include <stdlib.h>

void DrawImage(Image *img, int_32 x, int_32 y, bool defaultColors)
{
    if (defaultColors)
    {
        SetDrawColor_1(img->colors[0]);
        SetDrawColor_2(img->colors[1]);
        SetDrawColor_3(img->colors[2]);
        SetDrawColor_4(img->colors[3]);
    }

    blit(img->data, x, y, img->width, img->height, BLIT_2BPP);
}

void SetPaletteColor_1(uint_32 newColor)
{
    PALETTE[0] = newColor;
}

uint_32 GetPaletteColor_1()
{
    return PALETTE[0];
}

void SetPaletteColor_2(uint_32 newColor)
{
    PALETTE[1] = newColor;
}

uint_32 GetPaletteColor_2()
{
    return PALETTE[1];
}

void SetPaletteColor_3(uint_32 newColor)
{
    PALETTE[2] = newColor;
}

uint_32 GetPaletteColor_3()
{
    return PALETTE[2];
}

void SetPaletteColor_4(uint_32 newColor)
{
    PALETTE[3] = newColor;
}

uint_32 GetPaletteColor_4()
{
    return PALETTE[3];
}

void SetDrawColor_1(uint_16 colorId)
{
    uint_16 currentColor = *DRAW_COLORS;
    currentColor = currentColor & 0xfff0;
    currentColor = currentColor | colorId;
    *DRAW_COLORS = currentColor;
}

void SetDrawColor_2(uint_16 colorId)
{
    uint_16 colorIndex = colorId << 4;
    uint_16 currentColor = *DRAW_COLORS;
    currentColor = currentColor & 0xff0f;
    currentColor = currentColor | colorIndex;
    *DRAW_COLORS = currentColor;
}

void SetDrawColor_3(uint_16 colorId)
{
    uint_16 colorIndex = colorId << 8;
    uint_16 currentColor = *DRAW_COLORS;
    currentColor = currentColor & 0xf0ff;
    currentColor = currentColor | colorIndex;
    *DRAW_COLORS = currentColor;
}

void SetDrawColor_4(uint_16 colorId)
{
    uint_16 colorIndex = colorId << 12;
    uint_16 currentColor = *DRAW_COLORS;
    currentColor = currentColor & 0x0fff;
    currentColor = currentColor | colorIndex;
    *DRAW_COLORS = currentColor;
}

void SetDrawColors(uint_16 colors)
{
    *DRAW_COLORS = colors;
}