#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *max(int l1, int l2, char *n1, char *n2)
{
    if (l1 > l2)
    {
        return n1;
    }
    else if (l1 == l2)
    {
        for (int i = 0, len = strlen(n1); i < len; i++)
        {
            if (n1[i] > n2[i])
                return n1;
            else if (n1[i] < n2[i])
            {
                return n2;
            }
        }
    }
    else
        return n2;
}

char *min(int l1, int l2, char *n1, char *n2)
{
    if (l1 > l2)
    {
        return n2;
    }
    else if (l1 == l2)
    {
        for (int i = 0, len = strlen(n1); i < len; i++)
        {
            if (n1[i] > n2[i])
                return n2;
            else if (n1[i] < n2[i])
            {
                return n1;
            }
        }
    }
    else
        return n1;
}

int is_all_zero(int a[])
{
    for (int i = 0; i < 257; i++)
    {
        if (a[i] != 0)
            return 0;
    }
    return 1;
}

void divide_two(int *a)
{
    for (int i = 0; i < 256; i++)
    {
        a[i + 1] += (a[i] % 2) * 10;
        a[i] /= 2;
    }
}

void power_two(int *ans)
{
    int carry = 0;
    for (int i = 255; i >= 0; i--)
    {
        ans[i] *= 2;
        ans[i] += carry;
        if (ans[i] >= 10)
        {
            carry = 1;
            ans[i] -= 10;
        }
        else
        {
            carry = 0;
        }
    }
}

int compare(int a[], int b[])
{
    int index_a = 0, index_b = 0;
    while (a[index_a] == 0)
    {
        index_a++;
    }
    while (b[index_b] == 0)
    {
        index_b++;
    }
    if (index_a > index_b)
    {
        return 1;
    }
    else if (index_a < index_b)
    {
        return 0;
    }
    else
        for (int i = index_a; i < 256; i++)
        {
            if (a[i] > b[i])
            {
                return 0;
            }
            else if (a[i] < b[i])
            {
                return 1;
            }
        }
    return 0;
}

void swap(int **a, int **b)
{
    int *t = *a;
    *a = *b;
    *b = t;
    return;
}

void sub(int *a, int *b)
{
    for (int i = 255; i >= 0; i--)
    {
        if (a[i] < b[i])
        {
            a[i] += 10;
            a[i - 1]--;
        }
        a[i] -= b[i];
    }
}

void mul(int *a, int *b, int *result)
{
    int carry, sum;
    for (int i = 255; i >= 0; i--)
    {
        carry = 0;
        for (int j = 255; j >= 0; j--)
        {
            sum = a[i] * b[j] + carry + result[i + j + 1];
            result[i + j + 1] = sum % 10;
            carry = sum / 10;
        }
        result[i] += carry;
    }
}

int main()
{
    char n1[257];
    char n2[257];
    scanf("%s%s", n1, n2);
    int len1 = strlen(n1);
    int len2 = strlen(n2);
    char *M = max(len1, len2, n1, n2);
    char *N = min(len1, len2, n1, n2);
    int *m = malloc(sizeof(int) * 257);
    int *n = malloc(sizeof(int) * 257);
    for (int i = 0; i < 257; i++)
        m[i] = n[i] = 0;
    for (int i = 0, len = strlen(M); i < len; i++)
    {
        m[256 + i - len] = M[i] - '0';
    }
    for (int i = 0, len = strlen(N); i < len; i++)
    {
        n[256 + i - len] = N[i] - '0';
    }

    int ans[257] = {0};
    ans[255] = 1;
    int carry = 0;

    while (is_all_zero(m) == 0 && is_all_zero(n) == 0)
    {
        if (m[255] % 2 == 0 && n[255] % 2 == 0)
        {
            divide_two(m);
            divide_two(n);
            power_two(ans);
        }
        else if (m[255] % 2 == 0)
        {
            divide_two(m);
        }
        else if (n[255] % 2 == 0)
        {
            divide_two(n);
        }
        if (compare(m, n) == 1)
        {
            swap(&m, &n);
        }
        sub(m, n);

        /*for( int i = 0 ; i < 256 ; i++){
            printf("%d", m[i]);
        }
        printf("\n");
        for( int i = 0 ; i < 256 ; i++){
            printf("%d", n[i]);
        }
        printf("\n");
        */
    }
    int result[515] = {0};
    mul(n, ans, result);
    int index = 0;
    while (result[index] == 0)
    {
        index++;
    }
    int final[515] = {0};
    for (int i = 0; i < 515; i++)
    {
        if (index + i < 515)
            final[i] = result[index + i];
    }
    for (int i = 0; i < 512 - index; i++)
    {
        printf("%d", final[i]);
    }
    return 0;
}