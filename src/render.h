#pragma once
#include "stdint.h"
#include "image.h"
#include "bounding_volume.h"

void DrawRectangle(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t colors[4]);
void DrawImage(Image *img, int32_t x, int32_t y);
void DrawImageWithCustomColors(Image *img, int32_t x, int32_t y, uint16_t customColors[4]);
void DrawText(char* content, int32_t x, int32_t y, uint16_t colors[4]);
void DrawBoundingVolume(BoundingVolume* bv);
void DrawProgressBar(int32_t val);

void SetPaletteColor_1(uint32_t newColor);
uint32_t GetPaletteColor_1();

void SetPaletteColor_2(uint32_t newColor);
uint32_t GetPaletteColor_2();

void SetPaletteColor_3(uint32_t newColor);
uint32_t GetPaletteColor_3();

void SetPaletteColor_4(uint32_t newColor);
uint32_t GetPaletteColor_4();

void SetDrawColors(uint16_t colors);

void SetDrawColor_1(uint16_t colorId);
void SetDrawColor_2(uint16_t colorId);
void SetDrawColor_3(uint16_t colorId);
void SetDrawColor_4(uint16_t colorId);