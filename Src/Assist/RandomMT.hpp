/* ------------------------------------------------ *
 *  Written by:      Nagy Balint                    *
 *  Contact:         b.nagy.balint@gmail.com        *
 *                                                  *
 *  This file can be used/improved/redistributed    *
 *  under GNU public license                        *
 *                                                  *
 *  Nagy Balint (C) 2010                            *
 * ------------------------------------------------ */

/* ------------------------------------------------ *
 *  Library:         bcore                          *
 *  Version:         0.8.00                         *
 *  Date:            19-01-2011                     *
 * ------------------------------------------------ */


#ifndef RANDOM_MT_HPP_
#define RANDOM_MT_HPP_

#include "Assist/Common.h"

/**
* Pseudo random number generator (PRNG) class which uses the Mersene twister
* algorithm to create high-presision and acceptably distributed pseudo-random
* numbers. Code implemented directly from Wikipedia pseudocode.
*/
class MTRandomizer {

    public:

        /// Constructor using default seed.
        MTRandomizer();
        /// Constructor using user-defined seed.
        MTRandomizer(const unsigned int seed);
        /// Destructor
        ~MTRandomizer();

        /// Set seed to user-defined value
        void seed(const unsigned int seed);
        /// Set seed to default value
        void seed();

        /// Randomize integer in [0, randMax].
        unsigned int random ();
        /// Randomize integer in [a, b-1].
        unsigned int random (unsigned int a, unsigned int b);

        /// Randomize float with uniform distribution in [0,1].
        float  randomUniform ();
        /// Randomize float with uniform distribution in [min,max].
        float  randomUniform (float min, float max);
        /// Randomize float with uniform distribution in [-1,1].
        /// Same as randomUniform(-1,1).
        float  randomNormalized ();
        /// Randomize float with Standard Gaussian (Normal) distribution.
        /// Same as randomGaussian(0,1).
        float  randomGaussian ();
        /// Randomize float with Gaussian (Normal) distribution.
        /// Parameter m is the mean value, d is the standard deviation
        float  randomGaussian (float m, float d);

        /// Randomize integer in [0, randMax] n times and store it in ptr.
        unsigned int* random (unsigned int* ptr, unsigned int n);
        /// Randomize integer in [a, b-1] n times and store it in ptr.
        unsigned int* random (unsigned int* ptr, unsigned int n, unsigned int a, unsigned int b);

        /// Randomize float with uniform distribution in [0,1] n times and store it in ptr.
        float* randomUniform (float* ptr, unsigned int n);
        /// Randomize float with uniform distribution in [min,max] n times and store it in ptr.
        float* randomUniform (float* ptr, unsigned int n, float min, float max);
        /// Randomize float with uniform distribution in [-1,1] n times and store it in ptr.
        /// Same as randomUniform(ptr,n,-1,1).
        float* randomNormalized (float* ptr, unsigned int n);
        /// Randomize float with Standard Gaussian (Normal) distribution n times and store it in ptr.
        /// Same as randomGaussian(ptr,n,0,1).
        float* randomGaussian (float* ptr, unsigned int n);
        /// Randomize float with Gaussian (Normal) distribution n times and store it in ptr.
        /// Parameter m is the mean value, d is the standard deviation
        float* randomGaussian (float* ptr, unsigned int n, float m, float d);

        /**
        * MTrandomizer instance using default seed. Calling
        * function Random() results in calling randomize()
        * of this instance.
        */
        static MTRandomizer& current();

        static unsigned int randMax();

    protected:

        unsigned int* MTdata;                           // data of the randomization, its recalculated every 623 RNG
        unsigned int MTindex;                           // index of the current RNG out of 623

        void generate();                                // (re)calculate MTdata
        void initialize(const unsigned int seed);       // initialize MTdata, with MTdata[0] = seed

};

