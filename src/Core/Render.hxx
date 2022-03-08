#pragma once

#include "../include.hxx"

#include "Engine.hxx"
#include <numbers>
#include <cmath>

using namespace std::numbers;
#define PI pi_v<float>

namespace Core::Render {
    size_t SetupArc(SDL_Point center, float radius, float f, SDL_FPoint *out, size_t nPointsMax);

    void RenderArc(SDL_FPoint *points, size_t n, int s);
}