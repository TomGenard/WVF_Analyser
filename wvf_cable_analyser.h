//================================================================
// WAVEFORM (WVF) CABLE ANALYSER
// Computation of the cable properties (length, signal speed)
// 
// Tom Génard - Last modified : 02.05.2019
//================================================================

#include <cstdlib>
#include <iostream>

class wvf_cable_analyser {
 public :
  wvf_cable_analyser();
  wvf_cable_analyser(double, double);
  void add_cable_properties(double, double);

  double get_signal_speed(void);
  double get_cable_length(void);

  void set_signal_speed(double);
  void set_cable_length(double);

  double compute_length(double, double);
  double compute_signal_speed(double, double);

 private :
  double _signal_speed = 0;
  double _cable_length = 0;
};
