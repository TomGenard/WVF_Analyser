//================================================================
// SAVITZKY-GOLAY (SG) CONVOLUTION ALGORITHM
// Smoothen a waveform using the Savitzky-Golay algorithm
// 
// Tom Génard - Last modified : 03.05.2019
//================================================================

class sg_convolution_algorithm {
 public:
  sg_convolution_algorithm();
  sg_convolution_algorithm(std::vector<double>);
  void add_curve(std::vector<double>);

  std::vector<double> smoothen_5_factors();
  std::vector<double> smoothen_7_factors();
  std::vector<double> smoothen_9_factors();
  std::vector<double> smoothen_11_factors();
  std::vector<double> smoothen_13_factors();
  std::vector<double> smoothen_15_factors();
  
 private:
  std::vector<double> _curve;
  std::vector<double> _smooth_curve;
};
