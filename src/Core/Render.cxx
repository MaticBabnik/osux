//
// Created by babnik on 3/8/22.
//

#include "Render.hxx"

namespace Core::Render {

    size_t SetupArc(SDL_Point center, float radius, float f, SDL_FPoint *out, size_t nPointsMax) {
        size_t n = nPointsMax * f;
        out[0] = {(float) center.x, (float) center.y + radius};
        if (n == 0) return 1;
        if (n < 2) n = 2;

        out[0] = {(float) center.x, (float) center.y + radius};


        for (int s = 1; s < n; s++) {
            auto f1 = f / (n - 1) * s;

            out[s] = {
                    (float) center.x + (float) sin(2 * PI * f1) * radius,
                    (float) center.y + (float) cos(2 * PI * f1) * radius
            };

        }
        return n;
    }

    void RenderArc(SDL_FPoint *points, size_t n, int s) {
        auto e = Engine::getRenderer();

        SDL_RenderSetScale(e, s, s);
        SDL_SetRenderDrawBlendMode(e, SDL_BLENDMODE_BLEND); //don't know
        SDL_RenderDrawLinesF(e, points, n);
        SDL_RenderSetScale(e, 1, 1);
    }
}
