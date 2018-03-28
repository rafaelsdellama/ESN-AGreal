/*
 * File:   nr_ran.h
 * Author: Shimo Ken
 *
 * Created on July 28, 2010, --:--
 *
 * A library of pseudo-random number generator.
 */

#ifndef NR_RAN_H
#define NR_RAN_H

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define MASK 123459876
#define IM1 2147483563
#define IM2 2147483399
#define AM1 (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define NDIV1 (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

long double ran0(long *idum);
long double ran1(long *idum); //call to this function must have idum < 0.
long double ran2(long *idum);

#endif /* NR_RAN_H */
