#include "Math2D.hxx"

long Core::dot_product(Core::Vec2 v1, Core::Vec2 v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

double Core::distance(Core::Vec2 v1, Core::Vec2 v2) {
    double dx = v2.x - v1.x, dy = v2.y - v1.y;

    return sqrt(dx * dx + dy * dy);
}

Core::Vec2 Core::delta(Core::Vec2 v1, Core::Vec2 v2) {
    int dx = v2.x - v1.x, dy = v2.y - v1.y;
    return {dx, dy};
}

double Core::norm(Core::Vec2 v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

Core::Vec2F Core::unit_vec(Core::Vec2 v) {
    auto size = Core::norm(v);

    return {v.x / size, v.y/size};
}

Core::Vec2 Core::fix_point(Core::Vec2 base, Core::Vec2 npoint, double newDistance) {
    auto vec = delta(base, npoint);
    auto uv = unit_vec(vec);

    return {(int)(base.x + uv.x * newDistance), (int)(base.y + uv.y * newDistance)};
}

int Core::get_orientation(Core::Vec2 p, Core::Vec2 q, Core::Vec2 r) {
    auto o_raw = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    return (o_raw != 0) ? (o_raw / abs(o_raw)) : 0; // return -1, 0 or 1
}

Core::m_circle Core::get_circle(Core::Vec2 p1, Core::Vec2 p2, Core::Vec2 p3) {
    //no idea, I stole this
    int x12 = p1.x - p2.x;
    int y12 = p1.y - p2.y;

    int x13 = p1.x - p3.x;
    int y13 = p1.y - p3.y;

    int x31 = p3.x - p1.x;
    int y31 = p3.y - p1.y;

    int x21 = p2.x - p1.x;
    int y21 = p2.y - p1.y;

    int sx13 = pow(p1.x, 2) - pow(p3.x, 2);
    int sy13 = pow(p1.y, 2) - pow(p3.y, 2);

    int sx21 = pow(p2.x, 2) - pow(p1.x, 2);
    int sy21 = pow(p2.y, 2) - pow(p1.y, 2);

    double f = (double) ((sx13) * (x12)
                         + (sy13) * (x12)
                         + (sx21) * (x13)
                         + (sy21) * (x13))
               / (double) (2 * ((y31) * (x12) - (y21) * (x13)));
    double g = (double) ((sx13) * (y12)
                         + (sy13) * (y12)
                         + (sx21) * (y13)
                         + (sy21) * (y13))
               / (double) (2 * ((x31) * (y12) - (x21) * (y13)));

    double c = -pow(p1.x, 2) - pow(p1.y, 2) - 2 * g * p1.x - 2 * f * p1.y;

    double h = -g;
    double k = -f;
    double sqr_of_r = h * h + k * k - c;

    double r = sqrt(sqr_of_r);

    return {{(int) h, (int) k}, r};
}

double Core::angle_between_points(Core::Vec2 c, Core::Vec2 p) {
    double dx = p.x - c.x, dy = p.y - c.y;
    auto slope = dy / dx;

    return atan(slope);
}



