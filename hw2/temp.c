// void switch_node(list *right, list *left, int l, int r, int a, int d)
// {
//     list *tmpr;
//     tmpr->l = right->l;
//     tmpr->r = right->r;
//     tmpr->a = right->a;
//     tmpr->d = right->d;
//     tmpr->i = right->i;
//     tmpr->j = right->j;
//     tmpr->hor = right->hor;
//     tmpr->ver = right->ver;
//     list *tmpl;
//     tmpl->l = left->l;
//     tmpl->r = left->r;
//     tmpl->a = left->a;
//     tmpl->d = left->d;
//     tmpl->i = left->i;
//     tmpl->j = left->j;
//     tmpl->hor = left->hor;
//     tmpl->ver = left->ver;
//     if (l)
//     {
//         right->l = tmpl->l;
//         left->r = tmpr->r;
//         right->l->r = right;
//         left->r->l = left;
//     }
//     else
//     {
//         right->l = tmpr->r;
//         left->r = tmpl->l;
//     }
//     if (r)
//     {
//         right->r = tmpl->r;
//         left->l = tmpr->l;
//         right->r->l = right;
//         left->l->r = left;
//     }
//     else
//     {
//         right->r = tmpr->l;
//         left->l = tmpl->r;
//     }
//     if (a)
//     {
//         right->a = tmpl->a;
//         left->d = tmpr->d;
//         right->a->d = right;
//         left->d->a = left;
//     }
//     else
//     {
//         right->d = tmpr->a;
//         left->a = tmpl->d;
//     }
//     if (d)
//     {
//         right->d = tmpl->d;
//         left->a = tmpr->a;
//         right->d->a = right;
//         left->a->d = left;
//     }
//     else
//     {
//         right->a = tmpr->d;
//         left->d = tmpl->a;
//     }
//     right->i = tmpl->i;
//     right->j = tmpl->j;
//     left->i = tmpr->i;
//     left->j = tmpr->j;
//     // right->hor = left->hor;
//     // right->ver = left->ver;
//     // left->hor = tmp->hor;
//     // left->ver = tmp->ver;
// }

// void print(list *head)
// {
//     list *ver_prev = NULL;
//     list *hor_prev = NULL;
//     list *ver = head;
//     list *hor = head;
//     for (int i = 0; i < N; i++)
//     {
//         hor_prev = NULL;
//         hor = ver;

//         for (int j = 0; j < M; j++)
//         {
//             list *tmp = hor;
//             printf("%d ", hor->t);
//             hor = XOR(hor_prev, hor->hor);
//             hor_prev = tmp;
//         }

//         list *tmp2 = ver;
//         ver = XOR(ver_prev, ver->ver);
//         ver_prev = tmp2;
//         printf("\n");
//     }
// }