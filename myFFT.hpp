/*
 * myFFT.hpp - Fast Fourier Transform (FFT)
 * Based on Interface Magazine, CQ Publishing, Sep. 2021, p. 53, List 1
 * Ported to C++ using myComplex class
 * (c) 2021 @RR_Inyo
 * Released under the MIT license
 * https://opensource.org/licenses/mit-license.php
 */

#ifndef _MYFFT_
#define _MYFFT_

#include <math.h>
#include "myComplex.hpp"

// FFT function prototype, recursive and non-recursive version
void fft_re(myComplex *f, int N);          // Recursive, based on Interface Magazine, Sep. 2021, p. 53, List 1, simple reordering

void fft_re_br(myComplex *f, int N);       // Recursive, based on Interface Magazine, Sep. 2021, p. 53, List 2, bit-reverse reordering
void fft_re_br_core(myComplex *f, int N);  // Butterfly calculation core of above

void fft_nr(myComplex *f, int N);          // Non-recursive calculation, bit-reverse reordering

// DFT function prototype
void dft(myComplex *f, int N);

#endif
