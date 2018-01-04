/*
 * File:   Random.h
 * Author: Shimo Ken
 *
 * Created on July 28, 2010, --:--
 *
 * This class represents a pseudo-random number generator.
 */

#ifndef RANDOM_H
#define RANDOM_H

#define RAN0 0
#define RAN1 1
#define RAN2 2

#include "nr_ran.h"

class Random {
public:
    Random(int function, long seed);
    ~Random();

    int nextInt(int max); //return a random int value between 0 (inclusive) and max (exclusive).
    bool nextBool(); //return a random boolean.
    long double nextGaussian(long double m, long double sd); //return a random float with gaussian distribution with mean m and standard deviation sd.
    long double nextFloat(long double min, long double max); //return a random float in [min,max].
    long double nextFloat(); //return a random float value between 0 (inclusive) and 1 (exclusive).
    long getidum();
private:
    long double (*ran)(long *idum); //pointer to the random function.
    long *idum; //random seed.

    bool hasNextGaussian; //true if there is a next gaussian value defined.
    float nextNextGaussian; //next gaussian value defined if there is one.
};

#endif /* RANDOM_H */
