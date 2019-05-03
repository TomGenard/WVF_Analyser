//================================================================
// SAVITZKY-GOLAY (SG) CONVOLUTION ALGORITHM
// Smoothens a waveform using the Savitzky-Golay algorithm
// 
// Tom Génard - Last modified : 03.05.2019
//================================================================

#include <cstdlib>
#include <iostream>
#include <vector>

#include "sg_convolution_algorithm.h"

sg_convolution_algorithm::sg_convolution_algorithm(){
  return;
}

sg_convolution_algorithm::sg_convolution_algorithm(std::vector<double> curve_){
  add_curve(curve_);
}

void sg_convolution_algorithm::add_curve(std::vector<double> curve_) {
  _curve = curve_;
}

std::vector<double> sg_convolution_algorithm::smoothen_5_factors() {
  _smooth_curve.clear();

  for ( int i = 0; i < 2; i++ ) {
    _smooth_curve.push_back(_curve[i]);
  }
  for ( int i = 2; i < ( _curve.size() - 2 ); i++ ) {
    _smooth_curve.push_back( ( -3 * _curve[i-2] + 12 * _curve[i-1] + 17 * _curve[i] + 12 * _curve[i+1] + -3 * _curve[i+2] ) / 35. );
  }
  for ( int i = ( _curve.size() - 2 ); i < _curve.size(); i++ ) {
    _smooth_curve.push_back(_curve[i]);
  }

  return _smooth_curve;
}

std::vector<double> sg_convolution_algorithm::smoothen_7_factors() {
  _smooth_curve.clear();
  std::cout << _smooth_curve.size() << std::endl;

  for ( int i = 0; i < 3; i++ ) {
    _smooth_curve.push_back(_curve[i]);
  }
  for ( int i = 3; i < ( _curve.size() - 3 ); i++ ) {
    _smooth_curve.push_back( ( -2 * _curve[i-3] + 3 * _curve[i-2] + 6 * _curve[i-1] + 7 * _curve[i] + 6 * _curve[i+1] + 3 * _curve[i+2] + -2 * _curve[i+3] ) / 21. );
  }
  for ( int i = ( _curve.size() - 3 ); i < _curve.size(); i++ ) {
    _smooth_curve.push_back(_curve[i]);
  }

  return _smooth_curve;
}

std::vector<double> sg_convolution_algorithm::smoothen_9_factors() {
  _smooth_curve.clear();

  for ( int i = 0; i < 4; i++ ) {
    _smooth_curve.push_back(_curve[i]);
  }
  for ( int i = 4; i < ( _curve.size() - 4 ); i++ ) {
    _smooth_curve.push_back( ( -21 * _curve[i-4] + 14 * _curve[i-3] + 39 * _curve[i-2] + 54 * _curve[i-1] + 59 * _curve[i] + 54 * _curve[i+1] + 39 * _curve[i+2] + 14 * _curve[i+3] + -21 * _curve[i+4] ) / 231. );
  }
  for ( int i = ( _curve.size() - 4 ); i < _curve.size(); i++ ) {
    _smooth_curve.push_back(_curve[i]);
  }

  return _smooth_curve;
}

std::vector<double> sg_convolution_algorithm::smoothen_11_factors() {
  _smooth_curve.clear();

  for ( int i = 0; i < 5; i++ ) {
    _smooth_curve.push_back(_curve[i]);
  }
  for ( int i = 5; i < ( _curve.size() - 5 ); i++ ) {
    _smooth_curve.push_back( ( -36 * _curve[i-5] + 9 * _curve[i-4] + 44 * _curve[i-3] + 69 * _curve[i-2] + 84 * _curve[i-1] + 89 * _curve[i] + 84 * _curve[i+1] + 69 * _curve[i+2] + 44 * _curve[i+3] + 9 * _curve[i+4] + -36 * _curve[i+5] ) / 429. );
  }
  for ( int i = ( _curve.size() - 5 ); i < _curve.size(); i++ ) {
    _smooth_curve.push_back(_curve[i]);
  }

  return _smooth_curve;
}

std::vector<double> sg_convolution_algorithm::smoothen_13_factors() {
  _smooth_curve.clear();

  for ( int i = 0; i < 6; i++ ) {
    _smooth_curve.push_back(_curve[i]);
  }
  for ( int i = 6; i < ( _curve.size() - 6 ); i++ ) {
    _smooth_curve.push_back( ( -11 * _curve[i-6] + 0 * _curve[i-5] + 9 * _curve[i-4] + 16 * _curve[i-3] + 21 * _curve[i-2] + 24 * _curve[i-1] + 25 * _curve[i] + 24 * _curve[i+1] + 21 * _curve[i+2] + 16 * _curve[i+3] + 9 * _curve[i+4] + 0 * _curve[i+5] + -11 * _curve[i+6] ) / 143. );
  }
  for ( int i = ( _curve.size() - 6 ); i < _curve.size(); i++ ) {
    _smooth_curve.push_back(_curve[i]);
  }

  return _smooth_curve;
}

std::vector<double> sg_convolution_algorithm::smoothen_15_factors() {
  _smooth_curve.clear();
  
  for ( int i = 0; i < 7; i++ ) {
    _smooth_curve.push_back(_curve[i]);
  }
  for ( int i = 7; i < ( _curve.size() - 7 ); i++ ) {
    _smooth_curve.push_back( ( -78 * _curve[i-7] + -13 * _curve[i-6] + 42 * _curve[i-5] + 87 * _curve[i-4] + 122 * _curve[i-3] + 147 * _curve[i-2] + 162 * _curve[i-1] + 167 * _curve[i] + 162 * _curve[i+1] + 147 * _curve[i+2] + 122 * _curve[i+3] + 87 * _curve[i+4] + 42 * _curve[i+5] + -13 * _curve[i+6] + -78 * _curve[i+7] ) / 1105. );
  }
  for ( int i = ( _curve.size() - 7 ); i < _curve.size(); i++ ) {
    _smooth_curve.push_back(_curve[i]);
  }

  return _smooth_curve;
}

// std::vector<double> sg_convolution_algorithm::smoothen_17_factors() {

// }

// std::vector<double> sg_convolution_algorithm::smoothen_19_factors() {

// }

// std::vector<double> sg_convolution_algorithm::smoothen_21_factors() {

// }

// std::vector<double> sg_convolution_algorithm::smoothen_23_factors() {

// }

// std::vector<double> sg_convolution_algorithm::smoothen_25_factors() {

// }
