#include "complex.h";
#include "math.h";

// Complex exponential
complex cpx_jexp(double w)
{
    complex res = {cos(w), sin(w)};
    return res;
};

complex cpx_prod(complex a, complex b)
{
    double re = a.re * b.re - a.im * b.im;
    double im = a.re * b.im + a.im * b.re;
    return (complex){.re = re, .im = im};
}

complex cpx_div_int(complex a, int b)
{
    return (complex){.re = a.re / b, .im = a.im / b};
}

complex cpx_add(complex a, complex b)
{
    return (complex){.re = a.re + b.re, .im = a.im + b.im};
}

complex cpx_sub(complex a, complex b)
{
    return (complex){.re = a.re - b.re, .im = a.im - b.im};
}

complex cpx_create(double re, double im)
{
    return (complex){.re = re, .im = im};
}