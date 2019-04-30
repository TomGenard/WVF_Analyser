//================================================================
// WAVEFORM (WVF) BASELINE ANALYSER
// Compute the mean baseline of the signal (waveform)
// 
// Tom Génard - Last modified : 30.04.2019
//================================================================

#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>

#include "wvf_baseline_analyser.h"

int main(void) {
  std::vector<int> adc_values_array;
  int adc_value = -1;
  
  std::ifstream inFile;
  std::string file_path;
  file_path = "wvf.data";
  
  std::ofstream myfile;
  inFile.open(file_path.c_str());
  while (inFile >> adc_value) {
    adc_values_array.push_back(adc_value);
  }
  inFile.close();

  wvf_baseline_analyser baseline;
  baseline.add_waveform(adc_values_array);
  
  double pulse_baseline;
  //baseline.print_waveform();
  pulse_baseline = baseline.compute_baseline();
  std::cout << "The pulse baseline of this signal is : " << pulse_baseline << std::endl;
}
