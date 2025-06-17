#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/util.h"

#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

void runTest(const char*name,void(*testFunc)()){
    printf("Running test: %s\n",name);
    fflush(stdout);
    testFunc();
    printf("%s PASSED\n",name);
}

void testUtils() {
    int *i1 = malloc(sizeof(int));
    int *i2 = malloc(sizeof(int));
    *i1 = 7;
    *i2 = 5;
    assert(intGreaterThan(i1,i2));
    assert(!intGreaterThan(i2,i1));
    assert(!intEqualTo(i2,i1));
    assert(intSmallerThan(i2,i1));
    free(i1);
    free(i2);
}


int main() {
    runTest("utils.c",testUtils);
}