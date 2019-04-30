//================================================================
// WAVEFORM (WVF) PEAK ANALYSER
// Finds the maximum point of a signal (waveform)
// 
// Tom Génard - Last Modified : 30.04.2019
//================================================================

#include <cstdlib>
#include <iostream>

#include "wvf_peak_analyser.h"
#include "wvf_baseline_analyser.h"
//#include "wvf_peak_info.h"

// struct peak_info {
//   int pulse_maximum;
//   int pulse_maximum_timestamp;
// };



wvf_peak_analyser::wvf_peak_analyser() {
  return;
}

wvf_peak_analyser::wvf_peak_analyser(std::vector<int> waveform_) {
  // Constructor
  add_waveform(waveform_);
}

void wvf_peak_analyser::add_waveform(std::vector<int> waveform) {
  _waveform_ = waveform;
  _initialized = true;
}

bool wvf_peak_analyser::is_initialized() {
  return  _initialized;
}

void wvf_peak_analyser::remove_baseline() {
  wvf_baseline_analyser baseline_analyser;
  baseline_analyser.add_waveform(_waveform_);

  double pulse_baseline;
  pulse_baseline = baseline_analyser.compute_baseline();
  
  for ( int i = 0; i < _waveform_.size(); i++ ) {
    _waveform_[i] = _waveform_[i] - pulse_baseline;
  }
}


void wvf_peak_analyser::find_pulses() {
  wvf_peak_info peak_info;
  int cursor = 0; // cursor = 0 means that it is searching for the start, cursor = 1 means that it is searching for the end
  int array_cursor = 0;
  int global_max = pulse_global_max_finder();

  for ( int i = 0; i < _waveform_.size(); i++ ) {
    if ( cursor == 0 && _waveform_[i] > 0.1 * global_max ) {
      peak_info.set_pulse_start(i);
      
      cursor = 1;
    }
    
    else if ( cursor == 1 && _waveform_[i] < 0.1 * global_max ) {
      peak_info.set_pulse_end(i);
      
      peaks_array.push_back(peak_info);
      peak_info.reset();
      cursor = 0;
    }
  }
}

int wvf_peak_analyser::pulse_global_max_finder() {
  int global_maximum = -1;

  for ( int i = 0; i < _waveform_.size(); i++) {
    if ( _waveform_[i] > global_maximum ) {
      global_maximum = _waveform_[i];
    }
  }

  return global_maximum;
}

wvf_peak_info wvf_peak_analyser::pulse_max_finder(wvf_peak_info peak_info_) {
  int a_maximum = -1;
  int a_maximum_timestamp = -1;

  for ( int i = peak_info_.get_pulse_start(); i < peak_info_.get_pulse_end(); i++) {
    if ( _waveform_[i] > a_maximum ) {
      a_maximum = _waveform_[i];
      a_maximum_timestamp = i;
    }
  }
  peak_info_.set_pulse_maximum(a_maximum);
  peak_info_.set_pulse_maximum_timestamp(a_maximum_timestamp);

  return peak_info_;
}

void wvf_peak_analyser::find_all_max() {
  wvf_peak_info tmp_peak_info;
  std::cout << "Size : " << peaks_array.size() << std::endl;
  for ( int i = 0; i < peaks_array.size(); i++ ) {
    tmp_peak_info = peaks_array[i];

    tmp_peak_info = pulse_max_finder(tmp_peak_info);

    peaks_array[i] = tmp_peak_info;
  }
}

int wvf_peak_analyser::get_number_peak() {
  return peaks_array.size();
}

void wvf_peak_analyser::print_peak_info(int i_) {
  wvf_peak_info tmp_peak_info;
  tmp_peak_info = peaks_array[i_];
  
  std::cout << "Maximum of the pulse     : " << tmp_peak_info.get_pulse_maximum()           << std::endl;
  std::cout << "Timestamp of the maximum : " << tmp_peak_info.get_pulse_maximum_timestamp() << std::endl;
  std::cout << "Start of the pulse       : " << tmp_peak_info.get_pulse_start()             << std::endl;
  std::cout << "End of the pulse         : " << tmp_peak_info.get_pulse_end()               << std::endl;
}
