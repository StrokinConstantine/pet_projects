#include <iostream>
#include <cstdint>
#include <cmath>



double test_function_1( double x )
{
	return  x * ( x * ( x * ( x * ( -5 * x + 4 ) -12 ) + 11 ) -2 ) + 1;
}

double test_function_2( double x )
{
	return -( std::log( x - 2 ) * std::log( x - 2 ) ) + ( std::log( 10 - x ) * std::log( 10 - x ) ) - std::pow( x, 0.2 ); 
}

double test_function_3( double x )
{
	return -3 * x * std::sin( 0.75 * x ) + std::exp( -2.0 * x );
}

double test_function_4( double x )
{
	return std::exp( 3.0 * x ) + 5.0 * std::exp( -2.0 * x );
}

double test_function_5( double x )
{
	return 0.2 * x * std::log( x ) + ( x - 2.3 ) * ( x - 2.3 );
}










double gr( double a, double b, double (*f)( double ) )
{
	static const double k = 0.61803398875;
	static uint16_t N = 0;
	
	
	while ( true )
	{
		double l = b - a;
		double x = a + k * l; 
		double y = b - k * l;
		
		std::cout << a << " " << b << std::endl;
		
		if ( f( x ) > f( y ) )
			b = y;
		else
			a = x;
		
		N++;
		if ( N > 100 )
			return ( a + b ) / 2;
	}
	
	return 0.0;
}


double f( double x )
{
	return x * x - 3 * x + 2;
}

int main()
{
	
	std::cout << gr( 1.0, 100.0, &f ) << std::endl;
	
}