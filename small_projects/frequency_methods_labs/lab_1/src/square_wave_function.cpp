#include <square_wave_function.h>

#include <constants.h>

#include <complex>


namespace frequency_methods_lab_1
{
	

	std::complex<double> square_wave::value( const std::complex<double>& argument ) const
	{
		double normalized_argument = fmod( argument.real(), 2.0 * PI );
	if ( normalized_argument > PI ) 
        normalized_argument -= 2.0 * PI;   
    else if ( normalized_argument < -1.0 * PI )  
        normalized_argument += 2.0 * PI;
	
	if ( normalized_argument > 0.0 )
		return 1;
	return -1;
	}
	
	std::complex<double> square_wave::fourier_series_coefficient_a_0(  ) const
	{
		return std::complex( 0.0, 0.0 );
	}
	
	std::complex<double> square_wave::fourier_series_coefficient_a_n( uint_fast32_t n ) const
	{
		return std::complex( 0.0, 0.0 );
	}
	
	std::complex<double> square_wave::fourier_series_coefficient_b_n( uint_fast32_t n ) const
	{
		if ( ( n % 2u ) == 0 ) return std::complex( 0.0, 0.0 );
		return std::complex( ( 4.0 / ( static_cast<double>( n )* PI ) ), 0.0 );
	}
	
	std::complex<double> square_wave::fourier_series_coefficient_c_n( int_fast32_t n ) const
	{
		if ( n == 0 ) return std::complex( 0.0 , 0.0 );
		//if ( ( n % 2 ) == 0 ) return std::complex( 0.0, 0.0 );
		//return std::complex( ( -2.0 / ( static_cast<double>( n*n )* PI ) ), 0.0 );
		return std::complex<double>( 0.0, ( cos( PI * static_cast<double>( n ) ) - 1.0 ) / ( PI * static_cast<double>( n ) ) );
	}
	
	std::complex<double> square_wave::sum_of_fourier_series( double argument ) const
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
	
	std::complex<double> square_wave::sum_of_fourier_series_in_complex_form( double argument ) const
	{
		std::complex<double> sum(0.0, 0.0);
		const std::complex<double> imaginary_unit(0.0, 1.0);
		for ( int_fast32_t i = -number_of_terms_in_fourier_series; i <= number_of_terms_in_fourier_series; ++i )
			sum += fourier_series_coefficient_c_n( i ) * std::exp( static_cast<std::complex<double>>(static_cast<double>(i) * argument) * imaginary_unit  );
		return sum;
	}

	
} // namespace frequency_methods_lab_1