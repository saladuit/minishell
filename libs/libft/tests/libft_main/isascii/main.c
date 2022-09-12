#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../libft.h"

char the_chars[] = { 0, 0x80, 127 };

#define SIZE sizeof( the_chars ) / sizeof( char )

int main( void )
{
    int i;

    for( i = 0; i < SIZE; i++ ) {
        if( ft_isascii( the_chars[i] ) ) {
            printf( "Char %c is an ASCII character\n",
                the_chars[i] );
        } else {
            printf( "Char %c is not an ASCII character\n",
                the_chars[i] );
        }
    }
    
    return EXIT_SUCCESS;
}