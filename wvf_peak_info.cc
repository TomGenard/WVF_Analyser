//================================================================
// WAVEFORM (WVF) PEAK INFORMATIONS
// Stores the main characteristics of a pulse, or "peak"
// 
// Tom Génard - Last modified : 30.04.2019
//================================================================

#include <cstdlib>
#include <iostream>

#include "wvf_peak_info.h"

wvf_peak_info::wvf_peak_info() {
  // Empty constructor
}

wvf_peak_info::wvf_peak_info(int pulse_maximum_, int pulse_maximum_timestamp_, int pulse_start_, int pulse_end_) {
  set_pulse_maximum(pulse_maximum_);
  set_pulse_maximum_timestamp(pulse_maximum_timestamp_);
  set_pulse_start(pulse_start_);
  set_pulse_end(pulse_end_);
}

// SETTERS

void wvf_peak_info::set_pulse_maximum(int pulse_maximum_) {
  _pulse_maximum = pulse_maximum_;
  _info_validated = false;
}

void wvf_peak_info::set_pulse_maximum_timestamp(int pulse_maximum_timestamp_) {
  _pulse_maximum_timestamp = pulse_maximum_timestamp_;
  _info_validated = false;
}

void wvf_peak_info::set_pulse_start(int pulse_start_) {
  _pulse_start = pulse_start_;
  _info_validated = false;
}

void wvf_peak_info::set_pulse_end(int pulse_end_) {
  _pulse_end = pulse_end_;
  _info_validated = false;
}

// GETTERS

int wvf_peak_info::get_pulse_maximum() {
  return _pulse_maximum;
}

int wvf_peak_info::get_pulse_maximum_timestamp() {
  return _pulse_maximum_timestamp;
}

int wvf_peak_info::get_pulse_start() {
  return _pulse_start;
}

int wvf_peak_info::get_pulse_end() {
  return _pulse_end;
}

// RESET

void wvf_peak_info::reset() {
  set_pulse_maximum(0); 
  set_pulse_maximum_timestamp(0);
  set_pulse_start(0);
  set_pulse_end(0);
}

// VERIFICATOR

void wvf_peak_info::verify_values() {
  if ( _pulse_start < _pulse_end ) {
    std::cerr << "ERROR : Start time is after end time" << std::endl;
    exit(1);
  }

  if ( _pulse_maximum < 0 ) {
    std::cerr << "ERROR : Pulse maximum is negative" << std::endl;
    exit(1);
  }

  if ( _pulse_maximum_timestamp < 0 ) {
    std::cerr << "ERROR : Timestamp of the pulse maximum is negative" << std::endl;
    exit(1);
  }

  if ( _pulse_start < 0 ) {
    std::cerr << "ERROR : Start time is negative" << std::endl;
    exit(1);
  }

  if ( _pulse_end < 0 ) {
    std::cerr << "ERROR : End time is negative" << std::endl;
    exit(1);
  }

  if ( _pulse_maximum > 4096 ) {
    std::cerr << "ERROR : Maximum value is above expected parameters" << std::endl;
    exit(1);
  }

  if ( _pulse_maximum_timestamp > 1024 ) {
    std::cerr << "ERROR : Timestamp is above the number of maximum timestep" << std::endl;
    exit(1);
  }
  
  if ( _pulse_start > 1024 ) {
    std::cerr << "ERROR : Start time is above the number of maximum timestep" << std::endl;
    exit(1);
  }

  if ( _pulse_end > 1024 ) {
    std::cerr << "ERROR : End time is above the number of maximum timestep" << std::endl;
    exit(1);
  }
  
  _info_validated = true;
}
