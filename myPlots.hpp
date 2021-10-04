/*
 * myPlots.hpp - Time- and frequency-domain plots
 * (c) 2021 @RR_Inyo
 * Released under the MIT license
 * https://opensource.org/licenses/mit-license.php
 */

#ifndef _MYPLOTS_
#define _MYPLOTS_

#include <M5Stack.h>
#include "myComplex.hpp"

// Plotting function prototypes
void plotWaveform(myComplex *f, int N);
void plotSpectrum(myComplex *F, int N);

#endif
