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
#include "line_2d.h"
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
  int global_max = find_pulse_global_max();
  double fitted_time = 0;
  double a = 0, b = 0;
 
  for ( int i = 0; i < _waveform_.size(); i++ ) {
    if ( cursor == 0 && _waveform_[i] > 0.1 * global_max ) {
      // We use a linear fit, y = ax + b
      // _waveform_[i]   is the current value, past the researched point
      // _waveform_[i-1] is the past value, just before the researched point

      a = ( ( _waveform_[i] - _waveform_[i-1] ) / ( i - ( i-1 ) ) );
      b = _waveform_[i] - ( a * i );

      fitted_time = ( 0.1 * global_max - b ) / a;

      peak_info.set_pulse_start(fitted_time);
      
      cursor = 1;
    }
    
    else if ( cursor == 1 && _waveform_[i] < 0.1 * global_max ) {
      a = ( ( _waveform_[i] - _waveform_[i-1] ) / ( i - ( i-1 ) ) );
      b = _waveform_[i] - ( a * i );

      fitted_time = ( 0.1 * global_max - b ) / a;

      peak_info.set_pulse_end(fitted_time);
      
      peaks_array.push_back(peak_info);
      peak_info.reset();
      cursor = 0;
    }
  }
}

int wvf_peak_analyser::find_pulse_global_max() {
  int global_maximum = -1;

  for ( int i = 0; i < _waveform_.size(); i++) {
    if ( _waveform_[i] > global_maximum ) {
      global_maximum = _waveform_[i];
    }
  }

  return global_maximum;
}

