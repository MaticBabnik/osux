#pragma once

#include "../include.hxx"

using namespace std;


namespace Core {
    typedef SDL_Point Vec2;

    struct Vec2F {
        double x,y;
    };

    struct m_circle {
        Vec2 center;
        double r;
    };

    /**
     * Distance between two points
     */
    double distance(Vec2 v1, Vec2 v2);

    /**
     * Subtracts two points
     */
    Vec2 delta(Vec2 v1, Vec2 v2);

    /**
     * Dot product of two vectors
     */
    long dot_product(Vec2 v1, Vec2 v2);

    double norm(Vec2 v);

    Vec2F unit_vec(Vec2 v);

    /**
     * "moves" the second point to change the distance between them, the angle stays the same.
     */
    Vec2 fix_point(Vec2 v1, Vec2 v2, double newDistance);

    /**
     * Returns the orientation
     */
    int get_orientation(Vec2 p,Vec2 q,Vec2 r);

    /**
     * I don't even know
     */
    float binomial_coefficent(int n, int k);

    /**
     * Gets circle from three points
     */
    m_circle get_circle(Vec2 p1, Vec2 p2, Vec2 p3);

    double angle_between_points(Vec2 c, Vec2 p);

    namespace Catmull {
        float get_t(float t, float alpha, const Vec2 p0, const Vec2 &p1);
        Vec2 catmull_rom_point(const Vec2 &p0, const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, float t);
    }
    namespace Bezier {
        Vec2 bezier_point(const vector<Vec2> &controlPoints, double t);
    }
    namespace Circle {
    }
}