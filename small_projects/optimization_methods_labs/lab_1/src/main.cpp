#include <matplot/matplot.h>

//#include <periodic_absolute_value_function.h>

#include <iostream>
#include <cstdint>
#include <cmath>
#include <algorithm>


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




double parabola(double a, double b, double (*f) (double), double epsilon, uint_fast32_t n)
{
	double f_a = f(a);
	double f_b = f(b);
	
	double c = (a + b) / 2;
	
	double f_c = f(c);

	for (uint_fast32_t i = 1; i < n; ++i)
	{
		double u = c - ((c - a) * (c - a) * (f(c) - f(b)) - (c - b) * (c - b) * (f(c) - f(a)))
			/ (2 * ((c - a) * (f(c) - f(b)) - (c - b) * (f(c) - f(a))));
		if (c == b)
			u = b;
			
	//	std::cout << "a: " << a << std::endl;
		//std::cout << "c: " << c << std::endl;
		//std::cout << "b: " << b << std::endl;
		//std::cout << "u: " << u << std::endl;
		double f_u = f(u);
		if (f_u < f_c && u < c)
		{
			b = c;
			f_b = f_c;
			c = u;
			f_c = f_u;
		} else if (f_u > f_c && u < c)
		{
			a = u;
			f_a = f_u;
		} else if (f_u < f_c && u > c)
		{
			a = c;
			f_a = f_c;
			c = u;
			f_c = f_u;
		} else 
		{
			b = u;
			f_b = f_u;
		}
		if (std::fabs(a - c) < epsilon)
		{
			return std::min(a, b);
		}
		
		//std::cout << a << " " << b << std::endl;
	}

	return 0.0;
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
	
	// std::cout << gr( 1.0, 100.0, &f ) << std::endl;
	
	
	std::cout << parabola(1.0, 100.0, &f, 0.0001, 100) << std::endl;
	
	
	double epsilon = 0.00001;
	uint_fast32_t N = 100U;

	std::vector<double> x = matplot::linspace(0.0,100.0, 1.0);
	
	
	for (int i = 0; i < 100; ++i)
	{
		std::cout << x[i] << std::endl;
	}
	
	
	std::vector<double> err;
	
	err.reserve(N);	
	
	for (uint_fast32_t i = 0; i < N; ++i)
	{
		// parabola(1.0, 100.0, &f, epsilon, i);
		
		err[i] =  (parabola(1.0, 100.0, &f, epsilon, i) - 1.5);
		std::cout << err[i];
	}
	
	matplot::plot(x, err);
	
}