#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DEC 257

typedef struct
{
    int number[MAX_DEC];
    int length;
} bigint;
void print(bigint a)
{

    for (int i = a.length - 1; i >= 0; i--)
    {
        printf("%d", a.number[i]);
    }
    printf("\n");
}

int is_bigger(bigint a, bigint b)
{
    // printf("bigger compare : \n");
    // print(a);
    // print(b);
    if (a.length > b.length)
    {
        return 1;
    }
    else if (a.length < b.length)
    {
        return 0;
    }
    else
    {
        for (int i = a.length - 1; i >= 0; i--)
        {
            // printf("i = %d, a %d, b %d\n", i, a.number[i], b.number[i]);
            if (a.number[i] > b.number[i])
            {

                return 1;
            }
            else if (a.number[i] < b.number[i])
            {
                return 0;
            }
        }
    }
    return 0;
}

int is_even(bigint k)
{
    if (k.number[0] % 2 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bigint two_times(bigint a)
{
    int next = 0;
    for (int i = 0; i < a.length; i++)
    {
        int num = a.number[i] * 2;
        if (num >= 10)
        {
            a.number[i] = num - 10 + next;
            next = 1;
        }
        else
        {
            a.number[i] = num + next;
            next = 0;
        }
    }
    if (next == 1)
    {
        a.number[a.length] = 1;
        a.length++;
    }
    return a;
}
bigint multiple(bigint a, int k)
{
    int next = 0;
    for (int i = 0; i < k; i++)
    {
        a = two_times(a);
    }
    return a;
}

bigint two_divide(bigint a)
{
    int next = 0;
    if (a.number[a.length - 1] == 1)
    {
        a.length--;
        next = 1;
    }
    for (int i = a.length - 1; i >= 0; i--)
    {
        a.number[i] += 10 * next;
        if (a.number[i] % 2 == 1)
        {
            a.number[i] -= 1;
            next = 1;
        }
        else
        {
            next = 0;
        }
        a.number[i] /= 2;
    }

    return a;
}

bigint subtraction(bigint n, bigint m)
{
    bigint sub;

    sub.length = m.length;
    for (int i = 0; i < m.length; i++)
    {
        // printf("%d true? %d %d\n", m.number[i], m.number[i] < 0, i >= n.length);
        if (i >= n.length && m.number[i] < 0)
        {
            m.number[i + 1] -= 1;
            sub.number[i] = m.number[i] + 10;
        }
        else if (i >= n.length)
        {
            sub.number[i] = m.number[i];
        }
        else if (m.number[i] >= n.number[i])
        {
            sub.number[i] = m.number[i] - n.number[i];
        }
        else
        {
            m.number[i + 1] -= 1;
            sub.number[i] = m.number[i] + 10 - n.number[i];
        }
    }
    for (int i = m.length - 1; i >= 0; i--)
    {
        if (sub.number[i] == 0)
        {
            sub.length--;
        }
        else
        {
            break;
        }
    }
    return sub;
}

bigint str2int(char *numstr)
{
    int num_list[MAX_DEC];
    bigint num;
    num.length = strlen(numstr);
    for (int i = 0; i < strlen(numstr); i++)
    {
        int out = numstr[i] - '0';
        num.number[strlen(numstr) - i - 1] = out;

        // printf("%d", out);
    }

    return num;
}

int main()
{
    char a[257], b[257];
    int ans;
    scanf("%s %s", a, b);
    bigint numa = str2int(a);
    bigint numb = str2int(b);
    bigint m = numb;
    bigint n = numa;
    if (is_bigger(numa, numb))
    {
        bigint n = numb;
        bigint m = numa;
    }
    int c = 0;
    while (n.length != 0 && m.length != 0)
    {

        // print(m);
        // print(n);
        if (is_even(n) && is_even(m))
        {
            ans++;
            m = two_divide(m);
            n = two_divide(n);
        }
        else if (is_even(n))
        {
            n = two_divide(n);
        }
        else if (is_even(m))
        {
            m = two_divide(m);
        }
        if (is_bigger(n, m))
        {
            // print(m);
            // print(n);

            bigint temp = n;
            n = m;
            m = temp;
        }
        // printf("before sub :\n");
        // print(m);
        // print(n);
        m = subtraction(n, m);
        // printf("after sub  :\n");
        // print(m);
        // print(n);
        // if (c > 20)
        // {
        //     // break;
        // }
        // c++;
    }
    // printf("ans = ");
    print(multiple(n, ans));
    return 0;
}