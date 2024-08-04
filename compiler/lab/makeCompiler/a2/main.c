#include <stdio.h>

// To print the characters
int printStr(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        printf("%c", str[i]);
        i++;
    }
    return i;
}

// To read the Integer