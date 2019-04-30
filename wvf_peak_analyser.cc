//================================================================
// WAVEFORM (WVF) PEAK ANALYSER
// Finds the maximum point of a signal (waveform)
// 
// Tom Génard - Last Modified : 30.04.2019
//================================================================

#include <cstdlib>
#include <iostream>

#include "wvf_peak_analyser.h"


// struct peak_info {
//   int pulse_maximum;
//   int pulse_maximum_timestamp;
// };



wvf_peak_analyser::wvf_peak_analyser(){

  return;
}

wvf_peak_analyser::wvf_peak_analyser(std::vector<int> waveform_) {
  // Constructor
  add_waveform(waveform_);
}



void wvf_peak_analyser::add_waveform(std::vector<int> waveform){
  std::vector<int> _waveform_ = waveform;
  _initialized = true;
}


bool wvf_peak_analyser::is_initialized(){
  return  _initialized;
}



peak_info wvf_peak_analyser::pulse_max_finder(){
  int a_maximum = -1;
  int a_maximum_timestamp = -1;
  
  for ( int i = 0; i < _waveform_.size(); i++) {
    if ( _waveform_[i] > pulse_maximum ) {
      a_maximum = _waveform_[i];
      a_maximum_timestamp = i;
    }
  }
  peak_info peak_1_info;
  peak_1_info.pulse_maximum =a_maximum;
  peak_1_info.pulse_maximum_timestamp = a_maximum_timestamp;


  return peak_1_info;
  
}


peak_info wvf_peak_analyser::find_first_peak() {
 

//   pulse_maximum = 0;
//   for ( int i = pulse_maximum_timestamp; i < ( pulse_maximum_timestamp + 25 ); i++ ) {
//     pulse_maximum = pulse_maximum + _waveform_[i];
//   }
  
//   pulse_maximum = pulse_maximum / 25.;

  peak_info peak_1_info;

//   peak_1_info.pulse_maximum = pulse_maximum;
//   peak_1_info.pulse_maximum_timestamp = pulse_maximum_timestamp;

  return peak_1_info;
}

std::vector<peak_info> wvf_peak_analyser::find_peaks() {
  peak_info peak_1_info;
  peak_info peak_2_info;

  peak_1_info = find_first_peak();
  
  int pulse_maximum = -1;
  int pulse_maximum_timestamp = -1;
  
  for ( int i = ( peak_1_info.pulse_maximum_timestamp + 100 ); i < _waveform_.size(); i++ ) { // The first signal takes way less than 100 timesteps to return to the baseline
    if ( _waveform_[i] > pulse_maximum ) {
      pulse_maximum = _waveform_[i];
      pulse_maximum_timestamp = i;
    }
  }

  peak_2_info.pulse_maximum = pulse_maximum;
  peak_2_info.pulse_maximum_timestamp = pulse_maximum_timestamp;

  std::vector<peak_info> peaks_info;

  peaks_info.push_back(peak_1_info);
  peaks_info.push_back(peak_2_info);

  return peaks_info;
}
