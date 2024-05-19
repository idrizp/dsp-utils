#ifndef FILTER_H
#define FILTER_H

#include <stdlib.h>

/**
 * @file filter.h
 * @brief Header file for DSP filter functions.
 *
 * This file contains the declarations of functions related to digital signal processing (DSP) filters.
 * It defines a circular buffer structure and provides functions for creating, writing, and reading from the buffer.
 * It also includes functions for applying Infinite Impulse Response (IIR) and Finite Impulse Response (FIR) filters.
 */

/**
 * @brief Structure representing a circular buffer.
 *
 * The `circ_buff` struct is used to store and manage data in a circular buffer.
 * It keeps track of the write and read pointers, the number of elements it can hold,
 * and a pointer to the buffer itself.
 */
typedef struct circ_buff
{
    int head;     // The write pointer
    int tail;     // The read pointer
    int N;        // The number of elements it can hold
    double *buff; // The buffer
} circ_buff;

/**
 * @brief Secondary order structure filter.
 */
typedef struct sosfilt
{
    double **sos; // The SOS vector.
    double *G;    // The gain vector.
    int L;
} sosfilt;

/**
 * @brief Creates a circular buffer with the specified size.
 *
 * This function initializes a circular buffer with the specified size `n`.
 * The circular buffer is represented by the `circ_buff` struct pointed to by `out`.
 *
 * @param n The size of the circular buffer.
 * @param out Pointer to the `circ_buff` struct to store the created circular buffer.
 */
void circ_buff_create(int n, circ_buff *out);

/**
 * @brief Writes a value to the circular buffer.
 *
 * This function writes the value `value` to the circular buffer `circ`.
 * If the buffer is full, the oldest value will be overwritten.
 *
 * @param circ Pointer to the circular buffer.
 * @param value The value to be written to the buffer.
 */
void circ_buff_write(circ_buff *circ, double value);

/**
 * @brief Reads a value from the circular buffer.
 *
 * This function reads a value from the circular buffer `circ` and stores it in the variable pointed to by `value`.
 * If the buffer is empty, the value will be unchanged.
 *
 * @param circ Pointer to the circular buffer.
 * @param value Pointer to store the read value.
 */
void circ_buff_read(circ_buff *circ, double *value);

/**
 * @brief Applies a Finite Impulse Response (FIR) filter to the input signal.
 *
 * This function applies an FIR filter to the input signal `x` using the coefficients `h`.
 *
 * @param x The input signal value to be filtered.
 * @param buff The circular buffer.
 * @param h The filter coefficients.
 * @param L The length of the filter coefficients array `h`.
 * @param y Pointer to store the filtered output value.
 */
void fir(int x, circ_buff *buff, double *h, int L, int *y);

/**
 * @brief Applies an Infinite Impulse Response (IIR) filter to the input signal.
 *
 * This function applies an IIR filter to the input signal `x` using the coefficients `b` and `a`.
 * The filtered output is stored in the circular buffer `out_buff`.
 *
 * @param x The input signal value to be filtered.
 * @param in_buff The input circular buffer.
 * @param out_buff The output circular buffer.
 * @param b The numerator coefficients of the IIR filter.
 * @param a The denominator coefficients of the IIR filter.
 * @param L The length of the numerator coefficients array `b`.
 * @param M The length of the denominator coefficients array `a`.
 * @param y Pointer to store the filtered output value.
 */
void iir(int x, circ_buff *in_buff, circ_buff *out_buff, double *b, double *a, int L, int M, int *y);

/**
 * Applies a second-order section (SOS) filter to the input signal.
 *
 * @param x The input signal value to be filtered.
 * @param filter Pointer to the SOS filter structure.
 * @param in_buff Pointer to the input circular buffer.
 * @param out_buff Pointer to the output circular buffer.
 * @param y Pointer to store the filtered output signal value.
 */
void sosfilt_filter(int x, sosfilt *filter, circ_buff *in_buff, circ_buff *out_buff, int *y);

#endif // FILTER_H
