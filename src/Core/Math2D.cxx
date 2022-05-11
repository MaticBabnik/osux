#include "Math2D.hxx"

long Core::dot_product(SDL_Point v1, SDL_Point v2) {
    return v1.x * v2.x + v1.y * v2.y;
}
