#include <cstdlib>
#include <vector>
#include <iostream>

#include <gsl/gsl_fit.h>

int main(void) {
  int error_code = EXIT_SUCCESS;
  
  std::vector<double> xi({ 1.0,  2.0, 3.0, 4.0});
  std::vector<double> yi({2.05, 2.85, 4.1, 5.2});
  std::vector<double> si({0.15, 0.16, 0.15, 0.17});
  std::vector<double> wi;
  for(auto s : si) {
    wi.push_back(1.0/gsl_pow_2(s));
  }

  double c0;
  double c1;
  double cov00;
  double cov01;
  double cov11;
  size_t ndata = xi.size();
  double chisq;
  
  int code = gsl_fit_wlinear(xi.data(), 1,
			     wi.data(), 1,
			     yi.data(), 1,
			     ndata,
			     &c0, &c1, &cov00, &cov01, &cov11, &chisq);

  if (code == 0) {
    std::cout << "c0 = " << c0 << std::endl;
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "cov00 = " << cov00 << std::endl;
    std::cout << "cov01 = " << cov01 << std::endl;
    std::cout << "cov11 = " << cov11 << std::endl;
    std::cout << "chisq = " << chisq << std::endl;
  } else {
    std::cerr << "Fit failed!" << std::endl;
  }

  double x = 5.0;
  double y;
  double y_err;
  code = gsl_fit_linear_est(x, c0, c1, cov00, cov01, cov11, &y, &y_err);
  std::cout << "y = " << y << std::endl;
  std::cout << "y_err = " << y_err << std::endl;
 
  return error_code;
}


  
