#include "image.h"
#include <stdbool.h>

void DrawImage(Image *img, int_32 x, int_32 y, bool defaultColors);
void DrawText(char* content, int_32 x, int_32 y, uint_16 colors[4]);

void SetPaletteColor_1(uint_32 newColor);
uint_32 GetPaletteColor_1();

void SetPaletteColor_2(uint_32 newColor);
uint_32 GetPaletteColor_2();

void SetPaletteColor_3(uint_32 newColor);
uint_32 GetPaletteColor_3();

void SetPaletteColor_4(uint_32 newColor);
uint_32 GetPaletteColor_4();

void SetDrawColors(uint_16 colors);

void SetDrawColor_1(uint_16 colorId);
void SetDrawColor_2(uint_16 colorId);
void SetDrawColor_3(uint_16 colorId);
void SetDrawColor_4(uint_16 colorId);