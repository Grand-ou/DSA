#include <stdio.h>
#include <stdlib.h> // malloc / free
#include <memory.h> // memset
typedef struct node
{
    int data;
    int id;
    struct node *nxt;
} node;
node *alloc(int id, int data, node *nxt)
{
    node *tmp = (node *)malloc(sizeof(node));
    tmp->id = id;
    tmp->data = data;
    tmp->nxt = nxt;
    return tmp;
}
void print(node *head)
{
    printf("current arena : ");
    while (head != NULL)
    {
        printf(" %d", head->id);
        head = head->nxt;
    }
    printf("\n");
}
void destory(node *head)
{
    if (head != NULL)
    {
        printf(" %d", head->id);
        destory(head->nxt);
        // clean sensitive data.
        memset(head, 0, sizeof(node));
        free(head);
    }
}
int main()
{
    int N, M = 0;

    scanf("%d %d", &N, &M);
    int p = 0;
    node *arena = NULL;
    int d = 0;
    int m = 0;
    for (int i = 0; i < N; i++)
    {
        d = 0;
        scanf("%d", &p);
        printf("Round %d:", (i + 1));
        if (m == 0 || arena->data >= p)
        {
            arena = alloc(i + 1, p, arena);
        }
        else
        {
            d = 1;
            node *a = arena;
            while (a->nxt != NULL)
            {

                if (a->nxt->data >= p)
                {
                    node *tmp = alloc(i + 1, p, alloc(a->nxt->id, a->nxt->data, a->nxt->nxt));
                    a->nxt = NULL;
                    // printf(" %d", arena->id);
                    destory(arena);
                    arena = tmp;
                    break;
                }
                else
                {
                    d++;
                }
                if (a->nxt->nxt == NULL && a->nxt->data < p)
                {

                    printf(" %d", arena->id);
                    destory(arena->nxt);
                    arena = alloc(i + 1, p, NULL);
                    d = m;
                    break;
                }
                a = a->nxt;
            }
        }
        m = m - d + 1;
        // printf(" (M,N) %d, %d ", m, M);
        if (m > M)
        {

            node *tmp = arena;

            while (tmp->nxt->nxt != NULL)
            {
                tmp = tmp->nxt;
            }
            printf(" %d", tmp->nxt->id);
            memset(tmp->nxt, 0, sizeof(node));
            free(tmp->nxt);
            tmp->nxt = NULL;
            m = M;
        }
        printf("\n");
        // print(arena);
    }
    printf("Final:");
    while (arena != NULL)
    {
        printf(" %d", arena->id);
        arena = arena->nxt;
    }
    return 0;
}