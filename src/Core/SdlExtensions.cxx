#include "SdlExtensions.hxx"

void sux_thick_aa_line_mul(SDL_Renderer *r, SDL_Point *points, size_t n, int thickness, uint32_t color) {
    for (size_t i = 0; i < n; i++) {
        aaFilledEllipseColor(r, points[i].x, points[i].y, thickness, thickness, color);
    }

    double lp_x[4], lp_y[4];
    for (size_t j = 1; j < n; j++) {
        auto x1 = points[j - 1].x, y1 = points[j - 1].y, x2 = points[j].x, y2 = points[j].y;
        int dx = x2 - x1, dy = y2 - y1;
        double slope = (double) dy / (double) dx;
        double perpendicular_slope_rad = atan(-1 / slope);
        double ox = cos(perpendicular_slope_rad) * thickness, oy = sin(perpendicular_slope_rad) * thickness;

        //this is garbage
        lp_x[0] = x1 + ox;
        lp_y[0] = y1 + oy;
        lp_x[1] = x2 + ox;
        lp_y[1] = y2 + oy;
        lp_x[2] = x2 - ox;
        lp_y[2] = y2 - oy;
        lp_x[3] = x1 - ox;
        lp_y[3] = y1 - oy;

        aaFilledPolygonColor(r, lp_x, lp_y, 4, color);
    }
}

void sux_thick_aa_line(SDL_Renderer *r, int x1, int y1, int x2, int y2, float thickness, uint32_t color) {
    //draw a circle at both points
    filledCircleColor(r, x1, y1, thickness, color);
    filledCircleColor(r, x2, y2, thickness, color);
    aacircleColor(r, x2, y2, thickness, color);
    aacircleColor(r, x1, y1, thickness, color);

    int dx = x2 - x1, dy = y2 - y1;
    double slope = (double) dy / (double) dx;
    //TODO: is there a faster way?
    double perpendicular_slope_rad = atan(-1 / slope);
    double ox = cos(perpendicular_slope_rad) * thickness, oy = sin(perpendicular_slope_rad) * thickness;
    double lp_x[4], lp_y[4];

    //this is garbage
    lp_x[0] = x1 + ox;
    lp_y[0] = y1 + oy;
    lp_x[1] = x2 + ox;
    lp_y[1] = y2 + oy;
    lp_x[2] = x2 - ox;
    lp_y[2] = y2 - oy;
    lp_x[3] = x1 - ox;
    lp_y[3] = y1 - oy;

    aaFilledPolygonColor(r, lp_x, lp_y, 4, color);

}
