//================================================================
// WAVEFORM (WVF) CABLE ANALYSER
// Computation of the cable properties (length, signal speed)
// 
// Tom Génard - Last modified : 02.05.2019
//================================================================

#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>

#include "wvf_peak_analyser.h"
#include "wvf_cable_analyser.h"

int main(void) {
  std::vector<int> adc_values_array;
  std::ifstream inFile;
  int adc_value = -1;
  
  std::string file_path;
  //file_path = "wvf.data";
  std::cout << "Insert file path :" << std::endl;
  std::cin >> file_path;
  
  std::ofstream myfile;
  inFile.open(file_path.c_str());
  while (inFile >> adc_value) {
    adc_values_array.push_back(adc_value);
  }
  inFile.close();

  wvf_peak_analyser analyser;
  analyser.add_waveform(adc_values_array);
  analyser.remove_baseline();
  analyser.find_pulses();
  analyser.find_all_max();

  double cable_length = 698;      // In cm
  double time_step    = 0.390625; // In ns
  double signal_speed = 0;        // In cm/ns
  double travel_time  = 0;        // In steps
  wvf_cable_analyser cable_analyser;
  wvf_peak_info current_peak_info, ref_peak_info;
  std::ofstream data_file;
  
  data_file.open("peak_data.data");
  for ( int i = 0; i < analyser.get_number_peak() ; i++) {
    std::cout << "===== PEAK N°" << i << " =====" << std::endl;
    analyser.print_peak_info(i);
    current_peak_info = analyser.get_peak_info(i);
    data_file << i << " " << current_peak_info.get_pulse_start() << " " << current_peak_info.get_pulse_end() << " " << current_peak_info.get_pulse_maximum() << " " << current_peak_info.get_pulse_maximum_timestamp() << "\n";
    
    if ( i > 0 ) {
      ref_peak_info = analyser.get_peak_info(0);
      
      travel_time = current_peak_info.get_pulse_start() - ref_peak_info.get_pulse_start();
      std::cout << "     =======" << std::endl;
      std::cout << "Time between this pulse and the original pulse : " << travel_time << std::endl;
      
      cable_analyser.set_cable_length(cable_length);
      signal_speed = cable_analyser.compute_signal_speed(travel_time, time_step);
      std::cout << "Signal speed : " << signal_speed << std::endl;
    }
  }
  data_file.close();
  std::cout << " " << std::endl;
}
