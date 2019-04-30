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
 
  void set_pulse_maximum(int);
  void set_pulse_maximum_timestamp(int);
  void set_pulse_start(int);
  void set_pulse_end(int);
  
  int get_pulse_maximum(void);
  int get_pulse_maximum_timestamp(void);
  int get_pulse_start(void);
  int get_pulse_end(void);
  
  void verify_values(void);

  
 private :
  int _pulse_maximum;
  int _pulse_maximum_timestamp;
  int _pulse_start, _pulse_end;
  bool _info_validated = false;

};
