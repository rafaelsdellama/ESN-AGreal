/*
 * File:   nr_ran.cpp
 * Author: Shimo Ken
 *
 * Created on July 28, 2010, --:--
 *
 * Implementation of Numerical Recipes ran0, ran1 and ran2.
 */

#include "nr_ran.h"

long double ran0(long *idum) {
    long k;
    long double ans;

    *idum ^= MASK; //XORing with MASK allows use of zero and other
    //simple bit patterns for idum.

    k = (*idum) / IQ;

    *idum = IA * (*idum - k * IQ) - IR * k; //Compute idum=(IA*idum) % IM without
    //over- flows by Schrage's method.
    if (*idum < 0) {
        *idum += IM;
    }

    ans = AM * (*idum); //Convert idum to a floating result.

    *idum ^= MASK; //Unmask before return.

    return ans;
}

long double ran1(long *idum) {
    int j;
    long k;
    static long iy = 0;
    static long iv[NTAB];
    long double temp;

    if (*idum <= 0 || !iy) // Initialize.
    {
        if (-(*idum) < 1)
            *idum = 1; //Be sure to prevent idum = 0.
        else
            *idum = -(*idum);

        for (j = NTAB + 7; j >= 0; j--) // Load the shu_e table (after 8 warm-ups).
        {
            k = (*idum) / IQ;
            *idum = IA * (*idum - k * IQ) - IR * k;

            if (*idum < 0)
                *idum += IM;
            if (j < NTAB)
                iv[j] = *idum;
        }
        iy = iv[0];
    }

    k = (*idum) / IQ; //Start here when not initializing.
    *idum = IA * (*idum - k * IQ) - IR * k; //Compute idum=(IA*idum) % IM without over-
    //flows by Schrage's method.
    if (*idum < 0)
        *idum += IM;

    j = iy / NDIV; //Will be in the range 0..NTAB-1.
    iy = iv[j]; // Output previously stored value and re_ll the shu_e table.
    iv[j] = *idum;
    if ((temp = AM * iy) > RNMX) //Because users don't expect endpoint values.
        return RNMX;
    else
        return temp;
}

long double ran2(long *idum) {
    int j;
    long k;
    static long idum2 = 123456789;
    static long iy = 0;
    static long iv[NTAB];
    long double temp;

    if (*idum <= 0) // Initialize.
    {
        if (-(*idum) < 1) // Be sure to prevent idum = 0.
            *idum = 1;
        else
            *idum = -(*idum);

        idum2 = (*idum);
        for (j = NTAB + 7; j >= 0; j--) // Load the shu_e table (after 8 warm-ups).
        {
            k = (*idum) / IQ1;
            *idum = IA1 * (*idum - k * IQ1) - k * IR1;

            if (*idum < 0)
                *idum += IM1;
            if (j < NTAB)
                iv[j] = *idum;
        }
        iy = iv[0];
    }

    k = (*idum) / IQ1; //Start here when not initializing.
    *idum = IA1 * (*idum - k * IQ1) - k * IR1; //Compute idum=(IA1*idum) % IM1 without
    //overflows by Schrage's method.
    if (*idum < 0)
        *idum += IM1;

    k = idum2 / IQ2;
    idum2 = IA2 * (idum2 - k * IQ2) - k * IR2; //Compute idum2=(IA2*idum) % IM2 likewise.
    if (idum2 < 0)
        idum2 += IM2;

    j = iy / NDIV1; //Will be in the range 0..NTAB-1.
    iy = iv[j] - idum2; //Here idum is shu_ed, idum and idum2 are
    //combined to generate output.
    iv[j] = *idum;

    if (iy < 1)
        iy += IMM1;

    if ((temp = AM1 * iy) > RNMX) // Because users don't expect endpoint values.
        return RNMX;
    else
        return temp;
}
