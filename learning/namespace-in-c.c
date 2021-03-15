// helper.c
static int _add(int a, int b) {
    return a + b;
}

const struct {
    double pi;
    int (*add) (int, int);
} helper = { 3.14, _add };

// helper.h
const struct {
    double pi;
    int (*add) (int, int);
} helper;

// main.c
#include <stdio.h>
#include "helper.h"

int main(){
    printf("3 + 2 = %d\n", helper.add(3, 2));
    printf("pi is %f\n", helper.pi);
}
