/*
 * myComplex.hpp - Complex number class
 * (c) 2021 @RR_Inyo
 * Released under the MIT license
 * https://opensource.org/licenses/mit-license.php
 */

#ifndef _MYCOMPLEX_
#define _MYCOMPLEX_

#include <math.h>

 // Complex number class
class myComplex {
  public:
    // Constructor and desctructor
    myComplex(float r, float i);
    myComplex();
    ~myComplex();

    // Setters
    void setCartesian(const float r, const float i);
    void setPolar(const float R, const float theta);

    // Single-term operations
    float real();
    float imag();
    float abs();
    float arg();
    myComplex conj();
    myComplex reciprocal();

    // Negation
    myComplex operator - ();    

    // Two-term operations
    myComplex operator + (const myComplex&);
    myComplex operator - (const myComplex&);
    myComplex operator * (const myComplex&);
    myComplex operator / (const myComplex&);

    // Augumented assignments
    myComplex& operator += (const myComplex&);
    myComplex& operator -= (const myComplex&);
    myComplex& operator *= (const myComplex&);
    myComplex& operator /= (const myComplex&);

  protected:
    float re;
    float im;
};

#endif
