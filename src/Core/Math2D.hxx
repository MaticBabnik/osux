#pragma once

#include "../include.hxx"

#define Vec2 SDL_Point

using namespace std;

namespace Core {
    long dot_product(Vec2 v1, Vec2 v2);
    float binomial_coefficent(int n, int k);
    namespace Catmull {
        float get_t(float t, float alpha, const Vec2 p0, const Vec2 &p1);
        Vec2 catmull_rom_point(const Vec2 &p0, const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, float t);
    }
    namespace Bezier {
        Vec2 bezier_point(const vector<Vec2> &controllPoints, float t);
    }
    namespace Circle {

    }


}