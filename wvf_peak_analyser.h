//================================================================
// WAVEFORM (WVF) PEAK ANALYSER
// Finds the maximum point of a signal (waveform)
// 
// Tom Génard - Last Modified : 30.04.2019
//================================================================

#ifndef WVF_PEAK_ANALYSER_H
#define WVF_PEAK_ANALYSER_H
#endif

#include <cstdlib>
#include <vector>
#include "wvf_peak_info.h"

class wvf_peak_analyser {
 public :
  wvf_peak_analyser();
  wvf_peak_analyser(std::vector<int>);
  void add_waveform(std::vector<int>);
  bool is_initialized();

  void remove_baseline(void);
  void find_pulses(void);
  int pulse_global_max_finder(void);
  wvf_peak_info pulse_max_finder(wvf_peak_info);
  void find_all_max(void);
  int get_number_peak(void);
  void print_peak_info(int);
  /* std::vector<wvf_peak_info> find_peaks(void); */

  
 private :
  int pulse_maximum;
  std::vector<int> _waveform_;
  bool _initialized = false;
  wvf_peak_info peak_info;
  std::vector<wvf_peak_info> peaks_array;
};
