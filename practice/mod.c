#include <stdio.h>
#include <stdlib.h> // malloc / free
#include <memory.h> // memset
int top = -1;       // 堆疊的頂端
int main()
{

    int N, M = 0;
    while (1)
    {
        scanf("%d", &N);
        int k = (N * 8) % 7;
        int i = 1 + ((2 * N - 2) % 6);
        printf("%d %d", k, i);
    }

    return 0;
}