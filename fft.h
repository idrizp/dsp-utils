#ifndef FFT_H
#define FFT_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "complex.h"

complex fft_wN(int N, double n, double k, int ifft);  // The twiddle factors of the FFT.
void fft(complex *x, int N, complex **out, int ifft); // Performs the FFT on a sequence, IFFT if the ifft flag is set to 1

void fft_circ_conv(complex *x, complex *y, int N, int M, complex **out, int *length); // Performs a circular convolution

#endif // FFT_H
