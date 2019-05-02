//================================================================
// VECTOR 2D
// A simple program to create a 2d vector
// 
// Tom Génard - Last Modified : 02.05.2019
//================================================================

#include <cstdlib>
#include <iostream>

#include "vector_2d.h"

vector_2d::vector_2d() {
  return;
}

vector_2d::vector_2d(double x_, double y_) {
  add_vector_2d(x_,y_);
}

void vector_2d::add_vector_2d(double x_, double y_) {
  _x = x_;
  _y = y_;
  _initialized = true;
}

bool vector_2d::is_initialized() {
  return _initialized;
}

// SETTERS

void vector_2d::set_x(double x_) {
  _x = x_;
}

void vector_2d::set_y(double y_) {
  _y = y_;
}

// GETTERS

double vector_2d::get_x() {
  return _x;
}

double vector_2d::get_y() {
  return _y;
}

