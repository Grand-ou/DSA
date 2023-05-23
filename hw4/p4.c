#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compute_prefix_function(char *pattern, int *pi)
{
    int m = strlen(pattern);
    pi[0] = 0;
    int k = 0;
    for (int i = 1; i < m; i++)
    {
        while (k > 0 && pattern[k] != pattern[i])
        {
            k = pi[k - 1];
        }
        if (pattern[k] == pattern[i])
        {
            k++;
        }
        pi[i] = k;
    }
}
void compute_suffix_function(char *pattern, int *pi)
{
    int m = strlen(pattern);
    pi[0] = 0;
    int k = 0;
    for (int i = 1; i < m; i++)
    {
        while (k > 0 && pattern[k] != pattern[i])
        {
            k = pi[k - 1];
        }
        if (pattern[k] == pattern[i])
        {
            k++;
        }
        pi[i] = k;
    }
}
void kmp_search(char *text, char *pattern)
{
    int cnt = 0;
    int n = strlen(text);
    int m = strlen(pattern);
    int *pi = (int *)malloc(m * sizeof(int));
    compute_prefix_function(pattern, pi);
    int q = 0;
    int start = -1;
    int pattern_start = -1;
    int mode = -1;
    for (int i = 0; i < n; i++)
    {
        if (mode == -1)
        {
            if (text[i] == pattern[0])
            {
                int end = start;
                if (i - start > m)
                {
                    end = i - m;
                }
                for (int j = i - 1; j > end; j++)
                {
                    int k = m - (i - j);
                    if (text[j] == pattern[k])
                    {
                        pattern_start = k;
                    }
                    else
                    {
                        break;
                    }
                }
                start = i;
                mode = 0;
            }
        }
        else
        {
            while (q > 0 && pattern[q] != text[i])
            {
                q = pi[q - 1];
            }
            if (pattern[q] == text[i])
            {
                q++;
            }

            if (mode == 0)
            {
                if (q == pattern_start - 1)
                {
                    cnt++;
                    mode = 1;
                }
            }
            else if (mode == 1)
            {
            }
        }

        if (q == m)
        {
            printf("Pattern found at index %d\n", i - m + 1);
            q = pi[q - 1];
        }
    }
    free(pi);
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    // scanf("%s", str);
    char text[] = "BACABCDABABACD";
    char pattern[] = "BACABABAC";
    // scanf("%s", str);
    // scanf %c
    kmp_search(text, pattern);
    return 0;
}
