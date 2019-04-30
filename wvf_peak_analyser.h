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

  
struct peak_info {
  int pulse_maximum;
  int pulse_maximum_timestamp;
};



class wvf_peak_analyser {
 public :
  wvf_peak_analyser();
  wvf_peak_analyser(std::vector<int>);


  peak_info pulse_max_finder();
  

  
  peak_info find_first_peak(void);
  std::vector<peak_info> find_peaks(void);

  void add_waveform(std::vector<int>);
  bool is_initialized();

  
 private :
  int pulse_maximum;
  std::vector<int> _waveform_;
  bool _initialized = false;


};
