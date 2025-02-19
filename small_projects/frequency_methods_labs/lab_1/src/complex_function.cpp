#include <periodic_absolute_value_function.h>

#include <constants.h>

#include <complex>


namespace frequency_methods_lab_1
{
	

	std::complex<double> periodic_absolute_value::value( const std::complex<double>& argument ) const
	{
		std::complex<double> value_to_return;
		
		double R = 1.0;
		double T = 2.0 * PI;
		
		double lower_bound = -PI / 4;  
        double upper_bound = 7 * PI / 4; 
		
		
		double period = 2.0 * PI;
		double mapped_argument = std::fmod( argument.real(), T )
		
		if ( mapped_argument < 0 )
			mapped_argument += T;
		
		mapped_argument += lower_bound;
		
		while( mapped_argument < lower_bound )
			x += T;
		while( mapped_argument > upper_bound )
			x -= T;
		
		if ( mapped_argument > ( -T / 8.0 ) && mapped_argument < ( T / 8.0 ) )
			return std::complex<double>( R, 8.0 * R * mapped_argument / T );
		if ( mapped_argument > ( T / 8.0 ) && mapped_argument < ( 3.0 * T / 8.0 ) )
			return std::complex<double>( 2.0 * R - 8.0 * R * mapped_argument / T, R );
		if ( mapped_argument > ( 3.0 * T / 8.0 ) && mapped_argument < ( 5.0 * T / 8.0 ) )
			return std::complex<double>( -R, 4.0 * R - 8.0 * R * mapped_argument / T );
	//	if ( mapped_argument > ( 5.0 * T / 8.0 ) && mapped_argument < ( 7.0 * T / 8.0 ) )
		return std::complex<double>( -6.0 * R + 8.0 * R * mapped_argument / T, -R );
	}
	
	std::complex<double> periodic_absolute_value::fourier_series_coefficient_a_0(  ) const
	{
		return std::complex( PI, 0.0 );
	}
	
	std::complex<double> periodic_absolute_value::fourier_series_coefficient_a_n( uint_fast32_t n ) const
	{
		if ( ( n % 2u ) == 0 ) return std::complex( 0.0, 0.0 );
		return std::complex( ( -4.0 / ( static_cast<double>( n*n )* PI ) ), 0.0 );
	}
	
	std::complex<double> periodic_absolute_value::fourier_series_coefficient_b_n( uint_fast32_t n ) const
	{
		return std::complex( 0.0, 0.0 );
	}
	
	std::complex<double> periodic_absolute_value::fourier_series_coefficient_c_n( uint_fast32_t n ) const
	{
		if ( n == 0 ) return std::complex( PI / 2.0, 0.0 );
		if ( ( n % 2 ) == 0 ) return std::complex( 0.0, 0.0 );
		return std::complex( ( -2.0 / ( static_cast<double>( n*n )* PI ) ), 0.0 );
	}
	
	std::complex<double> periodic_absolute_value::sum_of_fourier_series( double argument ) const
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
	
	std::complex<double> periodic_absolute_value::sum_of_fourier_series_in_complex_form( double argument ) const
	{
		std::complex<double> sum(0.0, 0.0);
		const std::complex<double> imaginary_unit(0.0, 1.0);
		for ( int_fast32_t i = -number_of_terms_in_fourier_series; i <= number_of_terms_in_fourier_series; ++i )
			sum += fourier_series_coefficient_c_n( i ) * std::exp( static_cast<std::complex<double>>(static_cast<double>(i) * argument) * imaginary_unit  );
		return sum;
	}

	
} // namespace frequency_methods_lab_1