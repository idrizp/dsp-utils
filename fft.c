#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "complex.h"
#include "fft.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

// Twiddle factor
complex fft_wN(int N, double n, double k, int ifft)
{
	complex res = cpx_jexp((ifft ? 1 : -1) * (2 * M_PI * n * k) / N);
	return res;
}

void fft_helper(complex *x, int N, complex **out, int ifft)
{
	*out = (complex *)malloc(sizeof(complex) * N);
	complex *X = *out;
	if (N == 1)
	{
		X[0] = x[0];
		return;
	}

	complex *x_even = (complex *)malloc(sizeof(complex) * (N / 2));
	complex *x_odd = (complex *)malloc(sizeof(complex) * (N / 2));

	for (int i = 0; i < N; i++)
	{
		if (i % 2 == 0)
		{
			// Even index
			x_even[i / 2] = x[i];
		}
		else
		{
			// Odd index
			x_odd[(int)(i / 2)] = x[i];
		}
	}

	complex *X_even;
	complex *X_odd;

	fft_helper(x_even, N / 2, &X_even, ifft);
	fft_helper(x_odd, N / 2, &X_odd, ifft);
	for (int i = 0; i < N / 2; i++)
	{
		complex twiddle = fft_wN(N, i, 1, ifft);
		complex t = cpx_add(X_even[i], cpx_prod(twiddle, X_odd[i]));
		complex r = cpx_sub(X_even[i], cpx_prod(twiddle, X_odd[i]));
		(*out)[i] = t;
		(*out)[i + N / 2] = r;
	}
	free(X_even);
	free(X_odd);
	free(x_even);
	free(x_odd);
}

void fft(complex *x, int N, complex **out, int ifft)
{
	fft_helper(x, N, out, ifft);
	if (ifft)
	{
		for (int i = 0; i < N; i++)
		{
			(*out)[i] = cpx_div_int((*out)[i], N);
		}
	}
}

void fft_circ_conv(complex *x, complex *y, int N, int M, complex **out, int *length)
{
	// Performs circular convolution using FFT
	int l = MAX(N, M);
	*length = l;
	*out = (complex *)malloc(sizeof(complex) * l);
	fft(x, N, &x, 0);
	fft(y, M, &y, 0);
	for (int i = 0; i < l; i++)
	{
		if (N < i || M < i)
		{
			// Effectively acts as a zero pad.
			(*out)[i] = cpx_create(0, 0);
			continue;
		}
		(*out)[i] = cpx_prod(x[i], y[i]);
	}
	fft(x, N, &x, 1); // IFFT the passed in X
	fft(y, N, &y, 1); // IFFT the passed in Y
	fft(out, l, &out, 1);
}