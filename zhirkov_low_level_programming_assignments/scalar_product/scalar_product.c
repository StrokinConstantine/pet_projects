#include <stdio.h>
#include <stdbool.h>

const int g_vector_1[] = {1, 2, 3};
const int g_vector_2[] = {4, 5, 6};



// sizeof works only for statically defined arrays


struct int_bool
{
	int integer;
	bool status;
};

// to do: product overflow
struct int_bool scalar_product( const int* v_1, const int* v_2, const size_t size  )
{
	size_t i;
	struct int_bool scalar_product_with_status = { .integer = 0, .status = true };
	
	if( v_1 == NULL || v_2 == NULL ){
		scalar_product_with_status.status = false;
		return scalar_product_with_status;
	}

	for( i = 0; i < size; i++ )
		scalar_product_with_status.integer += v_1[ i ] * v_2[ i ];
	
	return scalar_product_with_status;
}



int main( void )
{
	
	printf("Product: %d\n", scalar_product( g_vector_1, g_vector_2, sizeof( g_vector_1 ) / sizeof( int ) ).integer );
	printf("Product: %d\n", scalar_product( NULL, g_vector_2, sizeof( g_vector_1 ) / sizeof( int ) ).status );

	return 0;
}