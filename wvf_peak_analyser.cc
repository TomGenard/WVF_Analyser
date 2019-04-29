//================================================================
// WAVEFORM (WVF) PEAK ANALYSER
// Finds the maximum point of a signal (waveform)
// 
// Tom Génard - 26.04.2019
//================================================================

#include <cstdlib>
#include <iostream>

#include "wvf_peak_analyser.h"

wvf_peak_analyser::wvf_peak_analyser(std::vector<int> waveform) {
  // Constructor
  std::vector<int> _waveform_ = waveform
}

int find_maximum() {
  for ( int i = 0; i < adc_values_array.size(); i++ ) {
    if ( adc_values_array[i] > pulse_maximum ) {
      pulse_maximum = adc_values_array[i];
    }
  }

  return pulse_maximum;
}
