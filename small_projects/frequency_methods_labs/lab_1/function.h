#ifndef FREQUENCY_METHODS_LAB_1_FUNCTION_H
#define FREQUENCY_METHODS_LAB_1_FUNCTION_H

#include <complex>

namespace frequency_methods_lab_1
{
	class function
	{
		virtual std::complex<double> value( const std::complex& argument ) const = 0; 
		virtual std::complex<double> fourier_series_coefficient_a_0() const = 0;
		virtual std::complex<double> fourier_series_coefficient_a_n( uint_fast32_t n ) const = 0;
		virtual std::complex<double> fourier_series_coefficient_b_n( uint_fast32_t n ) const = 0;
		virtual std::complex<double> fourier_series_coefficient_c_n( uint_fast32_t n ) const = 0;
	
		virtual std::complex<double> sum_of_fourier_series( uint_fast32_t n ) const = 0;
		virtual std::complex<double> sum_of_fourier_series_in_complex_form( int_fast32_t n ) const = 0;
		
		virtual ~function() = default;
	};
	
	
	
	
	class periodic_absolute_value : public function
	{
		std::complex<double> value( const std::complex& argument ) const override
		{
			double value = fmod( fabs( argument.real() ), 4.0 * matplot::pi );
			if ( value > ( 2.0 * matplot::pi ) )
				return 2.0 * matplot::pi - value;
			return value;
		}
		
		
		
	}
	
	
} // namespace frequency_methods_lab_1


#endif // FREQUENCY_METHODS_LAB_1_FUNCTION_H