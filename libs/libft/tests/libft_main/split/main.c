#include <stdio.h> 
#include <string.h> 
#include "../../../include/libft.h"

int main() 
{ 
    char str[] = "   lorem   ipsum dolor     sit amet, consectetur   adipiscing elit. Sed non risus. Suspendisse   "; 
  
    // Returns first token  
    char **token = ft_split(str, ' '); 
    
    // Keep printing tokens while one of the 
    // delimiters present in str[]. 
    while (*token != NULL) 
    { 
        printf("%s\n", *token);
        token++;
    } 
  
    return 0; 
} 
