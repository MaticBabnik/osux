#include "Math2D.hxx"

long Core::dot_product(Vec2 v1, Vec2 v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

double Core::distance(Vec2 v1, Vec2 v2) {
    double dx = v2.x - v1.x, dy = v2.y - v1.y;

    return sqrt(dx * dx + dy * dy);
}

Vec2 Core::delta(Vec2 v1, Vec2 v2) {
    int dx = v2.x - v1.x, dy = v2.y - v1.y;
    return {dx, dy};
}

Vec2 Core::fix_point(Vec2 v1, Vec2 v2, double newDistance) {
    double currentDistance = distance(v1, v2);
    Vec2 lVec = delta(v1, v2);

    auto ratio = newDistance / currentDistance;

    return {v1.x + (int) (lVec.x * ratio),
            v1.y + (int) (lVec.y * ratio)};

}
