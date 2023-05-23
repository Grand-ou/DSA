#include <stdio.h>
#include <stdlib.h> // malloc / free
#include <stdint.h>
#define XOR(a, b) (list *)((intptr_t)(a) ^ (intptr_t)(b))
int N, M = 0;
typedef struct _list
{
    int u;
    int t;
    int i;
    int j;
    struct _list *l;
    struct _list *r;
    struct _list *a;
    struct _list *d;
    struct _list *ver;
    struct _list *hor;
} list;

int distance(list *a, list *b)
{
    return abs((a->i - b->i) + (a->j - b->j));
}

void rotate_node(list *node)
{
    list tmp;
    tmp.l = node->l;
    tmp.r = node->r;
    tmp.a = node->a;
    tmp.d = node->d;
    node->l = tmp.r;
    node->r = tmp.l;
    node->a = tmp.d;
    node->d = tmp.a;
}

void switch_node(list *right, list *left, int l, int r, int a, int d)
{
    list tmpr;
    tmpr.l = right->l;
    tmpr.r = right->r;
    tmpr.a = right->a;
    tmpr.d = right->d;
    tmpr.i = right->i;
    tmpr.j = right->j;
    tmpr.hor = right->hor;
    tmpr.ver = right->ver;
    list tmpl;
    tmpl.l = left->l;
    tmpl.r = left->r;
    tmpl.a = left->a;
    tmpl.d = left->d;
    tmpl.i = left->i;
    tmpl.j = left->j;
    tmpl.hor = left->hor;
    tmpl.ver = left->ver;
    if (l)
    {
        right->l = tmpl.l;
        left->r = tmpr.r;
        if (right->l != NULL)
        {
            if (right->l->r != left)
                rotate_node(right->l);
            right->l->r = right;
        }
        if (left->r != NULL)
        {
            if (left->r->l != right)
                rotate_node(left->r);
            left->r->l = left;
        }
    }
    else
    {
        right->l = tmpr.r;
        left->r = tmpl.l;
    }
    if (r)
    {
        right->r = tmpl.r;
        left->l = tmpr.l;
        if (right->r != NULL)
        {
            if (right->r->l != left)
                rotate_node(right->r);
            right->r->l = right;
        }
        if (left->l != NULL)
        {
            if (left->l->r != right)
                rotate_node(left->l);
            left->l->r = left;
        }
    }
    else
    {
        right->r = tmpr.l;
        left->l = tmpl.r;
    }
    if (a)
    {

        right->a = tmpl.a;
        left->d = tmpr.d;
        if (right->a != NULL)
        {
            if (right->a->d != left)
                rotate_node(right->a);
            right->a->d = right;
        }
        if (left->d != NULL)
        {
            if (left->d->a != right)
                rotate_node(left->d);
            left->d->a = left;
        }
    }
    else
    {
        right->a = tmpr.d;
        left->d = tmpl.a;
    }
    if (d)
    {
        right->d = tmpl.d;
        left->a = tmpr.a;
        if (right->d != NULL)
        {
            if (right->d->a != left)
                rotate_node(right->d);
            right->d->a = right;
        }
        if (left->a != NULL)
        {
            if (left->a->d != right)
                rotate_node(left->a);
            left->a->d = left;
        }
    }
    else
    {
        right->d = tmpr.a;
        left->a = tmpl.d;
    }
    right->i = tmpl.i;
    right->j = tmpl.j;
    left->i = tmpr.i;
    left->j = tmpr.j;
}

void add_node(list *visit)
{
    if (visit->l != NULL)
        visit->l->r = visit;
    if (visit->r != NULL)
        visit->r->l = visit;
    if (visit->a != NULL)
        visit->a->d = visit;
    if (visit->d != NULL)
        visit->d->a = visit;
}

void delete_node(list *visit)
{
    if (visit->l != NULL)
        visit->l->r = visit->r;
    if (visit->r != NULL)
        visit->r->l = visit->l;
    if (visit->a != NULL)
        visit->a->d = visit->d;
    if (visit->d != NULL)
        visit->d->a = visit->a;
}

