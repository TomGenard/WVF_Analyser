//================================================================
// WAVEFORM (WVF) BASELINE ANALYSER
// Compute the mean baseline of the signal (waveform)
// 
// Tom Génard - Last modified : 30.04.2019
//================================================================

#ifndef WVF_BASELINE_ANALYSER_H
#define WVF_BASELINE_ANALYSER_H
#endif

#include <cstdlib>
#include <vector>

class wvf_baseline_analyser {
 public :
  wvf_baseline_analyser();
  wvf_baseline_analyser(std::vector<int>);
  void add_waveform(std::vector<int>);
  bool is_initialized(void);

  /* void print_waveform(void); */
  double compute_baseline(void);
  
 private :
  std::vector<int> _waveform_;
  bool _initialized = false;
};