/**
* Return random numbers using DefaultMTRandomizer instance
*  -> Random():            random number from [ 0, randMax ]
*  -> Random(ub):          random number from [ 0, ub-1 ]
*  -> Random(a,b):         random number from [ a, b-1 ]
*  -> RandomUniform():     uniform random floating point number from [ 0, 1 ]
*  -> RandomUniform(a,b):  uniform random floating point number from [ a, b ]
*  -> RandomNormalized():  uniform random floating point number from [ -1, 1 ]
*  -> RandomGaussian()     random float with standard normal distribution
*  -> RandomGaussian(m,d)  random float with normal distribution with mean m and variance d
*
*  -> Random(ptr,n):             n random numbers from [ 0, randMax ], store it in ptr
*  -> Random(ptr,n,ub):          n random numbers from [ 0, ub-1 ], store it in ptr
*  -> Random(ptr,n,a,b):         n random numbers from [ a, b-1 ], store it in ptr
*  -> RandomUniform(ptr,n):      n random floating point numbers from [ 0, 1 ], store it in ptr
*  -> RandomUniform(ptr,na,b):   n random floating point numbers from [ a, b ], store it in ptr
*  -> RandomNormalized(ptr,n):   n random floating point numbers from [ -1, 1 ], store it in ptr
*  -> RandomGaussian(ptr,n)      n random floats with standard normal distribution, store it in ptr
*  -> RandomGaussian(ptr,n,m,d): n random floats with normal distribution with mean m and variance d, store it in ptr
*/

unsigned int Random ();
unsigned int Random (unsigned int ub);
unsigned int Random (unsigned int a, unsigned int b);
float RandomUniform ();
float RandomUniform (float min, float max);
float RandomNormalized ();
float RandomGaussian ();
float RandomGaussian (float m, float d);

unsigned int* Random (unsigned int* ptr, unsigned int n);
unsigned int* Random (unsigned int* ptr, unsigned int n, unsigned int ub);
unsigned int* Random (unsigned int* ptr, unsigned int n, unsigned int a, unsigned int b);
float* RandomUniform (float* ptr, unsigned int n);
float* RandomUniform (float* ptr, unsigned int n, float min, float max);
float* RandomNormalized (float* ptr, unsigned int n);
float* RandomGaussian (float* ptr, unsigned int n);
float* RandomGaussian (float* ptr, unsigned int n, float m, float d);


inline unsigned int Random () {
    return MTRandomizer::current().random();
}

inline unsigned int Random (unsigned int ub) {
    return MTRandomizer::current().random(0U, ub);
}

inline unsigned int Random (unsigned int a, unsigned int b) {
    return MTRandomizer::current().random(a, b);
}

inline float RandomUniform () {
    return MTRandomizer::current().randomUniform();
}

inline float RandomUniform (float min, float max) {
    return MTRandomizer::current().randomUniform(min, max);
}

inline float RandomNormalized () {
    return MTRandomizer::current().randomNormalized();
}

inline float RandomGaussian () {
    return MTRandomizer::current().randomGaussian();
}

inline float RandomGaussian (float m, float d) {
    return MTRandomizer::current().randomGaussian(m, d);
}

inline unsigned int* Random (unsigned int* ptr, unsigned int n) {
    return MTRandomizer::current().random(ptr, n);
}

inline unsigned int* Random (unsigned int* ptr, unsigned int n, unsigned int ub) {
    return MTRandomizer::current().random(ptr, n, 0U, ub);
}

inline unsigned int* Random (unsigned int* ptr, unsigned int n, unsigned int a, unsigned int b) {
    return MTRandomizer::current().random(ptr, n, a, b);
}

inline float* RandomUniform (float* ptr, unsigned int n) {
    return MTRandomizer::current().randomUniform(ptr, n);
}

inline float* RandomUniform (float* ptr, unsigned int n, float min, float max) {
    return MTRandomizer::current().randomUniform(ptr, n, min, max);
}

inline float* RandomNormalized (float* ptr, unsigned int n) {
    return MTRandomizer::current().randomNormalized(ptr, n);
}

inline float* RandomGaussian (float* ptr, unsigned int n) {
    return MTRandomizer::current().randomGaussian(ptr, n);
}

inline float* RandomGaussian (float* ptr, unsigned int n, float m, float d) {
    return MTRandomizer::current().randomGaussian(ptr, n, m, d);
}

#endif /* RANDOM_MT_HPP_ */
