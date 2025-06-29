#include <stdio.h>
#include <math.h>

int main(void) {
    // printf("Hello, World!\n");
    // unsigned int h = (unsigned int)log2(1+1);
    // unsigned int millieu = pow(2,2)/2;

    for (int i = 1; i < 10;i++)
    {
        printf("Log de %d = %d\n",i,(int)log2(i));
    }


    // printf("h = %u, millieu = %u\n",h,millieu);
    return 0;
}
