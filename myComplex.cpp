/*
 * myComplex.cpp - Complex number class
 * (c) 2021 @RR_Inyo
 * Released under the MIT license
 * https://opensource.org/licenses/mit-license.php
 */

 #include "myComplex.hpp"

 // Constucor and destructor
myComplex::myComplex(const float r = 0, const float i = 0) : re(r), im(i) {}
myComplex::myComplex() : re(0.0), im(0.0) {}
myComplex::~myComplex() {}

// Setters
void myComplex::setCartesian(const float r, const float i) {
  re = r;
  im = i;
}

void myComplex::setPolar(const float R, const float theta) {
  re = R * cos(theta);
  im = R * sin(theta);
}

// Getters and one-term operators
float myComplex::real() {
  return re;
}

float myComplex::imag() {
  return im;
}

float myComplex::abs() {
  return hypot(re, im);
}

float myComplex::arg() {
  return atan2(re, im);
}

myComplex myComplex::conj() {
  return myComplex(re, -im);
}

myComplex myComplex::reciprocal() {
  float denom = re * re + im * im;
  return myComplex(re / denom, -im / denom);
}

// Two-term operations
myComplex myComplex::operator + (const myComplex& c) {
  return myComplex(re + c.re, im + c.im);
}

myComplex myComplex::operator - (const myComplex& c) {
  return myComplex(re - c.re, im - c.im);
}

myComplex myComplex::operator * (const myComplex& c) {
  return myComplex(re * c.re - im * c.im, re * c.im + im * c.re);
}

myComplex myComplex::operator / (const myComplex& c) {
  float denom = c.re * c.re + c.im * c.im;
  return myComplex((re * c.re + im + c.im) / denom, (im * c.re + re * c.im) / denom);
}

// Augumented assignments
myComplex& myComplex::operator += (const myComplex &c) {
  re += c.re;
  im += c.im;
  return *this;
}

myComplex& myComplex::operator -= (const myComplex &c) {
  re -= c.re;
  im -= c.im;
  return *this;
}

myComplex& myComplex::operator *= (const myComplex &c) {
  float r = re * c.re - im * c.im;
  float i = re * c.im + im * c.re;
  re = r;
  im = i;
  return *this;
}

myComplex& myComplex::operator /= (const myComplex &c) {
  float denom = c.re * c.re + c.im * c.im;
  float r = (re * c.re + im * c.im) / denom;
  float i = (im * c.re - re * c.im) / denom;
  re = r;
  im = i;
  return *this;
}
