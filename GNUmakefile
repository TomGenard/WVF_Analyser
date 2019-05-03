
CPPFLAGS=-I. $(shell gsl-config --cflags)
LDFLAGS=-L. -lwvf
LDFLAGS_GSL=$(LDFLAGS) $(shell gsl-config --libs)

objects=wvf_cable_analyser.o wvf_peak_analyser.o wvf_peak_info.o wvf_baseline_analyser.o line_2d.o vector_2d.o

.PHONY : all
all : wvf_test_gsl wvf_cable_analyser

.PHONY : clean
clean :
	$(RM) wvf_test_gsl
	$(RM) wvf_cable_analyser
	$(RM) libwvf.a 
	find . -name "*.o" -exec rm -f \{\} \;

wvf_test_gsl : wvf_test_gsl.cxx libwvf.a 
	$(CXX) $(CPPFLAGS) $< -o $@ $(LDFLAGS_GSL)

wvf_cable_analyser : wvf_cable_analyser.cxx libwvf.a 
	$(CXX) $(CPPFLAGS) $< -o $@ $(LDFLAGS)

libwvf.a : $(objects)
	ar rcs $@ $(objects) 

wvf_cable_analyser.o : wvf_cable_analyser.cc wvf_cable_analyser.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

wvf_peak_analyser.o : wvf_peak_analyser.cc wvf_peak_analyser.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

wvf_peak_info.o : wvf_peak_info.cc wvf_peak_info.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

wvf_baseline_analyser.o : wvf_baseline_analyser.cc wvf_baseline_analyser.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

line_2d.o : line_2d.cc line_2d.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

vector_2d.o : vector_2d.cc vector_2d.h
	$(CXX) $(CPPFLAGS) -c $< -o $@
