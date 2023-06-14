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

void kmp_search(char *text, char *pattern)
{
    int n = strlen(text);
    int m = strlen(pattern);
    int *pi = (int *)malloc(m * sizeof(int));
    compute_prefix_function(pattern, pi);
    int q = 0;
    for (int i = 0; i < n; i++)
    {
        while (q > 0 && pattern[q] != text[i])
        {
            q = pi[q - 1];
        }
        if (pattern[q] == text[i])
        {
            q++;
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
    // scanf("%s", str);
    char text[] = "ABCABCDABABACD";
    char pattern[] = "ABABAC";
    // scanf("%s", str);
    // scanf % c
    kmp_search(text, pattern);
    return 0;
}
