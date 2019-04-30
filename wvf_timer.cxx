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
  int pulse_maximum_1 = -1, pulse_maximum_2 = -1;
  double pulse_baseline = -1;
  std::vector<int> adc_values_array;
  double threshold = 0.3; // 0.3 by default

  std::cout << "Insert filepath :" << std::endl;
  std::cin >> file_path;
  //file_path = "wvf.data";

  inFile.open(file_path.c_str());

  std::ofstream myfile;
  myfile.open ("adc_values.data");
  while (inFile >> adc_value) {
    adc_values_array.push_back(adc_value);
    myfile << adc_value << "\n";
  }
  myfile.close();

  //========================================
  // First pass for the maximum and baseline
  //========================================

  double pulse_maximum_1_timestamp = 0, pulse_maximum_2_timestamp = 0;
  int pulse_1_below_threshold_timestamp = -1;
 
  // Compute the baseline of the waveform
  for ( int i = 0; i < adc_values_array.size(); i++ ) {
    if ( i < 100 ) {
      pulse_baseline += adc_values_array[i];
    }
  }
  pulse_baseline = pulse_baseline/100; // Mean of the 100 first values
  
  // Removing the baseline from the waveform
  for ( int i = 0; i < adc_values_array.size(); i++ ) {
    adc_values_array[i] = adc_values_array[i] - pulse_baseline;
  }

  // Finding the first maximum
  for ( int i = 0; i < adc_values_array.size(); i++ ) {
    // For the maximum of the first pulse
    if ( adc_values_array[i] > pulse_maximum_1 ) {
      pulse_maximum_1 = adc_values_array[i];
      pulse_maximum_1_timestamp = i;
    }
  }

  // Compute the mean maximum of the first pulse (to take into account the possible fluctuations)
  pulse_maximum_1 = 0;
  for ( int i = pulse_maximum_1_timestamp; i < ( pulse_maximum_1_timestamp + 25 ); i++ ) {
    pulse_maximum_1 = pulse_maximum_1 + adc_values_array[i];
  }
  
  pulse_maximum_1 = pulse_maximum_1 / 25.;

  // Finding the point where the first pulse goes below the threshold
  for ( int i = pulse_maximum_1_timestamp; i < adc_values_array.size(); i++ ) {
    if ( adc_values_array[i] < ( threshold/2. ) * pulse_maximum_1 ) {
      pulse_1_below_threshold_timestamp = i;
      break;
    }
  }

  // Finding the second maximum
  for ( int i = pulse_1_below_threshold_timestamp; i < adc_values_array.size(); i++ ) { // The first signal takes way less than 100 timesteps to return to the baseline
    if ( adc_values_array[i] > pulse_maximum_2 ) {
      pulse_maximum_2 = adc_values_array[i];
      pulse_maximum_2_timestamp = i;
    }
  }
  
  std::cout << "==========================" << std::endl;
  std::cout << "Maximum 1 : " << pulse_maximum_1 << " at timestamp " << pulse_maximum_1_timestamp << std::endl;
  std::cout << "Maximum 2 : " << pulse_maximum_2 << " at timestamp " << pulse_maximum_2_timestamp << std::endl;
  std::cout << "Baseline : " << pulse_baseline << std::endl;
  std::cout << "==========================" << std::endl;

  //========================================
  // Second pass to find the two trigger points
  //========================================

  int current_value, past_value; // current_value is the value at the current time, past_value is the value at the previous timestamp
  int current_timestamp = -1;    // The current integer timestamp
  double fitted_timestamp = 0;   // The true fitted timestamp
  double a = 0, b = 0;           // Calculation values for the fitting, y = ax + b
  
  for ( int i = 0; i < adc_values_array.size(); i++ ) {
    if ( current_timestamp > 0 ) { // "> 0" to have a past value
      past_value = adc_values_array[i-1];
      current_value = adc_values_array[i];

      if ( timestamp_first_pulse == -1 // -1 is the initial value, test if the value has already been set
	   && current_value > threshold * pulse_maximum_1 ) // Test is we are in the rising period of the signal
	{
	if ( current_timestamp < pulse_maximum_1_timestamp ) {
	  a = ( ( current_value - past_value ) / 1. ); // Divided by 1 because there is only one timestep between the two
	  b = current_value - ( a * i );
	  
	  fitted_timestamp = ( threshold * pulse_maximum_1 - b ) / a;
	  
	  timestamp_first_pulse = fitted_timestamp;
	}
      }
      else if ( timestamp_second_pulse == -1 // -1 is the initial value, test if the value has already been set
		&& current_value > threshold * pulse_maximum_2 // Test is we are in the rising period of the signal
		&& i > ( timestamp_first_pulse + 50 ) ) // Set to 100 to search a maximum beyond the first signal
	{
	if ( current_timestamp < pulse_maximum_2_timestamp ) {
	  a = ( ( current_value - past_value ) / 1. ); // Divided by 1 because there is only one timestep between the two
	  b = current_value - ( a * i );
	  
	  fitted_timestamp = ( threshold * pulse_maximum_2 - b ) / a;
	  
	  timestamp_second_pulse = fitted_timestamp;
	}
      }
    }

    current_timestamp++;
  }

  //========================================
  // Computation of the length of the cable
  //======================================== 
  
  // Each timestamp represents 390,625 ps
  // Length of the cable : 698 cm

  double travel_time, travel_speed;
  double cable_length, timestep_length;

  cable_length = 698;          // In cm
  timestep_length = 0.390625; // In ns
  
  travel_time = ( timestamp_second_pulse - timestamp_first_pulse ) * timestep_length; // In ns
  travel_speed = ( cable_length * 2 ) / travel_time;                                  // In cm/ns
  
  std::cout << "==========================" << std::endl;
  std::cout << "The cable length is : " << cable_length << " cm" << std::endl;
  std::cout << "The length of a single timestep is : " << cable_length << " ns" << std::endl;
  std::cout << "==========================" << std::endl;
  std::cout << "The first timestamp is : " << timestamp_first_pulse << std::endl;
  std::cout << "The second timestamp is : " << timestamp_second_pulse << std::endl;
  std::cout << "The signal took " << travel_time << " ns to do the back and forth" << std::endl;
  std::cout << "The speed of the signal is : " << travel_speed << " cm/ns" << std::endl;
  std::cout << "==========================" << std::endl;
}
