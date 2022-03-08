#include "Osu.hxx"
#include <stdexcept>

using namespace std;

// #fuckPpy

double getArFadeinTime(double ar) { //TODO: close enough but not 100% accurate
    if (ar < 0) throw runtime_error("AR must be positive... WHAT THE FUCK!");

    if (ar > 5) return -120.0 * ar + 1800;
    else return -150 * ar + 1950; // why can't AR just be linear?
}

double getCsSize(double cs) {
    if (cs < 0) throw runtime_error("CS must be positive... WHAT THE FUCK!");
    //stolen from the wiki
    return 54.4 - 4.48 * cs;
}
