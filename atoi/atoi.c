#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    int value = convert(input);
    printf("%i\n", value);


    // correct way
    //int x = 5 * value;
    //printf("%i\n", x);

    // if after that i use x then x will not be input * 5 as input has been changed in my code in function change it becomes only first digit
    //int x = 5*convert(input);
    //printf("%i\n", x);


}

int convert(string input)
{
    // size of the input
    int size = strlen(input);
    // base case
    if (size == 1)
    {
        // when the first digit from left is reached
        int fd = input[size - 1] - 48;
        return fd;
    }
    // last digit int by ascii value
    int ld = input[size - 1] - 48;
    // deleting the last digit
    input[size - 1] = '\0';

    // returning the value
    return 10 * convert(input) + ld;

}