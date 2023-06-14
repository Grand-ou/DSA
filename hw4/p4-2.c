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
    pi[m - 1] = m - 1;
    int k = m - 1;
    for (int i = m - 2; i >= 0; i--)
    {
        while (k < m - 1 && pattern[k] != pattern[i])
        {
            k = pi[k + 1];
        }
        if (pattern[k] == pattern[i])
        {
            k--;
        }
        pi[i] = k;
    }
}
int kmp_search(char *text, char *pattern)
{
    int cnt = 0;
    int n = strlen(text);
    int m = strlen(pattern);
    int *pi = (int *)malloc(m * sizeof(int));
    int *ip = (int *)malloc(m * sizeof(int));
    compute_prefix_function(pattern, pi);
    compute_suffix_function(pattern, ip);
    for (int i = 0; i < m - 1; i++)
    {
        printf("%d,", pi[i]);
    }
    printf("\n");
    for (int i = 0; i < m - 1; i++)
    {
        printf("%d,", ip[i]);
    }
    int q = -1;
    int start = -1;
    int pattern_start = -1;
    int mode = -1;
    for (int i = 0; i < n; i++)
    {
        if (mode == -1)
        {
            if (text[i] == pattern[0])
            {
                if (start < i - m)
                {
                    start = i - m;
                }
                for (int j = i - 1; j > start; j++)
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
        else if (mode == 1)
        {
            if (pattern[q] == text[i])
            {
                q++;
                if (q == m)
                {
                    q = 0;
                }
                cnt += 1;
            }
            else
            {
                mode = 0;
                while (q > 0 && pattern[q] != text[i])
                {
                    q = pi[q - 1];
                }
                if (pattern[q] == text[i])
                {
                    q++;
                }
                if (q == 0)
                {
                    mode = -1;
                }
                else
                {

                    if (start < i - m + q)
                    {
                        start = i - m + q;
                    }
                    for (int j = i - 1; j > start; j++)
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
                }
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
            if (q == pattern_start - 1)
            {
                cnt++;
                mode = 1;
            }
            else if (q == 0)
            {
                mode = -1;
            }
            else
            {

                if (start < i - m + q)
                {
                    start = i - m + q;
                }
                for (int j = i - 1; j > start; j++)
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
            }
        }

        if (q == m)
        {
            printf("Pattern found at index %d\n", i - m + 1);
            q = pi[q - 1];
        }
    }
    free(pi);
    free(ip);
    return cnt;
}

int main()
{
    int N, M;
    // scanf("%d %d", &N, &M);
    // scanf("%s", str);
    char text[] = "ABCABCDABABACD";
    char pattern[] = "ABABAC";
    // scanf("%s", str);
    // scanf %c
    int cnt = kmp_search(text, pattern);
    printf("%d", cnt);
    return 0;
}