#pragma once

#include "../include.hxx"

#include "Engine.hxx"
#include <numbers>
#include <cmath>

using namespace std::numbers;

namespace Core::Render {
    size_t SetupArc(SDL_Point center, double r1, double r2, double f, double *ox, double *oy, size_t nPointsMax);
}