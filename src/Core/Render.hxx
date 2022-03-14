#pragma once

#include "../include.hxx"

#include "Engine.hxx"
#include <numbers>
#include <cmath>

using namespace std::numbers;
#define PI pi_v<float>

namespace Core::Render {
    size_t SetupArc(SDL_Point center, float radius, float f, double *out_x, double *out_y, size_t nPointsMax);
}