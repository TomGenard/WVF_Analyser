//================================================================
// WAVEFORM (WVF) PEAK ANALYSER
// Finds the maximum point of a signal (waveform)
// 
// Tom Génard - 26.04.2019
//================================================================

#ifndef WVF_PEAK_ANALYSER_H
#define WVF_PEAK_ANALYSER_H
#endif

#include <cstdlib>
#include <vector>

class wvf_peak_analyser {
 public :
  wvf_peak_analyser(std::vector<int>);
  int find_maximum(void);

 private :
  std::vector<int> _waveform_;
  int pulse_maximum;
}
