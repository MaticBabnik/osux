#pragma once
#include "../include.hxx"

void sux_thick_aa_line_mul(SDL_Renderer *r, SDL_Point *points, size_t n, int thickness, uint32_t color);
void sux_thick_aa_line(SDL_Renderer *r, int x1, int y1, int x2, int y2, float thickness, uint32_t color);