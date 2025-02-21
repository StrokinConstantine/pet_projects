#ifndef FREQUENCY_METHODS_LAB_1_FUNCTION_H
#define FREQUENCY_METHODS_LAB_1_FUNCTION_H

#include <complex>
#include <cstdint>
#include <iostream>
#include <constants.h>
#include <cmath>
namespace frequency_methods_lab_1
{
	class function
	{
	protected:
		
		int_fast32_t number_of_terms_in_fourier_series = 0;
		
	public:
		
		function( int_fast32_t n ) : number_of_terms_in_fourier_series( n )
		{

		}
		
		int_fast32_t get_number_of_terms_in_fourier_series( ) const
		{
			return number_of_terms_in_fourier_series;
		}
		
		virtual std::complex<double> value( const std::complex<double>& argument ) const = 0; 
		virtual std::complex<double> fourier_series_coefficient_a_0() const = 0;
		virtual std::complex<double> fourier_series_coefficient_a_n( uint_fast32_t n ) const = 0;
		virtual std::complex<double> fourier_series_coefficient_b_n( uint_fast32_t n ) const = 0;
		virtual std::complex<double> fourier_series_coefficient_c_n( int_fast32_t n ) const = 0;
		virtual std::complex<double> sum_of_fourier_series( double argument ) const = 0;
		virtual std::complex<double> sum_of_fourier_series_in_complex_form( double argument ) const = 0;
		virtual ~function() = default;
		
		
		void check_parsevals_identity(
		double left_argument_boundary
		, double right_argument_boundary
		, double discretization_step
		, int_fast32_t number_of_terms_in_fourier_series
		) const
		{
			double integral = 0.0;
			std::complex<double> sum( 0.0, 0.0 );
			
			for ( double t = ( left_argument_boundary + discretization_step / 2.0 ); t < right_argument_boundary; t += discretization_step )
			{
				
				integral += value( t ).real() * value( t ).real() * discretization_step;
			}
			
			integral *= ( 2.0 / (right_argument_boundary - left_argument_boundary) );
			
			for ( int_fast32_t i = 1; i < number_of_terms_in_fourier_series; ++i )
			{
				sum += ( (fourier_series_coefficient_a_n(i)*fourier_series_coefficient_a_n(i)) + (fourier_series_coefficient_b_n(i)*fourier_series_coefficient_b_n(i)) );
			}

			for ( int_fast32_t i = -number_of_terms_in_fourier_series; i < number_of_terms_in_fourier_series; ++i )
			{
			//	sum += std::abs( fourier_series_coefficient_c_n(i) ) * std::abs( fourier_series_coefficient_c_n(i) ) * 2;
			}

			sum += fourier_series_coefficient_a_0() * fourier_series_coefficient_a_0() / 2.0;
			
			
			std::cout << sum << std::endl;
			std::cout << integral << std::endl;
			
			
		}
		
	};
	
} // namespace frequency_methods_lab_1

#endif // FREQUENCY_METHODS_LAB_1_FUNCTION_H