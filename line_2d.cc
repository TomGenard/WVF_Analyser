//================================================================
// LINE 2D
// A simple program to create a 2d line
// 
// Tom Génard - Last Modified : 02.05.2019
//================================================================

#include <cstdlib>
#include <iostream>

//#include "vector_2d.h"
#include "line_2d.h"

line_2d::line_2d() {
  return;
}

line_2d::line_2d(vector_2d first_point_, vector_2d second_point_) {
  add_vertices(first_point_, second_point_);
}

void line_2d::add_vertices(vector_2d first_point_, vector_2d second_point_) {
  _first_point = first_point_;
  _second_point = second_point_;
  _initialized = true;
}

bool line_2d::is_initialized() {
  return _initialized;
}

// SETTERS

void line_2d::set_first_x(double x_) {
  _first_point.set_x(x_);
}

void line_2d::set_first_y(double y_) {
  _first_point.set_y(y_);
}

void line_2d::set_second_x(double x_) {
  _second_point.set_x(x_);
}

void line_2d::set_second_y(double y_) {
  _second_point.set_y(y_);
}

// GETTERS

double line_2d::get_first_x() {
  return _first_point.get_x();
}

double line_2d::get_first_y() {
  return _first_point.get_y();
}

double line_2d::get_second_x() {
  return _second_point.get_x();
}

double line_2d::get_second_y() {
  return _second_point.get_y();
}

// COMPUTATIONS

double line_2d::get_slope() {
  double a;

  a = ( get_second_y() - get_first_y() ) / ( get_second_x() - get_first_x() );
  
  return a;
}

double line_2d::get_origin() {
  double b;

  b = ( get_first_y() - ( get_slope() * get_first_x() ) );
  
  return b;
}
