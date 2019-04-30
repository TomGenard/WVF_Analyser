//================================================================
// WAVEFORM (WVF) BASELINE ANALYSER
// Compute the mean baseline of the signal (waveform)
// 
// Tom Génard - Last modified : 30.04.2019
//================================================================

#include <cstdlib>
#include <iostream>

#include "wvf_baseline_analyser.h"

wvf_baseline_analyser::wvf_baseline_analyser() {
  // Empty constructor
}

wvf_baseline_analyser::wvf_baseline_analyser(std::vector<int> waveform_) {
  // Constructor
  add_waveform(waveform_);
}

void wvf_baseline_analyser::add_waveform(std::vector<int> waveform_) {
  // Constructor
  _waveform_ = waveform_;
  _initialized = true;
}

bool wvf_baseline_analyser::is_initialized(){
  return  _initialized;
}

void wvf_baseline_analyser::print_waveform() {
  std::cout << "Size : " << _waveform_.size() << std::endl;
  for ( int i = 0; i < _waveform_.size(); i++ ) {
    std::cout << _waveform_[i] << " ";
  }
  std::cout << std::endl;
}

double wvf_baseline_analyser::compute_baseline() {
  double pulse_baseline = -1;
  
  for ( int i = 0; i < _waveform_.size(); i++ ) {
    if ( i < 100 ) {
      pulse_baseline += _waveform_[i];
    }
  }
  pulse_baseline = pulse_baseline/100; // Mean of the 100 first values
  
  return pulse_baseline;
}
