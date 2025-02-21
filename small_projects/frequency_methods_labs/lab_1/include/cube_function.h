#ifndef FREQUENCY_METHODS_LAB_1_CUBE_FUNCTION_H
#define FREQUENCY_METHODS_LAB_1_CUBE_FUNCTION_H

#include <function.h>
#include <complex>

namespace frequency_methods_lab_1
{
	class cube : public function
	{
	public:
	
		cube( int_fast32_t n ) : function( n ) { }
	
		std::complex<double> value( const std::complex<double>& argument ) const final;
		std::complex<double> fourier_series_coefficient_a_0(  ) const final;
		std::complex<double> fourier_series_coefficient_a_n( uint_fast32_t n ) const final;
		std::complex<double> fourier_series_coefficient_b_n( uint_fast32_t n ) const final;
		std::complex<double> fourier_series_coefficient_c_n( int_fast32_t n ) const final;
		std::complex<double> sum_of_fourier_series( double argument ) const final;
		std::complex<double> sum_of_fourier_series_in_complex_form( double argument ) const final;
	};
	
	
	
	
} // namespace frequency_methods_lab_1

#endif // FREQUENCY_METHODS_LAB_1_CUBE_FUNCTION_H