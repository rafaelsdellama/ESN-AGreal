/*
 * File:   Random.cpp
 * Author: Shimo Ken
 *
 * Created on July 28, 2010, --:--
 *
 * Implementation of class Random.
 */

#include <cmath>

#include "Random.h"

Random::Random(int function, long seed) {
    idum = new long;
    *idum = seed;

    hasNextGaussian = false;

    switch(function) {
        case RAN0:
            ran = ran0;
            break;
        case RAN1:
            *idum *= (seed > 0) ? -1 : 1; //guarantees idum < 0.
            ran = ran1;
            break;
        case RAN2:
            ran = ran2;
    }
}

Random::~Random() {
    delete idum;
}

int Random::nextInt(int max) {
    return (int)floor(max*nextFloat());
}

bool Random::nextBool() {
    return nextFloat() < 0.5;
}

long double Random::nextGaussian(long double m, long double sd) {
    long double x1, x2, w, next;

    if (hasNextGaussian) //use value from previous call
    {
        next = nextNextGaussian;
        hasNextGaussian = false;
    }
    else
    {
        do {
            x1 = 2.0 * nextFloat() - 1.0;
            x2 = 2.0 * nextFloat() - 1.0;
            w = x1 * x1 + x2 * x2;
        } while ( w >= 1.0 || w == 0);

        w = sqrt( (-2.0 * log( w ) ) / w );
        next = x1 * w;
        nextNextGaussian = x2 * w;
        hasNextGaussian = true;
    }

    return( m + next * sd );
}

long double Random::nextFloat(long double min, long double max) {
    return  nextFloat() * (max-min) + min;
}

long double Random::nextFloat() {
    return (*ran)(idum);
}

long Random::getidum() {
    return *idum;
}
