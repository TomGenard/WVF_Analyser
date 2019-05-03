//================================================================
// SAVITZKY-GOLAY (SG) CONVOLUTION ALGORITHM
// Smoothen a waveform using the Savitzky-Golay algorithm
// 
// Tom Génard - Last modified : 03.05.2019
//================================================================

#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>

#include "sg_convolution_algorithm.h"

int main(void) {
  std::vector<double> adc_values_array;
  int adc_value = -1;
  
  std::ifstream inFile;
  std::string file_path;
  //file_path = "wvf.data";
  std::cout << "Insert file path :" << std::endl;
  std::cin >> file_path;
  
  inFile.open(file_path.c_str());
  while (inFile >> adc_value) {
    adc_values_array.push_back(adc_value);
  }
  inFile.close();

  sg_convolution_algorithm sg_conv_algo(adc_values_array);
  std::vector<double> adc_values_array_smooth_5;
  std::vector<double> adc_values_array_smooth_7;
  std::vector<double> adc_values_array_smooth_9;
  std::vector<double> adc_values_array_smooth_11;
  std::vector<double> adc_values_array_smooth_13;
  std::vector<double> adc_values_array_smooth_15;
  std::ofstream myfile;
  
  // 5 FACTORS
  
  adc_values_array_smooth_5 = sg_conv_algo.smoothen_5_factors();

  myfile.open ("adc_values_smooth_5.data");
  for ( int i = 0; i < adc_values_array_smooth_5.size(); i++ ) {
    myfile << adc_values_array_smooth_5[i] << "\n";
  }
  myfile.close();

  // 7 FACTORS

  adc_values_array_smooth_7 = sg_conv_algo.smoothen_7_factors();

  myfile.open ("adc_values_smooth_7.data");
  for ( int i = 0; i < adc_values_array_smooth_7.size(); i++ ) {
    myfile << adc_values_array_smooth_7[i] << "\n";
  }
  myfile.close();

  // 9 FACTORS

  adc_values_array_smooth_9 = sg_conv_algo.smoothen_9_factors();

  myfile.open ("adc_values_smooth_9.data");
  for ( int i = 0; i < adc_values_array_smooth_9.size(); i++ ) {
    myfile << adc_values_array_smooth_9[i] << "\n";
  }
  myfile.close();

  // 11 FACTORS

  adc_values_array_smooth_11 = sg_conv_algo.smoothen_11_factors();

  myfile.open ("adc_values_smooth_11.data");
  for ( int i = 0; i < adc_values_array_smooth_11.size(); i++ ) {
    myfile << adc_values_array_smooth_11[i] << "\n";
  }
  myfile.close();

  // 13 FACTORS

  adc_values_array_smooth_13 = sg_conv_algo.smoothen_13_factors();

  myfile.open ("adc_values_smooth_13.data");
  for ( int i = 0; i < adc_values_array_smooth_13.size(); i++ ) {
    myfile << adc_values_array_smooth_13[i] << "\n";
  }
  myfile.close();

  // 15 FACTOR

  adc_values_array_smooth_15 = sg_conv_algo.smoothen_15_factors();

  myfile.open ("adc_values_smooth_15.data");
  for ( int i = 0; i < adc_values_array_smooth_15.size(); i++ ) {
    myfile << adc_values_array_smooth_15[i] << "\n";
  }
  myfile.close();
}
