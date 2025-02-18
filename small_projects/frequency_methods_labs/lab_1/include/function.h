#ifndef FREQUENCY_METHODS_LAB_1_FUNCTION_H
#define FREQUENCY_METHODS_LAB_1_FUNCTION_H

#include <complex>
#include <cstdint>

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
		
		virtual std::complex<double> value( const std::complex<double>& argument ) const = 0; 
		virtual std::complex<double> fourier_series_coefficient_a_0() const = 0;
		virtual std::complex<double> fourier_series_coefficient_a_n( uint_fast32_t n ) const = 0;
		virtual std::complex<double> fourier_series_coefficient_b_n( uint_fast32_t n ) const = 0;
		virtual std::complex<double> fourier_series_coefficient_c_n( uint_fast32_t n ) const = 0;
		virtual std::complex<double> sum_of_fourier_series( double argument ) const = 0;
		virtual std::complex<double> sum_of_fourier_series_in_complex_form( double argument ) const = 0;
		virtual ~function() = default;
	};
	
} // namespace frequency_methods_lab_1

#endif // FREQUENCY_METHODS_LAB_1_FUNCTION_H