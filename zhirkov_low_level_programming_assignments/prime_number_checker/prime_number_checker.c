#include <stdio.h>


int is_prime( unsigned long n )
{
	unsigned long i;
	
	
	for( i = 2; i <= n / 2; i++ )
		if( n % i != 1 )
			return 0;

	return 1;
}


int main( void )
{
	
	return 0;
}