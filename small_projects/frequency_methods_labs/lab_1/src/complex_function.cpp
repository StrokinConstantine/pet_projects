#include <complex_function.h>

#include <constants.h>
#include <iostream>
#include <complex>


namespace frequency_methods_lab_1
{
	

	std::complex<double> complex_function::value( const std::complex<double>& argument ) const
	{
		std::complex<double> value_to_return;
		
		double R = 100.0;
		double T = 2.0 * PI;
		
		double lower_bound = -PI / 4;  
        double upper_bound = 7 * PI / 4; 
		
		
		double period = 2.0 * PI;
		double mapped_argument = std::fmod( argument.real(), T );
		
		if ( mapped_argument < 0 )
			mapped_argument += T;
		
		mapped_argument += lower_bound;
		
		while( mapped_argument < lower_bound )
			mapped_argument += T;
		while( mapped_argument > upper_bound )
			mapped_argument -= T;
		
		if ( mapped_argument > ( -T / 8.0 ) && mapped_argument < ( T / 8.0 ) )
			return std::complex<double>( R, 8.0 * R * mapped_argument / T );
		if ( mapped_argument > ( T / 8.0 ) && mapped_argument < ( 3.0 * T / 8.0 ) )
			return std::complex<double>( 2.0 * R - 8.0 * R * mapped_argument / T, R );
		if ( mapped_argument > ( 3.0 * T / 8.0 ) && mapped_argument < ( 5.0 * T / 8.0 ) )
			return std::complex<double>( -R, 4.0 * R - 8.0 * R * mapped_argument / T );
		if ( mapped_argument > ( 5.0 * T / 8.0 ) && mapped_argument < ( 7.0 * T / 8.0 ) )
			return std::complex<double>( -6.0 * R + 8.0 * R * mapped_argument / T, -R );
		
		return std::complex<double>( -99.0, 0.0 );
	}
	
	std::complex<double> complex_function::fourier_series_coefficient_a_0(  ) const
	{
		return std::complex( PI, 0.0 );
	}
	
	std::complex<double> complex_function::fourier_series_coefficient_a_n( uint_fast32_t n ) const
	{
		if ( ( n % 2u ) == 0 ) return std::complex( 0.0, 0.0 );
		return std::complex( ( -4.0 / ( static_cast<double>( n*n )* PI ) ), 0.0 );
	}
	
	std::complex<double> complex_function::fourier_series_coefficient_b_n( uint_fast32_t n ) const
	{
		return std::complex( 0.0, 0.0 );
	}
	
	std::complex<double> complex_function::fourier_series_coefficient_c_n( int_fast32_t n ) const
	{
		if ( n == 0 )
			return std::complex( 0.0, 0.0 );
		/*
		double R = 100.0;
		double n_double = static_cast<double>( n );
		std::complex<double> sum( 0.0, 0.0 );
		
		double base_angle = PI * n_double / 4.0;
		double angles[4] = { base_angle , 3.0 * base_angle, 5.0 * base_angle, 5.0 * base_angle };
		
		
		sum = (  ( ( 2.0 * PI * n_double + 8.0 ) * sin( angles[0] ) ) - 2.0 * PI * n_double * cos( angles[0] )  );
		
		sum += std::complex(  -PI * n_double * sin( angles[0] ) ,  ( -4 + -PI * n_double ) * sin( angles[0] ) );
		sum += std::complex(  ( 4 + PI * n_double ) * cos( angles[0] ) ,  ( -PI * n_double ) * cos( angles[0] ) );
		
		sum += std::complex(  4 * sin( angles[1] ) ,  4 * sin( angles[1] ) );
		sum += std::complex(  -4 * cos( angles[1] ) ,  4 * cos( angles[1] ) );
		
		sum += std::complex(  -4 * sin( angles[2] ) ,  4 * sin( angles[2] ) );
		sum += std::complex(  -4 * cos( angles[2] ) ,  -4 * cos( angles[2] ) );
		
		sum += std::complex(  PI * n_double * sin( angles[3] ) ,  ( -4 + -PI * n_double ) * sin( angles[3] ) );
		sum += std::complex(  ( 4 + PI * n_double ) * cos( angles[3] ) ,  ( PI * n_double ) * cos( angles[3] ) );
		
		sum *= ( R / ( 2 * PI * PI * n_double * n_double ) );
		*/
		//std::cout << "INTEGRAL3:" << integral_3( 3 ) << std::endl;
		//std::cout << "INTEGRAL1:" << integral_1( 3 ) << std::endl;
		//std::cout << "INTEGRAL4:" << integral_4( 5 ) << std::endl;
		
		return integral_1( n ) + integral_2( n ) + integral_3( n ) + integral_4( n );
	}
	
	std::complex<double> complex_function::sum_of_fourier_series( double argument ) const
	{
		std::complex<double> sum(0.0, 0.0);
		for ( uint_fast32_t i = 1; i <= number_of_terms_in_fourier_series; ++i )
		{
			double angle = static_cast<double>(i) * argument;
			sum += ( fourier_series_coefficient_a_n( i ) * cos( angle ) + fourier_series_coefficient_b_n( i ) * sin( angle ) );
		}
		sum += ( fourier_series_coefficient_a_0() / 2.0 );
		return sum;
	}
	
	std::complex<double> complex_function::sum_of_fourier_series_in_complex_form( double argument ) const
	{
		argument -= PI / 4.0;
		
		std::complex<double> sum(0.0, 0.0);
		const std::complex<double> imaginary_unit(0.0, 1.0);
		
		for ( int_fast32_t i = -number_of_terms_in_fourier_series; i <= number_of_terms_in_fourier_series; ++i )
			sum += fourier_series_coefficient_c_n( i ) * std::exp( static_cast<std::complex<double>>(static_cast<double>(i) * argument) * imaginary_unit  );
		
		return sum;
	}
	
} // namespace frequency_methods_lab_1