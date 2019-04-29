//================================================================
// WAVEFORM (WVF) TIMER
// Short program to detect two pulses reaching a threashold, and calculate the delay between the two
// 
// Tom Génard - 26.04.2019
//================================================================

#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>

int main(void) {
  std::ifstream inFile;
  std::string file_path;
  double timestamp_first_pulse = -1, timestamp_second_pulse = -1;
  int adc_value = -1;
  double current_timestamp = -1;
  int pulse_maximum = -1;
  double pulse_baseline = -1;
  std::vector<int> adc_values_array;

  std::cout << "Insert filepath :" << std::endl;
  std::cin >> file_path;
  //file_path = "waveform.data";

  inFile.open(file_path.c_str());

  std::ofstream myfile;
  myfile.open ("adc_values.data");
  while (inFile >> adc_value) {
    //std::cout << adc_value << std::endl;

    adc_values_array.push_back(adc_value);
    myfile << adc_value << "\n";
  }
  myfile.close();

  //========================================
  // First pass for the maximum and baseline
  //========================================

  for ( int j = 0; j < adc_values_array.size(); j++ ) {
    // For the maximum
    if ( adc_values_array[j] > pulse_maximum ) {
      pulse_maximum = adc_values_array[j];
    }

    // For the baseline
    if ( j < 100 ) {
      pulse_baseline += adc_values_array[j];
    }
  }

  pulse_baseline = pulse_baseline/100; // Mean of the 100 first values

  std::cout << "Maximum : " << pulse_maximum << std::endl;
  std::cout << "Baseline : " << pulse_baseline << std::endl;

  //========================================
  // Second pass to find the two trigger points
  //========================================

  int current_value, past_value;
  double a = 0, b = 0;

  for ( int i = 0; i < adc_values_array.size(); i++ ) {
    if ( current_timestamp > 0 ) {
      past_value = adc_values_array[i-1];
      current_value = adc_values_array[i];

      if ( current_value > 0.3 * ( pulse_maximum - pulse_baseline ) + pulse_baseline && past_value < 0.3 * ( pulse_maximum - pulse_baseline ) + pulse_baseline ) {
	if ( current_value > past_value ) {
	  a = ( ( current_value - past_value ) / 1. ); // Divided by 1 because there is only one timestep between the two
	  b = current_value - ( a * i );

	  current_timestamp = ( ( 0.3 * ( pulse_maximum - pulse_baseline ) + pulse_baseline ) - b ) / a;
	  std::cout << i << " " << current_timestamp << std::endl;

	  if ( timestamp_first_pulse == -1 ) {
	    timestamp_first_pulse = current_timestamp;
	  }
	  else {
	    timestamp_second_pulse = current_timestamp;
	  }
	}
      }
    }

    else {
      // Do nothing
    }

    current_timestamp++;
  }

  //========================================
  // Computation of the length of the cable
  //======================================== 
  
  // Each timestamp represents 390,625 ps
  // Speed of the signal : 20 cm/ns

  double travel_time, travel_length;

  travel_time = ( timestamp_second_pulse - timestamp_first_pulse ) * 390.625; // In ps
  travel_length = 20 * ( travel_time * 0.001 ); // In cm

  std::cout << "The first timestamp is : " << timestamp_first_pulse << std::endl;
  std::cout << "The second timestamp is : " << timestamp_second_pulse << std::endl;
  std::cout << "The legth of the cable is : " << ( travel_length / 2. ) << " cm" << std::endl;
}
