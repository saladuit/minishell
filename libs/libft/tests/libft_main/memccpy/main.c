#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

char* msg = "This is the string: not copied";

int main( void )
{
    char buffer[29];

    memset( buffer, 'j', 29);
    ft_memccpy( buffer, "zyxwvutsrqponmlkjihgfedcba", 't', 10);

    printf( "%s\n", buffer );
    
    return EXIT_SUCCESS;
}