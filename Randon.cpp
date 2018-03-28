/*
 * File:   Randon.cpp
 * Author: Shimo Ken
 *
 * Created on July 28, 2010, --:--
 *
 * Implementation of class Randon.
 */

#include <cmath>

#include "Randon.hpp"

Randon::Randon(int function, long seed) {
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

Randon::~Randon() {
    delete idum;
}

int Randon::nextInt(int max) {
    return (int)floor(max*nextFloat());
}

bool Randon::nextBool() {
    return nextFloat() < 0.5;
}

long double Randon::nextGaussian(long double m, long double sd) {
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

long double Randon::nextFloat(long double min, long double max) {
    return  nextFloat() * (max-min) + min;
}

long double Randon::nextFloat() {
    return (*ran)(idum);
}

long Randon::getidum() {
    return *idum;
}
