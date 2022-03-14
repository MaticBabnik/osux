//
// Created by babnik on 3/8/22.
//

#include "Render.hxx"

namespace Core::Render {


    /**
     * @brief Writes out points to form an arc
     * @param center The center point
     * @param r1 Inner radius
     * @param r2 Outer radius
     * @param f Length (0-1)
     * @param ox output array for x points
     * @param oy output array for y points
     * @param nPointsMax ox and oy size
     * @return how many points were set (pass this to the polygon function)
     */
    size_t SetupArc(SDL_Point center, double r1, double r2, double f, double *ox, double *oy, size_t nPointsMax) {
        if (f == 0) return 0; //dont render anything

        size_t res = nPointsMax / 2;
        f *= 2 * numbers::pi;
        auto step = f / (res-1);
        double a = 0;

        //compute the outer points
        for (int i = 0; i < res; i++) {
            ox[i] = center.x + sin(a) * r2;
            oy[i] = center.y + cos(a) * r2;
            a += step;

        }

        for (int i = 0; i < res; i++) {
            a -= step;
            ox[res + i] = center.x + sin(a) * r1;
            oy[res + i] = center.y + cos(a) * r1;
        }

        return nPointsMax;
    }

}
