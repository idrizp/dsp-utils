#include "filter.h"
#include <stdlib.h>

typedef struct circ_buff
{
    int head;  // The write pointer
    int tail;  // The read pointer
    int N;     // The number of elements it can hold
    int *buff; // The buffer
} circ_buff;

void circ_buff_create(int n, circ_buff *out)
{
    double *buff = (int *)calloc(n, sizeof(double));
    *out = (circ_buff){
        .head = 0,
        .tail = 0,
        .buff = buff,
        .N = n,
    };
    return out;
}

// Writes to the circular buffer.
void circ_buff_write(circ_buff *circ, double value)
{
    circ->buff[circ->head] = value;
    circ->head = (circ->tail + 1) % circ->N;
}

// Reads from the circular buffer.
void circ_buff_read(circ_buff *circ, double *value)
{
    *value = circ->buff[circ->tail];
    circ->tail = (circ->tail + 1) % circ->N;
}

void fir(int x, circ_buff *buff, double *h, int L, int *y)
{
    circ_buff_write(&buff, x);
    // y[n] = sum(i=0, L-1){x[n - i]h[i]}
    for (int i = 0; i < L; i++)
    {
        circ_buff_read(&buff, &x);
        *y += h[i] * x;
    }
}

void iir(int x, circ_buff *in_buff, circ_buff *out_buff, double *b, double *a, int L, int M, int *y)
{
    // y[n] = sum(i=0, L-1){x[n - i]b[i]} + sum(i=0,M-1){y[n-i]a[i]}
    circ_buff_write(&in_buff, x);
    for (int i = 0; i < L; i++)
    {
        circ_buff_read(&in_buff, &x);
        *y += b[i] * x;
    }
    for (int i = 0; i < M; i++)
    {
        circ_buff_read(&out_buff, &x); // Now we are reading the previous outputs
        *y += a[i] * x;
    }
    circ_buff_write(&out_buff, *y);
}

void sosfilt_filter(int x, sosfilt *filter, circ_buff *in_buff, circ_buff *out_buff, int *y)
{
    for (int row = 0; row < filter->L; row++)
    {
        double *coeff = filter->sos[row];
        int out;
        iir(x, in_buff, out_buff, (double[3]){coeff[0], coeff[1], coeff[2]}, (double[2]){coeff[4], coeff[5]}, 3, 2, y);
        (*y) *= filter->G[row]; // Multiplied by the gain.
    }
}
