

#include <stdio.h>
#include <string.h>
#include "util.h"

#define NUMVALS 5

int main()
{
    double vals[NUMVALS] = {1.2, 3, 0.005, 1, 23};

    person me;
    strcpy(me.name, "Apit");
    me.age = 30;

    printf("Mean: %lf\n", getmean(vals, NUMVALS));
    print_person_info(&me);
}
