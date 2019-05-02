//================================================================
// VECTOR 2D
// A simple program to create a 2d vector
// 
// Tom Génard - Last Modified : 02.05.2019
//================================================================

#ifndef VECTOR_2D_H
#define VECTOR_2D_H
#endif

#include <cstdlib>
#include <vector>

class vector_2d {
 public :
  vector_2d();
  vector_2d(double, double);
  void add_vector_2d(double, double);
  bool is_initialized(void);
  
  void set_x(double);
  void set_y(double);

  double get_x(void);
  double get_y(void);

 private :
  double _x,_y;
  bool _initialized = false;
};
