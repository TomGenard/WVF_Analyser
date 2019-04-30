//================================================================
// WAVEFORM (WVF) PEAK ANALYSER
// Finds the maximum point of a signal (waveform)
// 
// Tom Génard - Last Modified : 30.04.2019
//================================================================

#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>

#include "wvf_peak_analyser.h"

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

  wvf_peak_analyser analyser(adc_values_array);
  
}
