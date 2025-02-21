#include <iostream>
#include <cmath>
#include <complex>
#include <matplot/matplot.h>

#include <periodic_absolute_value_function.h>
#include <complex_function.h>
#include <square_wave_function.h>

void plot_f(
	const frequency_methods_lab_1::function& f
	, const std::string& plot_name
	, double left_plot_argument_boundary
	, double right_plot_argument_boundary
	, uint_fast16_t plot_precision
)
{
	std::vector<double> x = matplot::linspace( left_plot_argument_boundary, right_plot_argument_boundary, plot_precision );

	matplot::xlabel( "t" );
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
	
	for ( size_t i = 0; i < plot_precision; ++i )
	{
	//	std::cout << actual_f[i] << "; " << sum_of_fourier_series_in_complex_form_of_f[i] << std::endl;
	}
	
	
	f.check_parsevals_identity(
		-frequency_methods_lab_1::PI
		, frequency_methods_lab_1::PI
		, 0.001
		, f.get_number_of_terms_in_fourier_series()
	);
	
	matplot::plot( x, actual_f );
	matplot::show();
	matplot::cla(); 
	

	matplot::plot( x, actual_f, x, sum_of_fourier_series_in_complex_form_of_f );
	matplot::show();
	matplot::cla();
	
	matplot::plot( x, actual_f, x, sum_of_fourier_series_of_f, x, sum_of_fourier_series_in_complex_form_of_f );
	matplot::show();
	matplot::cla();

	
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
	
	
	
	matplot::ylabel( "Разница между исходной функцией и её рядом Фурье" );
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
	/*
	plot_f(
		frequency_methods_lab_1::complex_function( 50 )
		, " |x| "
		, -3.0 * matplot::pi
		, 3.0 * matplot::pi
		, 10'00
	);
	*/
	
	plot_f(
		frequency_methods_lab_1::periodic_absolute_value( 5000 )
		, " Модуль "
		, -3.0 * matplot::pi
		, 3.0 * matplot::pi
		, 10'000
	);

	
	
	return 0;
}