#ifndef COMPLEX_H
#define COMPLEX_H

#include "math.h"
typedef struct complex
{
    double re;
    double im;
} complex;

complex cpx_jexp(double w);
complex cpx_prod(complex a, complex b);
complex cpx_div_int(complex a, int b);
complex cpx_add(complex a, complex b);
complex cpx_sub(complex a, complex b);
complex cpx_create(double re, double im);

#endif