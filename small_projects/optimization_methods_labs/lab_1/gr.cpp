#include <iostream>
#include <cstdint>

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