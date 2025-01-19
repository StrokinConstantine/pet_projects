#include <stdio.h>


int is_prime( unsigned long n )
{
	unsigned long i;
	
	
	for( i = 2; i <= ( n / 2 ); i++ )
		if( (n % i) == 0 )
			return 0;

	return 1;
}


int main( void )
{
	
	
	printf("%d\n", is_prime( 16 ) );
	printf("%d\n", is_prime( 17 ) );
	printf("%d\n", is_prime( 15 ) );
	
	
	return 0;
}