wvf_peak_info wvf_peak_analyser::find_pulse_max(wvf_peak_info peak_info_) {
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

wvf_peak_info wvf_peak_analyser::find_square_pulse_max(wvf_peak_info peak_info_) {
  // Here, we'll do an interpolation of two lines, defined by the rising slope and the plateau of the suare signal
  // We use two line_2d for that, each defined by two vector_2d that determine their verticies
  // The computation of the crosspoint is made here, but the lines slopes and origin point are calculated in the line_2d class

  double a_maximum = -1;
  double a_maximum_timestamp = -1;

  int time_start, time_end;
  int total_time;
  
  int rising_start, rising_end;
  int rising_start_value, rising_end_value;
  int plateau_start, plateau_end;
  int plateau_start_value, plateau_end_value;
  
  time_start = peak_info_.get_pulse_start();
  time_end   = peak_info_.get_pulse_end();

  total_time = time_end - time_start;

  rising_start       = (int) ( 0.00 * total_time ) + time_start;
  rising_start_value = _waveform_[rising_start];
  rising_end         = (int) ( 0.1 * total_time ) + time_start;
  rising_end_value   = _waveform_[rising_end];

  plateau_start       = (int) ( 0.5 * total_time ) + time_start;
  plateau_start_value = _waveform_[plateau_start];
  plateau_end         = (int) ( 0.85 * total_time ) + time_start;
  plateau_end_value   = _waveform_[plateau_end];

  vector_2d vector_1;
  vector_1.add_vector_2d(rising_start, rising_start_value);
  vector_2d vector_2;
  vector_2.add_vector_2d(rising_end, rising_end_value);
  vector_2d vector_3;
  vector_3.add_vector_2d(plateau_start, plateau_start_value);
  vector_2d vector_4;
  vector_4.add_vector_2d(plateau_end, plateau_end_value);
  
  line_2d line_2d_first(vector_1,vector_2);
  line_2d line_2d_second(vector_3,vector_4);

  a_maximum_timestamp = ( line_2d_second.get_origin() - line_2d_first.get_origin() ) / ( line_2d_first.get_slope() - line_2d_second.get_slope() );
  a_maximum = ( line_2d_first.get_slope() * a_maximum_timestamp ) + line_2d_first.get_origin();
  
  peak_info_.set_pulse_maximum(a_maximum);
  peak_info_.set_pulse_maximum_timestamp(a_maximum_timestamp);

  return peak_info_;
}

// double wvf_peak_analyser::find_square_pulse_start(wvf_peak_info peak_info_) {
//   // Here, we'll do an interpolation of two lines, defined by the rising slope and the baseline of the signal
//   // We use two line_2d for that, each defined by two vector_2d that determine their verticies
//   // The computation of the crosspoint is made here, but the lines slopes and origin point are calculated in the line_2d class

//   double a_pulse_start = -1;

//   int time_start, time_end;
//   int total_time;
  
//   int rising_start, rising_end;
//   int rising_start_value, rising_end_value;
//   int baseline_start, baseline_end;
//   int baseline_start_value, baseline_end_value;
  
//   time_start = peak_info_.get_pulse_start();
//   time_end   = peak_info_.get_pulse_end();

//   total_time = time_end - time_start;

//   rising_start       = (int) ( 0.00 * total_time ) + time_start;
//   rising_start_value = _waveform_[rising_start];
//   rising_end         = (int) ( 0.1 * total_time ) + time_start;
//   rising_end_value   = _waveform_[rising_end];
  
//   wvf_baseline_analyser baseline_analyser;
//   baseline_analyser.add_waveform(_waveform_);

//   double pulse_baseline;
//   pulse_baseline = baseline_analyser.compute_baseline();
  
//   baseline_start       = time_start - 100;
//   baseline_start_value = pulse_baseline;
//   baseline_end         = time_start - 50;
//   baseline_end_value   = pulse_baseline;
  
//   vector_2d vector_1;
//   vector_1.add_vector_2d(rising_start, rising_start_value);
//   vector_2d vector_2;
//   vector_2.add_vector_2d(rising_end, rising_end_value);
//   vector_2d vector_3;
//   vector_3.add_vector_2d(baseline_start, baseline_start_value);
//   vector_2d vector_4;
//   vector_4.add_vector_2d(baseline_end, baseline_end_value);
  
//   line_2d line_2d_first(vector_1,vector_2);
//   line_2d line_2d_second(vector_3,vector_4);

//   a_pulse_start = ( line_2d_second.get_origin() - line_2d_first.get_origin() ) / ( line_2d_first.get_slope() - line_2d_second.get_slope() );

//   return a_pulse_start;
// }

void wvf_peak_analyser::find_all_max() {
  wvf_peak_info tmp_peak_info;

  // The first peak is a square signal, thus it requires a special treatment

  tmp_peak_info = peaks_array[0];
  tmp_peak_info = find_square_pulse_max(tmp_peak_info);
  peaks_array[0] = tmp_peak_info;

  // The rest of the peaks
  
  for ( int i = 1; i < peaks_array.size(); i++ ) {
    tmp_peak_info = peaks_array[i];
    tmp_peak_info = find_pulse_max(tmp_peak_info);
    peaks_array[i] = tmp_peak_info;
  }
}

int wvf_peak_analyser::get_number_peak() {
  return peaks_array.size();
}

wvf_peak_info wvf_peak_analyser::get_peak_info(int i_) {
  return peaks_array[i_];
}

void wvf_peak_analyser::print_peak_info(int i_) {
  wvf_peak_info tmp_peak_info;
  tmp_peak_info = peaks_array[i_];
  
  std::cout << "Maximum of the pulse     : " << tmp_peak_info.get_pulse_maximum()                               << std::endl;
  std::cout << "Timestamp of the maximum : " << tmp_peak_info.get_pulse_maximum_timestamp()                     << std::endl;
  std::cout << "Start of the pulse       : " << tmp_peak_info.get_pulse_start()                                 << std::endl;
  std::cout << "End of the pulse         : " << tmp_peak_info.get_pulse_end()                                   << std::endl;
  std::cout << "Total pulse time         : " << tmp_peak_info.get_pulse_end() - tmp_peak_info.get_pulse_start() << std::endl;
}
