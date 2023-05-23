#include <stdio.h>
#include <stdlib.h> // malloc / free
#include <memory.h> // memset
typedef struct node
{
    int discount;
    int days;
} node;
typedef struct company
{
    int id;
    long long total_price;
    int child_cnt;
    struct company *child;
    struct company *sibling;
    struct company *last_child;
} company;

void print(node *heap, int len)
{
    for (int k = 1; k <= len; k++)
    {
        printf("%d ", heap[k].discount);
    }
    printf("\n");
}
void Insert(node *heap, int len, node new_node)
{
    int current, target;
    node temp;
    heap[len] = new_node;
    current = len;
    // printf("\n inserting :\n");
    while (current > 1)
    {
        target = current / 2;
        if (heap[current].discount >= heap[target].discount)
            break;
        temp = heap[current];
        heap[current] = heap[target];
        heap[target] = temp;
        current = target;
    }
}
void Delete(node *heap, int len)
{
    int current, target;
    node temp;
    heap[1] = heap[len];
    current = 1;
    len -= 1;
    while (current * 2 <= len)
    {
        int fb = 1;
        if (heap[2 * current].discount < heap[current].discount || ((2 * current + 1) <= len && heap[2 * current + 1].discount < heap[current].discount))
        {
            target = 2 * current;
            if (target + 1 <= len && heap[target + 1].discount < heap[target].discount)
                target += 1;
            temp = heap[current];
            heap[current] = heap[target];
            heap[target] = temp;
            current = target;
        }
        else
        {
            break;
        }
    }
}

void count_total_child_cnt(company *top)
{
    company *temp = top->child;
    while (temp != NULL)
    {
        count_total_child_cnt(temp);
        top->child_cnt += temp->child_cnt;
        temp = temp->sibling;
    }
}

void preprocess(company *top, int *c)
{
    company *temp = top->child;
    top->total_price = c[top->id];
    while (temp != NULL)
    {
        preprocess(temp, c);
        top->total_price += temp->total_price;
        temp = temp->sibling;
    }
    // printf("id : %d price : %d child : %d ", top->id, top->total_price, top->child_cnt);
}

int get_max_under(company *top, int C)
{
    int max = 0;
    company *temp = top->child;
    if (C >= top->total_price)
    {
        return top->child_cnt + 1;
    }
    int now = 0;
    while (temp != NULL)
    {
        now = get_max_under(temp, C);
        if (C >= now && now > max)
        {
            max = now;
        }
        temp = temp->sibling;
    }
    return max;
}

int main()
{
    int N, M, C = 0;

    scanf("%d %d %d", &N, &M, &C);
    int x[N + 1];
    struct company com[N + 1];
    // int child_cnt[N + 1];
    int c[M + 1][N + 1];
    struct node camp[N + 1][M + 1];
    struct node camp_heap[N + 1][M + 1];
    int heap_len[N + 1];
    for (int i = 1; i <= N; i++)
    {
        // child_cnt[i] = 0;
        com[i].id = i;
        com[i].total_price = 0;
        com[i].child_cnt = 0;
        com[i].child = NULL;
        com[i].sibling = NULL;
        com[i].last_child = NULL;
    }
    for (int i = 2; i <= N; i++)
    {
        scanf("%d", &x[i]);
        // child_cnt[x[i]] += 1;
        com[x[i]].child_cnt += 1;
        if (com[x[i]].child == NULL)
        {
            com[x[i]].child = &com[i];
            com[x[i]].last_child = &com[i];
        }
        else
        {
            com[x[i]].last_child->sibling = &com[i];
            com[x[i]].last_child = &com[i];
        }
    }
    for (int j = 1; j <= M; j++)
    {
        for (int i = 1; i <= N; i++)
        {
            int price, day;
            scanf("%d %d", &price, &day);
            camp[i][j].discount = price;
            camp[i][j].days = j + day;
        }
    }
    for (int i = 1; i <= N; i++)
    {
        // printf("company i %d \n", i);
        // printf(" child cnt %d\n", (com[i].child_cnt));
        heap_len[i] = 0;
        for (int j = 1; j <= M; j++)
        {
            heap_len[i]++;
            Insert(camp_heap[i], heap_len[i], camp[i][j]);
            // printf("%d \n", camp_heap[i][1].days);
            while (camp_heap[i][1].days < j)
            {
                Delete(camp_heap[i], heap_len[i]);
                heap_len[i] -= 1;
            }
            // print(camp_heap[i], heap_len[i]);
            c[j][i] = camp_heap[i][1].discount;
        }
    }
    count_total_child_cnt(&com[1]);
    for (int j = 1; j <= M; j++)
    {
        // for (int i = 1; i <= N; i++)
        // {
        //     printf("company i %d \n", i);
        //     printf(" child cnt %d\n", (com[i].child_cnt));
        // }
        preprocess(&com[1], c[j]);
        int max = 0;
        max = get_max_under(&com[1], C);
        printf("%d\n", max);
    }
    return 0;
}