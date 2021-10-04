/*
 * myFFT.cpp - Fast Fourier Transform (FFT)
 * Based on Interface Magazine, CQ Publishing, Sep. 2021, p. 53, List 1
 * Ported to C++ using myComplex class
 * (c) 2021 @RR_Inyo
 * Released under the MIT license
 * https://opensource.org/licenses/mit-license.php
 */

#include "myFFT.hpp"

// Fast Fourier Transform (FFT), recursive
// Ported from Interface Magazine, CQ Publishing, Sep. 2021, p. 53, List 1
// Through my porting to Python
void fft_re(myComplex *f, int N) {
  if (N > 1) {
    int n = N / 2;
    for (int i = 0; i < n; i++) {
      // Prepare complex sinusoid, rotation operator
      myComplex W(cos(2 * M_PI * i / N), -sin(2 * M_PI * i / N));
      
      myComplex f_tmp = f[i] - f[n + i];
      f[i] += f[n + i];
      f[n + i] = W * f_tmp;
    }

    // Recursively call this function
    fft_re(&f[0], n);  // First half
    fft_re(&f[n], n);  // Second half

    // Reorder back again, simple method
    myComplex y[N];
    for (int i = 0; i < n; i++) {
      y[2 * i] = f[i];
      y[2 * i + 1] = f[n + i];
    }
    for (int i = 0; i < N; i++) {
      f[i] = y[i];
    }
  }
}

// Fast Fourier Transform (FFT), recursive, bit-reverse
// Ported from Interface Magazine, CQ Publishing, Sep. 2021, p. 53, List 2
// Through my porting to Python
void fft_re_br(myComplex *f, int N) {
  fft_re_br_core(f, N);

  // Bit-reverse reordering
  int i = 0;
  for (int j = 1; j < N - 1; j++) {
    for (int k = N >> 1; k > (i ^= k); k >>= 1);
    if (j < i) {
      myComplex f_tmp = f[j];
      f[j] = f[i];
      f[i] = f_tmp;
    }
  }
}

void fft_re_br_core(myComplex *f, int N) {
  if (N > 1) {
    int n = N / 2;
    for (int i = 0; i < n; i++) {
      // Prepare complex sinusoid, rotation operator
      myComplex W(cos(2 * M_PI * i / N), -sin(2 * M_PI * i / N));
      
      myComplex f_tmp = f[i] - f[n + i];
      f[i] += f[n + i];
      f[n + i] = W * f_tmp;
    }

    // Recursively call this function
    fft_re_br_core(&f[0], n);  // First half
    fft_re_br_core(&f[n], n);  // Second half
  }
}

// Fast Fourier Transform (FFT), non-recursive, bit-reverse reordering
// Ported from my code in Python
void fft_nr(myComplex *f, int N) {
  // Calculate number of data divisions
  int p = int(log2(N));

  // FFT core calculation
  for (int i = 0; i < p; i++) {
    int n = N / int(pow(2, i + 1));
    for (int j = 0; j < int(pow(2, i)); j++) {
      // Butterfly computation
      for (int k = 0; k < n; k++) {
        // Prepare complex sinusoid, rotation operator
        myComplex W(cos(2 * M_PI * k / (2 * n)), -sin(2 * M_PI * k / (2 * n)));

        // Do Butterfly computation
        myComplex f_tmp = f[n * 2 * j + k] - f[n * (2 * j + 1) + k];
        f[n * 2 * j  + k] = f[n * 2 * j  + k] + f[n * (2 * j + 1) + k];
        f[n * (2 * j + 1) + k] = W * f_tmp;
      }
    }
  }

  // Bit-reverse reordering
  int i = 0;
  for (int j = 1; j < N - 1; j++) {
    for (int k = N >> 1; k > (i ^= k); k >>= 1);
    if (j < i) {
      myComplex f_tmp = f[j];
      f[j] = f[i];
      f[i] = f_tmp;
    }
  }
}

// Discrete Fourier Transform (DFT), straight-forward
void dft(myComplex *f, int N) {
  // Declare myComplex array to store output, cleared with 0 + j0 as written in constructor
  myComplex y[N];

  // Direct calculation of Fourier coefficients
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      // Prepare complex sinusoid, rotation operator
      myComplex W(cos(2 * M_PI * i * j / N), -sin(2 * M_PI * i * j / N));

      // Perform multiply-accumulate operation
      y[i] += W * f[j];
    }
  }

  // Overwrite input with output
  for (int i = 0; i < N; i++) {
    f[i] = y[i];
  }
}
