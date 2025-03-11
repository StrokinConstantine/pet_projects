#ifndef FREQUENCY_METHODS_LAB_1_COMPLEX_FUNCTION_H
#define FREQUENCY_METHODS_LAB_1_COMPLEX_FUNCTION_H

#include <function.h>
#include <complex>
#include <constants.h>

namespace frequency_methods_lab_1
{
	class complex_function : public function
	{
	public:
	
		complex_function( int_fast32_t n ) : function( n ) { }
	
		
		std::complex<double> value( const std::complex<double>& argument ) const final;
		std::complex<double> fourier_series_coefficient_a_0(  ) const final;
		std::complex<double> fourier_series_coefficient_a_n( uint_fast32_t n ) const final;
		std::complex<double> fourier_series_coefficient_b_n( uint_fast32_t n ) const final;
		std::complex<double> fourier_series_coefficient_c_n( int_fast32_t n ) const final;
		std::complex<double> sum_of_fourier_series( double argument ) const final;
		std::complex<double> sum_of_fourier_series_in_complex_form( double argument ) const final;
		
		virtual ~complex_function() {}
		
		
		std::complex<double> f_1( int_fast32_t n, double x ) const
		{
			double n_double = static_cast<double>( n ); 
			
			std::complex<double> power(0.0, -1.0 * n_double * x );
			
			std::complex<double> value( (4.0*n_double*x) , (-4.0) + (-PI*n_double) );
			
			std::complex<double> multiplier(-100.0 / (2.0*PI*PI*n_double*n_double), 0 );
			
			std::complex<double> ret = value*multiplier* std::exp( power );
			
			return ret;
		}
		
		std::complex<double> integral_1( int_fast32_t n ) const
		{
			return f_1( n, PI / 4.0) - f_1( n, -PI / 4.0);
		}
		
		
		std::complex<double> f_2( int_fast32_t n, double x ) const
		{
			double n_double = static_cast<double>( n ); 
			
			std::complex<double> power(0.0, -1.0 * n_double * x );
			
			std::complex<double> value( (4.0) + (PI*n_double) ,(-2.0*PI*n_double) + (4.0*x*n_double)  );
			
			std::complex<double> multiplier(-100.0/(2.0*PI*PI*n_double*n_double), 0 );
			
			std::complex<double> ret = value*multiplier* std::exp( power );
			
			return ret;
		}
		
		std::complex<double> integral_2( int_fast32_t n ) const
		{
			return f_2( n, 3.0 * PI / 4.0) - f_2( n, PI / 4.0);
		}
		
		
		std::complex<double> f_3( int_fast32_t n, double x ) const
		{
			double n_double = static_cast<double>( n ); 
			
			std::complex<double> power(0.0, -1.0 * n_double * x );
			
			std::complex<double> value( (4.0*n_double*x) - (4.0*PI*n_double), (-4.0) + (-PI*n_double));
			
			std::complex<double> multiplier(100.0/(2.0*PI*PI*n_double*n_double), 0 );
			
			std::complex<double> ret = value*multiplier* std::exp( power );
			
			return ret;
		}
		
		std::complex<double> integral_3( int_fast32_t n ) const
		{
			return f_3( n, 5.0 * PI / 4.0) - f_3( n, 3.0 * PI / 4.0);
		}
		
		
		std::complex<double> f_4( int_fast32_t n, double x ) const
		{
			double n_double = static_cast<double>( n ); 
			
			std::complex<double> power(0.0, -1.0 * n_double * x );
			
			std::complex<double> value( (4.0) + (PI*n_double) ,(-6.0*PI*n_double) + (4.0*x*n_double)  );
			
			std::complex<double> multiplier(100.0/(2.0*PI*PI*n_double*n_double), 0 );
			
			std::complex<double> ret = value*multiplier* std::exp( power );
			
			return ret;
		}
		
		std::complex<double> integral_4( int_fast32_t n ) const
		{
			return f_4( n, 7.0 * PI / 4.0) - f_4( n, 5.0 * PI / 4.0);
		}
		
		
		
		
		
	};
	
	
	
	
} // namespace frequency_methods_lab_1

#endif // FREQUENCY_METHODS_LAB_1_COMPLEX_FUNCTION_H