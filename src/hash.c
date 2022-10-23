#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

uint32_t hash(const char *str)
{
    /* hash <- 5381*/
    uint32_t hash = 5381; 
    uint32_t i = 0; /**/
    /* c <- first character of str */
    char c = str[i]; 
    /* while c != '\0' do*/
    while (c != '\0'){ 
        /*hash <- hash * 33 + c */
        hash = hash * 33 + c; 
        i++;
        /* c <- next character of str */
        c = str[i]; 
    }
    return hash; 
}

