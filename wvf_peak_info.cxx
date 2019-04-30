//================================================================
// WAVEFORM (WVF) PEAK INFORMATIONS
// Stores the main characteristics of a pulse, or "peak"
// 
// Tom Génard - Last modified : 30.04.2019
//================================================================

#include <cstdlib>
#include <iostream>

#include "wvf_peak_info.h"

int main(void) {
  wvf_peak_info test_peak;
  
  test_peak.set_pulse_maximum(100);
  test_peak.set_pulse_maximum_timestamp(101);
  test_peak.set_pulse_start(102);
  test_peak.set_pulse_end(103);

  std::cout << test_peak.get_pulse_maximum()           << std::endl;
  std::cout << test_peak.get_pulse_maximum_timestamp() << std::endl;
  std::cout << test_peak.get_pulse_start()             << std::endl;
  std::cout << test_peak.get_pulse_end()               << std::endl;
}
