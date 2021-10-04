/*
 * myPlots.cpp - Time- and frequency-domain plots
 * (c) 2021 @RR_Inyo
 * Released under the MIT license
 * https://opensource.org/licenses/mit-license.php
 */

#include "myPlots.hpp"

// Plot waveform, show only real part
void plotWaveform(myComplex *f, int N) {
  // Frame coordinates
  const int X0 = 31;
  const int Y0 = 19;
  const int W = 256;
  const int H = 90;

  // Waveform color
  const int colBG = BLACK;
  const int colFrame = DARKGREY;
  const int colPlot = YELLOW;

  // Draw frame and clear old waveform
  M5.Lcd.fillRect(X0, Y0, W, H, colBG);
  M5.Lcd.drawRect(X0 - 1, Y0 - 1, W + 2, H + 2 , colFrame);

  // Plot first point
  int x = X0;
  int y = Y0 + constrain(map(int(1000 * f[0].real()), -2500, 2500, H, 0), 0, H);
  M5.Lcd.drawPixel(x, y, colPlot);
  int x_old = x;
  int y_old = y;

  // Plot second point and rest
  for (int k = 1; k < N; k++) {
    x = X0 + k;
    y = Y0 + constrain(map(int(1000 * f[k].real()), -2500, 2500, H, 0), 0, H);
    M5.Lcd.drawLine(x_old, y_old, x, y, colPlot);
    x_old = x;
    y_old = y;
  }
}

// Plot spectrum, show absolute value
void plotSpectrum(myComplex *f, int N) {
  // Frame coordinates
  const int X0 = 31;
  const int Y0 = 129;
  const int W = 256;
  const int H = 90;

  // Waveform color
  const int colBG = BLACK;
  const int colFrame = DARKGREY;
  const int colBar = CYAN;

  // Draw frame and clear old waveform
  M5.Lcd.fillRect(X0, Y0, W, H, colBG);
  M5.Lcd.drawRect(X0 - 1, Y0 - 1, W + 2, H + 2, colFrame);

  // Plot bar graph
  for (int k = 0; k < N / 2; k++) {
    int x = X0 + k * 2;
    int y = constrain(map(int(f[k].abs()), 0, N / 2, 0, H), 0 , H);
    M5.Lcd.drawFastVLine(x, Y0 + H - y, y, colBar);
    M5.Lcd.drawFastVLine(x + 1, Y0 + H - y, y, colBar);
  }
}
