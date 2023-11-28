#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main (void)
{
    string input = get_string("INPUT: ");
    while(strlen(input) != 0)
    {
        printf("%s\n", input);
        input[strlen(input) - 1] = '\0';

    }
}