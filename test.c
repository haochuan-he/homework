#include <stdio.h>
#include <stdlib.h>

int main()
{
    char in[9];
    fgets(in, 9, stdin);
    int out[9] = {0};

    out[0] = atoi(in);
    printf("%d  %d", out[0], out[1]);
}

