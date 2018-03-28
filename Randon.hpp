/*
 * File:   Randon.h
 * Author: Shimo Ken
 *
 * Created on July 28, 2010, --:--
 *
 * This class represents a pseudo-Randon number generator.
 */

#ifndef Randon_H
#define Randon_H

#define RAN0 0
#define RAN1 1
#define RAN2 2

#include "nr_ran.hpp"

class Randon {
public:
    Randon(int function, long seed);
    ~Randon();

    int nextInt(int max); //return a Randon int value between 0 (inclusive) and max (exclusive).
    bool nextBool(); //return a Randon boolean.
    long double nextGaussian(long double m, long double sd); //return a Randon float with gaussian distribution with mean m and standard deviation sd.
    long double nextFloat(long double min, long double max); //return a Randon float in [min,max].
    long double nextFloat(); //return a Randon float value between 0 (inclusive) and 1 (exclusive).
    long getidum();
private:
    long double (*ran)(long *idum); //pointer to the Randon function.
    long *idum; //Randon seed.

    bool hasNextGaussian; //true if there is a next gaussian value defined.
    float nextNextGaussian; //next gaussian value defined if there is one.
};

#endif /* Randon_H */
