//
// Created by babnik on 5/5/22.
//

#include "Slideher.hxx"

/*
 * Mediocre factorial implementation
 */
long long IO::SliderMath::factorial(int n) {
    long long a = 1;
    auto n_abs = abs(n);

    while (n_abs > 1) {
        a*=n_abs--;
    }

    return n >= 0 ? a : -a;
}

double IO::SliderMath::binomial_coefficent(int n, int k) {
    return (double)factorial(n)  / (double)(factorial(k) * factorial(n-k));
}
