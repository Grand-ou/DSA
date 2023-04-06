#include <stdio.h>
#include <stdlib.h> // malloc / free
#include <memory.h> // memset

int main()
{
    int N, M = 0;

    scanf("%d %d", &N, &M);
    int p = 0; // current atk
    int atk[2 * M];
    int id[2 * M];
    int first_fill = -1; // eliminating player in round
    int m = 0;           // number of m in arena
    int end = 0;
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &p);
        printf("Round %d:", (i + 1));
        if (m == 0)
        {
            id[0] = i + 1;
            atk[0] = p;
            m = 1;
            end = 0;
        }
        else
        {
            int j = end;
            m += 1;
            while (atk[j] < p)
            {
                printf(" %d", id[j]);
                j--;
                m--;
                if (j < 0)
                {
                    j = 2 * M - 1;
                }
                if (m == 1)
                {
                    break;
                }
            }
            j++;
            if (j == 2 * M)
            {
                j = 0;
            }
            atk[j] = p;
            id[j] = i + 1;
            end = j;
        }
        if (m > M)
        {
            m -= 1;
            int i = end - m;
            if (i < 0)
            {
                i += 2 * M;
            }
            printf(" %d", id[i]);
            // printf(" end %d, m %d, i %d\n", end, m, i);
        }
        printf("\n");
    }
    printf("Final:");
    int i = end;
    while (m > 0)
    {
        m--;
        printf(" %d", id[i]);
        i--;
        if (i < 0)
        {
            i = 2 * M - 1;
        }
    }
    return 0;
}