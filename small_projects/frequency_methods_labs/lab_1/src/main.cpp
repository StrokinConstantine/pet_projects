#include <iostream>
#include <cmath>
#include <complex>
#include <matplot/matplot.h>

#include <periodic_absolute_value_function.h>


void plot_f(
	const frequency_methods_lab_1::function& f
	, const std::string& plot_name
	, double left_plot_argument_boundary
	, double right_plot_argument_boundary
	, uint_fast16_t plot_precision
	, uint_fast32_t number_of_terms_in_fourier_series
)
{
	std::vector<double> x = matplot::linspace( left_plot_argument_boundary, right_plot_argument_boundary, plot_precision );

	matplot::xlabel( "x" );
    matplot::ylabel( plot_name );
	
	std::vector<double> actual_f = matplot::transform(
		x
		, [ &f ]( double t ) { return f.value( t ).real(); }
	); 
	std::vector<double> sum_of_fourier_series_of_f = matplot::transform(
		x
		, [ &f ]( double t ) { return f.sum_of_fourier_series( t ).real(); }
	); 
	std::vector<double> sum_of_fourier_series_in_complex_form_of_f = matplot::transform(
		x
		, [ &f ]( double t ) { return f.sum_of_fourier_series_in_complex_form( t ).real(); }
	); 
	
	matplot::plot( x, actual_f, x, sum_of_fourier_series_of_f, x, sum_of_fourier_series_in_complex_form_of_f );
	matplot::show();
	matplot::cla(); // clear the current plot 
	
	std::vector<double> difference_between_actual_f_and_sum_of_fourier_series_of_f( plot_precision );
	std::vector<double> difference_between_actual_f_and_sum_of_fourier_series_in_complex_form( plot_precision );
	double standard_deviation_for_sum_of_fourier_series_of_f = 0.0;
	double standard_deviation_for_sum_of_fourier_series_in_complex_form_of_f = 0.0;
	
	for ( size_t i = 0; i < plot_precision; ++i )
	{
		difference_between_actual_f_and_sum_of_fourier_series_of_f[ i ] = actual_f[ i ] - sum_of_fourier_series_of_f[ i ];
		difference_between_actual_f_and_sum_of_fourier_series_in_complex_form[ i ] = actual_f[ i ] - sum_of_fourier_series_in_complex_form_of_f[ i ];
		standard_deviation_for_sum_of_fourier_series_of_f += ( difference_between_actual_f_and_sum_of_fourier_series_of_f[ i ] ) * ( difference_between_actual_f_and_sum_of_fourier_series_of_f[ i ] );
		standard_deviation_for_sum_of_fourier_series_in_complex_form_of_f += ( difference_between_actual_f_and_sum_of_fourier_series_in_complex_form[ i ] ) * ( difference_between_actual_f_and_sum_of_fourier_series_in_complex_form[ i ] );
	}
	standard_deviation_for_sum_of_fourier_series_of_f /= static_cast<double>( plot_precision );
	standard_deviation_for_sum_of_fourier_series_in_complex_form_of_f /= static_cast<double>( plot_precision );
	standard_deviation_for_sum_of_fourier_series_of_f = std::sqrt( standard_deviation_for_sum_of_fourier_series_of_f );
	standard_deviation_for_sum_of_fourier_series_in_complex_form_of_f = std::sqrt( standard_deviation_for_sum_of_fourier_series_in_complex_form_of_f );
	
	
	matplot::plot( x, difference_between_actual_f_and_sum_of_fourier_series_of_f );
	matplot::show();
	
	std::cout << "standard_deviation_for_sum_of_fourier_series_of_f: " << standard_deviation_for_sum_of_fourier_series_of_f << std::endl;
	
	matplot::cla();

	matplot::plot( x, difference_between_actual_f_and_sum_of_fourier_series_in_complex_form );
	matplot::show();
	
	std::cout << "standard_deviation_for_sum_of_fourier_series_in_complex_form_of_f: " << standard_deviation_for_sum_of_fourier_series_in_complex_form_of_f << std::endl;
	
	matplot::cla();
}





int main( void )
{
	
	plot_f(
		frequency_methods_lab_1::periodic_absolute_value( 10'000 )
		, " |x| "
		, -3.0 * matplot::pi
		, 3.0 * matplot::pi
		, 10'000
		, 2
	);

	return 0;
}