void print_race(list *head)
{
    list *ver = head;
    list *hor = head;
    int mode = 0;
    int mode2 = 0;
    for (int i = 0; i < N; i++)
    {
        hor = ver;
        if (mode2 == 1)
            mode = 1;
        else
            mode = 0;

        for (int j = 0; j < M; j++)
        {
            // printf(" i, j : %d %d \n", i, j);
            int id = 20;
            // printf("%d ", mode);s
            printf("%d ", hor->u);
            // if (j < M - 1)
            // {
            //     printf(" r: %d ", hor->r->u);
            // }
            if (mode == 0)
            {
                if (hor->r != NULL && hor->r->r == hor)
                    mode = 1;
                hor = hor->r;
            }
            else if (mode == 1)
            {
                if (hor->l != NULL && hor->l->l == hor)
                    mode = 0;
                hor = hor->l;
            }
        }
        if (mode2 == 0)
        {
            if (ver->d != NULL && ver->d->d == ver)
                mode2 = 1;
            ver = ver->d;
        }
        else if (mode2 == 1)
        {
            if (ver->a != NULL && ver->a->a == ver)
                mode2 = 0;
            ver = ver->a;
        }
        printf("\n");
    }
}

void print_train(list *head)
{
    list *ver_prev = NULL;
    list *hor_prev = NULL;
    list *ver = head;
    list *hor = head;
    for (int i = 0; i < N; i++)
    {
        hor_prev = NULL;
        hor = ver;

        for (int j = 0; j < M; j++)
        {
            list *tmp = hor;
            printf("%d", hor->t);
            if (j != M - 1)
                printf(" ");
            hor = XOR(hor_prev, hor->hor);
            hor_prev = tmp;
        }

        list *tmp2 = ver;
        ver = XOR(ver_prev, ver->ver);
        ver_prev = tmp2;
        if (i != N - 1)
            printf("\n");
    }
}
typedef struct coor
{
    int i;
    int j;
} coor;

