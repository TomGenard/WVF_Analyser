set grid
set terminal wxt size 1000,600

# THE WHOLE SIGNAL #

set xrange [*:*]
set yrange [*:*]

plot 'adc_values.data' with lp
replot 'adc_values_smooth_5.data'  with lp
replot 'adc_values_smooth_7.data'  with lp
replot 'adc_values_smooth_9.data'  with lp
replot 'adc_values_smooth_11.data' with lp
replot 'adc_values_smooth_13.data' with lp
replot 'adc_values_smooth_15.data' with lp
pause -1 "Hit [Enter]..."

set terminal pdfcairo
set output "adc_smoothing_test_first_peak.pdf"
replot
set output
set terminal wxt size 1000,600

# THE FIRST PEAK #

set xrange [180:260]
set yrange [*:*]

plot 'adc_values.data' with lp
replot 'adc_values_smooth_5.data'  with lp
replot 'adc_values_smooth_7.data'  with lp
replot 'adc_values_smooth_9.data'  with lp
replot 'adc_values_smooth_11.data' with lp
replot 'adc_values_smooth_13.data' with lp
replot 'adc_values_smooth_15.data' with lp
pause -1 "Hit [Enter]..."

set terminal pdfcairo
set output "adc_smoothing_test_first_peak.pdf"
replot
set output
set terminal wxt size 1000,600

# THE SECOND PEAK #

set xrange [360:460]
set yrange [*:*]

plot 'adc_values.data' with lp
replot 'adc_values_smooth_5.data'  with lp
replot 'adc_values_smooth_7.data'  with lp
replot 'adc_values_smooth_9.data'  with lp
replot 'adc_values_smooth_11.data' with lp
replot 'adc_values_smooth_13.data' with lp
replot 'adc_values_smooth_15.data' with lp
pause -1 "Hit [Enter]..."

set terminal pdfcairo
set output "adc_smoothing_test_second_peak.pdf"
replot
set output
set terminal wxt

## end