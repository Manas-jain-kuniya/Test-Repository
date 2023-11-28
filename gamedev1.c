#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool distance_calculator(int x, int y, int r){
    if (pow(x, 2) + pow(y,2) > pow(r,2))
        return false;
    else
        return true;
}
