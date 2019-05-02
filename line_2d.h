//================================================================
// LINE 2D
// A simple program to create a 2d line
// 
// Tom Génard - Last Modified : 02.05.2019
//================================================================

#ifndef LINE_2D_H
#define LINE_2D_H
#endif

#include <cstdlib>
#include <vector>

#include "vector_2d.h"

class line_2d {
 public :
  line_2d();
  line_2d(vector_2d, vector_2d);
  void add_vertices(vector_2d, vector_2d);
  bool is_initialized(void);

  void set_first_x(double);
  void set_first_y(double);
  void set_second_x(double);
  void set_second_y(double);

  double get_first_x();
  double get_first_y();
  double get_second_x();
  double get_second_y();

  double get_slope();
  double get_origin();
  
 private :
  vector_2d _first_point;
  vector_2d _second_point;
  bool _initialized = false;
};
