/*
   FFT_comparison.ino - Comparison of FFT with/without recursive function and DFT
   (c) 2021 @RR_Inyo
   Released under the MIT license
   https://opensource.org/licenses/mit-license.php
*/

#include <M5Stack.h>
#include <math.h>
#include "myComplex.hpp"
#include "myFFT.hpp"
#include "myPlots.hpp"

// Number of data points
const int NPOINTS = 256;
const int NCOMP = 5;

// Waveform-spectrum data buffer
myComplex f[NPOINTS];

/*
   The setup function
*/
void setup() {
  // Initialize
  M5.begin();
  M5.Power.begin();
  M5.Lcd.setBrightness(160);
}

/*
   The loop function
*/
void loop() {
  // Type of Fourier transform
  static int tFourier = 0;

  // Prepare sample input data
  int h[NCOMP];
  float a[NCOMP], phi[NCOMP];
  if (tFourier == 0) {
    // Random numbers to generate time-domain waveforms, amplitude, harmonic order, phase angle
    for (int i = 0; i < NCOMP; i++) {
      h[i] = random(0, 128);                     // Harmonic order
      a[i] = float(random(0, 90) / 100.0);      // Amplitude
      phi[i] = float(random(-180, 180) / M_PI);  // Phase angle
    }
  }

  // Generate time-domain input data
  for (int i = 0; i < NPOINTS; i++) {
    float re = 0.0;
    for (int j = 0; j < NCOMP; j++) {
      re += a[j] * cos(2 * h[j] * M_PI * i / NPOINTS + phi[j]);
    }
    float im = 0.0;
    f[i].setCartesian(re, im);
  }

  // Plot input waveform
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(32, 2, 2);
  M5.Lcd.print("Time domain");
  plotWaveform(f, NPOINTS);

  // Ticks to store start and finish of Fourier transform
  unsigned long t0, t1;

  // Choose Fourier transform algorithm
  switch (tFourier) {
    case 0:  // DFT
      // Get tick before, perform, and get tick after DFT
      t0 = micros();
      dft(f, NPOINTS);
      t1 = micros() - t0;
      break;

    case 1:  // FFT, recursive, simple
      // Get tick before, perform, and get tick after FFT, recursive
      t0 = micros();
      fft_re(f, NPOINTS);
      t1 = micros() - t0;
      break;

    case 2:  // FFT, recursive, bit-reverse
      // Get tick before, perform, and get tick after FFT, recursive
      t0 = micros();
      fft_re_br(f, NPOINTS);
      t1 = micros() - t0;
      break;

    case 3:  // FFT, non-recursive
      // Get tick before, perform, and get tick after FFT, non-recursive, bit-reverse reordering
      t0 = micros();
      fft_nr(f, NPOINTS);
      t1 = micros() - t0;
      break;
  }

  // Plot output spectrum
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(32, 112, 2);
  M5.Lcd.print("Frequency domain");
  plotSpectrum(f, NPOINTS);

  // Show time to execute Fourier transform
  M5.Lcd.fillRect(32, 221, 256, 18, BLACK);  // Erase previous information
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(32, 221, 1);
  M5.Lcd.printf("%d microsec needed for %d-point", t1, NPOINTS);

  // Show type of Fourier transform
  M5.Lcd.setCursor(32, 230, 1);
  switch (tFourier) {
    case 0:  // DFT
      M5.Lcd.print("Discrete Fourier Transform (DFT).");
      break;

    case 1:  // FFT, recursive, simple reordering
      M5.Lcd.print("FFT, recursive, simple.");
      break;

    case 2:  // FFT, recursive, bit-reverse reordering
      M5.Lcd.print("FFT, recursive, bit-reverse.");
      break;

    case 3:  // FFT, non-recursive, bit-reverse reordering
      M5.Lcd.print("FFT, non-recursive, bit-reverse.");
      break;
  }

  // Choose next algorithm
  tFourier = ++tFourier % 4;

  // Wait
  delay(3000);
}
