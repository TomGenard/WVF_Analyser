//================================================================
// WAVEFORM (WVF) PEAK INFORMATIONS
// Stores the main characteristics of a pulse, or "peak"
// 
// Tom Génard - Last modified : 30.04.2019
//================================================================

class wvf_peak_info {
 public :
  wvf_peak_info();
  wvf_peak_info(int,int,int,int);
 
  void set_pulse_maximum(double);
  void set_pulse_maximum_timestamp(double);
  void set_pulse_start(double);
  void set_pulse_end(double);
  
  double get_pulse_maximum(void);
  double get_pulse_maximum_timestamp(void);
  double get_pulse_start(void);
  double get_pulse_end(void);

  void reset(void);
  
  void verify_values(void);

  
 private :
  double _pulse_maximum;
  double _pulse_maximum_timestamp;
  double _pulse_start, _pulse_end;
  bool _info_validated = false;

};