int main()
{
    scanf("%d %d", &N, &M);
    int u[N][M];
    int t[N][M];
    list b[N][M];
    list b2[N][M];
    coor rank[N * M + 1];
    list *head = &b[0][0];
    // read data
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            scanf("%d", &u[i][j]);
            rank[u[i][j]].i = i;
            rank[u[i][j]].j = j;
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            scanf("%d", &t[i][j]);
        }
    }
    // draw map
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (i == 0)
            {
                b[i][j].ver = &b[i + 1][j];
                b[i][j].a = NULL;
                b[i][j].d = &b[i + 1][j];
            }
            else if (i == N - 1)
            {
                b[i][j].ver = &b[i - 1][j];
                b[i][j].a = &b[i - 1][j];
                b[i][j].d = NULL;
            }
            else
            {
                b[i][j].ver = XOR(&b[i - 1][j], &b[i + 1][j]);
                b[i][j].a = &b[i - 1][j];
                b[i][j].d = &b[i + 1][j];
            }

            if (j == 0)
            {
                b[i][j].hor = &b[i][j + 1];
                b[i][j].l = NULL;
                b[i][j].r = &b[i][j + 1];
            }
            else if (j == M - 1)
            {
                b[i][j].hor = &b[i][j - 1];
                b[i][j].l = &b[i][j - 1];
                b[i][j].r = NULL;
            }
            else
            {
                b[i][j].hor = XOR(&b[i][j - 1], &b[i][j + 1]);
                b[i][j].l = &b[i][j - 1];
                b[i][j].r = &b[i][j + 1];
            }
            b[i][j].t = t[i][j];
            b[i][j].u = u[i][j];
            b[i][j].i = i;
            b[i][j].j = j;
        }
    }
    // print_train(head);
    int T1, R, T2;
    scanf("%d %d %d", &T1, &R, &T2);
    list *bankrupt[M * N];
    int bankrupt_cnt = 0;
    int last_bankrupt_cnt = 0;
    int r, l, s;
    list *gather;
    list *visit = NULL;

    // first training period
    for (int k = 0; k < T1; k++)
    {
        scanf("%d %d %d", &r, &l, &s);
        int gi = rank[r].i;
        int gj = rank[r].j;
        gather = &b[gi][gj];
        list *visited[l + 1];
        int visited_cnt = 1;
        visited[0] = gather;
        delete_node(gather);
        for (int i = 0; i < l; i++)
        {
            // printf(" i: %d \n", i);
            visit = NULL;
            list *direct[4] = {gather->l, gather->r, gather->a, gather->d};

            int candidate[4] = {0, 0, 0, 0};
            int candidate_cnt = 0;
            int min_rank = M * N + 2;
            int dist = M + N;
            for (int j = 0; j < 4; j++)
            {
                if (direct[j] == NULL)
                {
                    continue;
                }
                // printf("dis : %d, mindis : %d \n", distance(gather, direct[j]), dist);
                if (distance(gather, direct[j]) <= dist)
                {
                    candidate[j] = 1;
                    visit = direct[j];
                    if (j != 0 && distance(gather, direct[j]) < dist)
                    {
                        for (int z = 0; z < j; z++)
                        {
                            candidate[z] = 0;
                            // printf(" %d quit ! \n", direct[j]->u);
                        }
                    }
                    dist = distance(gather, direct[j]);
                }
            }
            for (int j = 0; j < 4; j++)
            {
                if (candidate[j] == 1)
                {
                    // printf("rank : %d, rank : %d \n", direct[j]->u, min_rank);
                    if (min_rank > direct[j]->u)
                    {
                        min_rank = direct[j]->u;
                        visit = direct[j];
                    }
                }
            }

            if (visit == NULL)
            {
                break;
            }
            visit->t -= s;
            if (visit->t <= 0)
            {
                visit->t = 0;
                bankrupt[bankrupt_cnt] = visit;
                bankrupt_cnt++;
            }
            visited[visited_cnt] = visit;
            visited_cnt++;
            delete_node(visit);
            gather = visit;
            // print_train(&b[0][0]);
            // printf("\n");
        }
        for (int i = visited_cnt - 1; i >= 0; i--)
        {
            add_node(visited[i]);
        }
        visited_cnt = 0;
        for (int i = last_bankrupt_cnt; i < bankrupt_cnt; i++)
        {
            // printf("backrupt i: %d \n", i);
            delete_node(bankrupt[i]);
        }
        last_bankrupt_cnt = bankrupt_cnt;
    }

    for (int i = bankrupt_cnt - 1; i >= 0; i--)
    {
        add_node(bankrupt[i]);
    }

    // racing period
    for (int k = 0; k < R; k++)
    {
        scanf("%d %d", &r, &l);
        // printf("day %d\n", k);
        int gi = rank[r].i;
        int gj = rank[r].j;
        gather = &b[gi][gj];
        list *left = gather->l;
        list *right = gather->r;
        list *tmpl;
        list *tmpr;
        printf("gather %d, r %d , l %d\n", gather->u, right->u, left->u);
        printf("walking len : %d\n", (l - 1) / 2 - 1);
        for (int i = 0; i < (l - 1) / 2 - 1; i++)
        {
            printf("walking   %d", i);
            if (left->l != NULL && left->l->l == left)
                rotate_node(left->l);
            if (right->r != NULL && right->r->r == right)
                rotate_node(right->r);
            left = left->l;
            right = right->r;
        }
        printf("winding len : %d\n", (l - 1) * 2);
        for (int i = 0; i < (l - 1) * 2; i++)
        {
            printf("winding   %d\n", i);
            if (right == head)
            {
                head = left;
            }
            else if (left == head)
            {
                head = right;
            }
            tmpr = right;
            tmpl = left;
            // int id = 3;
            // printf("%d r %d\n", b[rank[id].i][rank[id].j].u, b[rank[id].i][rank[id].j].r->u);
            // printf("befor if\n");
            // printf("winding r: %d %d %d %d %d\n", tmpr->u, tmpr->l->u, tmpr->r->u, tmpr->a->u, tmpr->d->u);
            // printf("winding l: %d %d %d %d %d\n", tmpl->u, tmpl->l->u, tmpl->r->u, tmpl->a->u, tmpl->d->u);
            if (i < (l - 1) / 2)
            {
                if (left->a != NULL && left->a->a == left)
                    rotate_node(left->a);
                if (right->d != NULL && right->d->d == right)
                    rotate_node(right->d);
                left = left->a;
                right = right->d;
                printf("1 wind i : %d, r: %d, l: %d\n", i, tmpr->u, tmpl->u);
                switch_node(tmpr, tmpl, 1, 0, 0, 0);
                // printf("19 r %d\n", b[rank[19].i][rank[19].j].r->u);
            }
            else if (i < (l - 1) / 2 + (l - 1))
            {
                if (left->r != NULL && left->r->r == left)
                    rotate_node(left->r);
                if (right->l != NULL && right->l->l == right)
                    rotate_node(right->l);
                left = left->r;
                right = right->l;
                // printf("15 r %d\n", b[rank[15].i][rank[15].j].r->u);
                if (i == (l - 1) / 2)
                {
                    printf("2 wind i : %d, r: %d, l: %d\n", i, tmpr->u, tmpl->u);
                    switch_node(tmpr, tmpl, 1, 0, 1, 0);
                }
                else
                {
                    printf("3 wind i : %d, r: %d, l: %d\n", i, tmpr->u, tmpl->u);
                    switch_node(tmpr, tmpl, 0, 0, 1, 0);
                }
            }
            else
            {
                // printf("rotate");
                // printf("rotate : %d, r: %d, l: %d\n", i, right->a->u, left->d->u);
                if (i < (l - 1) * 2 - 1)
                {
                    // printf("rotate : %d, r: %d, l: %d\n", i, tmpr->u, tmpl->u);
                    if (left->d != NULL && left->d->d == left)
                        rotate_node(left->d);
                    if (right->a != NULL && right->a->a == right)
                        rotate_node(right->a);
                    left = left->d;
                    right = right->a;
                }
                if (i == (l - 1) / 2 + (l - 1))
                {
                    printf("4 wind i : %d, r: %d, l: %d\n", i, tmpr->u, tmpl->u);
                    switch_node(tmpr, tmpl, 0, 1, 1, 0);
                    // if (k == 4)
                    //     printf("19  r %d\n", b[rank[19].i][rank[19].j].r->u);
                }
                else
                {

                    printf("5 wind i : %d, r: %d, l: %d\n", i, tmpr->u, tmpl->u);
                    switch_node(tmpr, tmpl, 0, 1, 0, 0);
                    // printf("done\n");
                }
            }

            // printf("winding r: %d %d %d %d %d\n", tmpr->u, tmpr->l->u, tmpr->r->u, tmpr->a->u, tmpr->d->u);
            // printf("winding l: %d %d %d %d %d\n", tmpl->u, tmpl->l->u, tmpl->r->u, tmpl->a->u, tmpl->d->u);
        }
        // int id = 3;
        // printf("%d r %d\n", b[rank[id].i][rank[id].j].u, b[rank[id].i][rank[id].j].r->u);
        print_race(head);
        printf("\n");
    }

    list *ver = head;
    list *hor = head;
    if (hor->r == NULL)
        rotate_node(hor);
    for (int i = 0; i < N; i++)
    {
        hor = ver;
        for (int j = 0; j < M; j++)
        {
            if (hor->r != NULL && hor->r->r == hor)
                rotate_node(hor->r);
            // printf("%d ", hor->t);
            hor = hor->r;
        }
        ver = ver->d;
        // printf("\n");
    }
    ver = head;
    hor = head;

    bankrupt_cnt = 0;
    for (int i = 0; i < N; i++)
    {
        hor = ver;
        for (int j = 0; j < M; j++)
        {
            if (hor->r != NULL && hor->r->r == hor)
                rotate_node(hor->r);
            // printf("%d ", hor->t);
            b2[i][j].t = hor->t;
            b2[i][j].u = hor->u;

            rank[b2[i][j].u].i = i;
            rank[b2[i][j].u].j = j;
            hor = hor->r;
        }
        ver = ver->d;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (i == 0)
            {
                b[i][j].a = NULL;
                b[i][j].d = &b[i + 1][j];
            }
            else if (i == N - 1)
            {
                b[i][j].a = &b[i - 1][j];
                b[i][j].d = NULL;
            }
            else
            {
                b[i][j].a = &b[i - 1][j];
                b[i][j].d = &b[i + 1][j];
            }

            if (j == 0)
            {
                b[i][j].l = NULL;
                b[i][j].r = &b[i][j + 1];
            }
            else if (j == M - 1)
            {
                b[i][j].l = &b[i][j - 1];
                b[i][j].r = NULL;
            }
            else
            {
                b[i][j].l = &b[i][j - 1];
                b[i][j].r = &b[i][j + 1];
            }
            b[i][j].t = b2[i][j].t;
            b[i][j].u = b2[i][j].u;
            b[i][j].i = i;
            b[i][j].j = j;
            if (b[i][j].t <= 0)
            {
                bankrupt[bankrupt_cnt] = &b[i][j];
                bankrupt_cnt++;
            }
        }
    }

    for (int i = 0; i < bankrupt_cnt; i++)
    {
        // printf("backrupt i: %d \n", i);
        delete_node(bankrupt[i]);
    }
    last_bankrupt_cnt = bankrupt_cnt;
    head = &b[0][0];
    // print_race(head);
    // printf("\n");

    // second training period
    for (int k = 0; k < T2; k++)
    {
        scanf("%d %d %d", &r, &l, &s);
        int gi = rank[r].i;
        int gj = rank[r].j;
        gather = &b[gi][gj];
        list *visited[l + 1];
        int visited_cnt = 1;
        visited[0] = gather;
        delete_node(gather);
        for (int i = 0; i < l; i++)
        {
            // printf(" i: %d \n", i);
            visit = NULL;
            list *direct[4] = {gather->l, gather->r, gather->a, gather->d};

            int candidate[4] = {0, 0, 0, 0};
            int candidate_cnt = 0;
            int min_rank = M * N + 2;
            int dist = M + N;
            for (int j = 0; j < 4; j++)
            {
                if (direct[j] == NULL)
                {
                    continue;
                }
                // printf("dis : %d, mindis : %d \n", distance(gather, direct[j]), dist);
                if (distance(gather, direct[j]) <= dist)
                {
                    candidate[j] = 1;
                    visit = direct[j];
                    if (j != 0 && distance(gather, direct[j]) < dist)
                    {
                        for (int z = 0; z < j; z++)
                        {
                            candidate[z] = 0;
                            // printf(" %d quit ! \n", direct[j]->u);
                        }
                    }
                    dist = distance(gather, direct[j]);
                }
            }
            for (int j = 0; j < 4; j++)
            {
                if (candidate[j] == 1)
                {
                    // printf("rank : %d, rank : %d \n", direct[j]->u, min_rank);
                    if (min_rank > direct[j]->u)
                    {
                        min_rank = direct[j]->u;
                        visit = direct[j];
                    }
                }
            }

            if (visit == NULL)
            {
                break;
            }
            visit->t -= s;
            if (visit->t <= 0)
            {
                visit->t = 0;
                bankrupt[bankrupt_cnt] = visit;
                bankrupt_cnt++;
            }
            visited[visited_cnt] = visit;
            visited_cnt++;
            delete_node(visit);
            gather = visit;
            // print_train(&b[0][0]);
            // printf("\n");
        }
        for (int i = visited_cnt - 1; i >= 0; i--)
        {
            add_node(visited[i]);
        }
        visited_cnt = 0;
        for (int i = last_bankrupt_cnt; i < bankrupt_cnt; i++)
        {
            // printf("backrupt i: %d \n", i);
            delete_node(bankrupt[i]);
        }
        last_bankrupt_cnt = bankrupt_cnt;
    }

    print_train(head);
    // printf("\n");
    return 0;
}