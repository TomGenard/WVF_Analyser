//================================================================
// WAVEFORM (WVF) CABLE ANALYSER
// Computation of the cable properties (length, signal speed)
// Input/output length in cm and signal speed in cm/ns
// Tom Génard - Last modified : 02.05.2019
//================================================================

#include <cstdlib>
#include <iostream>

#include "wvf_peak_analyser.h"
#include "wvf_cable_analyser.h"

wvf_cable_analyser::wvf_cable_analyser() {
  return;
}

wvf_cable_analyser::wvf_cable_analyser(double signal_speed_, double cable_length) {
  add_cable_properties(signal_speed_, cable_length);
}

void wvf_cable_analyser::add_cable_properties(double signal_speed_, double cable_length) {
  _signal_speed = signal_speed_;
  _cable_length = cable_length;
}

// GETTERS

double wvf_cable_analyser::get_signal_speed() {
  return _signal_speed;
}

double wvf_cable_analyser::get_cable_length() {
  return _cable_length;
}

// SETTERS

void wvf_cable_analyser::set_signal_speed(double signal_speed_) {
  _signal_speed  = signal_speed_;
}

void wvf_cable_analyser::set_cable_length(double cable_length) {
  _cable_length = cable_length;
}

// COMPUTATIONS

double wvf_cable_analyser::compute_length(double travel_time_, double length_time_step_) {
  // travel_time_ in number of steps, length_time_step in ns
  double travel_length = 0;
  travel_length = get_signal_speed() * ( travel_time_ * length_time_step_ );
  
  return travel_length;
}

double wvf_cable_analyser::compute_signal_speed(double travel_time_, double length_time_step_) {
  double signal_speed = 0;
  signal_speed = ( get_cable_length() * 2 ) / ( travel_time_ * length_time_step_ );
  
  return signal_speed;
}
