#include <stdio.h>
#include <stdlib.h>

enum Color
{
    RED,
    BLACK
};

struct Node
{
    int data;
    int id;
    enum Color color;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->id = id;
    newNode->color = RED;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node *bstInsert(struct Node *root, struct Node *newNode)
{
    if (root == NULL)
        return newNode;

    if (newNode->data < root->data)
    {
        root->left = bstInsert(root->left, newNode);
        root->left->parent = root;
    }
    else if (newNode->data > root->data)
    {
        root->right = bstInsert(root->right, newNode);
        root->right->parent = root;
    }

    return root;
}

void leftRotate(struct Node **root, struct Node *node)
{
    struct Node *rightChild = node->right;
    node->right = rightChild->left;

    if (node->right != NULL)
        node->right->parent = node;

    rightChild->parent = node->parent;

    if (node->parent == NULL)
        *root = rightChild;
    else if (node == node->parent->left)
        node->parent->left = rightChild;
    else
        node->parent->right = rightChild;

    rightChild->left = node;
    node->parent = rightChild;
}

void rightRotate(struct Node **root, struct Node *node)
{
    struct Node *leftChild = node->left;
    node->left = leftChild->right;

    if (node->left != NULL)
        node->left->parent = node;

    leftChild->parent = node->parent;

    if (node->parent == NULL)
        *root = leftChild;
    else if (node == node->parent->left)
        node->parent->left = leftChild;
    else
        node->parent->right = leftChild;

    leftChild->right = node;
    node->parent = leftChild;
}

void fixViolation(struct Node **root, struct Node *newNode)
{
    struct Node *parent = NULL;
    struct Node *grandparent = NULL;

    while ((newNode != *root) && (newNode->color != BLACK) &&
           (newNode->parent->color == RED))
    {
        parent = newNode->parent;
        grandparent = newNode->parent->parent;

        if (parent == grandparent->left)
        {
            struct Node *uncle = grandparent->right;

            if (uncle != NULL && uncle->color == RED)
            {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            }
            else
            {
                if (newNode == parent->right)
                {
                    leftRotate(root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }

                rightRotate(root, grandparent);
                int temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                newNode = parent;
            }
        }
        else
        {
            struct Node *uncle = grandparent->left;

            if (uncle != NULL && uncle->color == RED)
            {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            }
            else
            {
                if (newNode == parent->left)
                {
                    rightRotate(root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }

                leftRotate(root, grandparent);
                int temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                newNode = parent;
            }
        }
    }

    (*root)->color = BLACK;
}

void deleteFixUp(struct Node **root, struct Node *node)
{
    while (node != *root && node->color == BLACK)
    {
        if (node == node->parent->left)
        {
            struct Node *sibling = node->parent->right;

            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                node->parent->color = RED;
                leftRotate(root, node->parent);
                sibling = node->parent->right;
            }

            if (sibling->left->color == BLACK && sibling->right->color == BLACK)
            {
                sibling->color = RED;
                node = node->parent;
            }
            else
            {
                if (sibling->right->color == BLACK)
                {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rightRotate(root, sibling);
                    sibling = node->parent->right;
                }

                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->right->color = BLACK;
                leftRotate(root, node->parent);
                node = *root;
            }
        }
        else
        {
            struct Node *sibling = node->parent->left;

            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                node->parent->color = RED;
                rightRotate(root, node->parent);
                sibling = node->parent->left;
            }

            if (sibling->left->color == BLACK && sibling->right->color == BLACK)
            {
                sibling->color = RED;
                node = node->parent;
            }
            else
            {
                if (sibling->left->color == BLACK)
                {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    leftRotate(root, sibling);
                    sibling = node->parent->left;
                }

                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->left->color = BLACK;
                rightRotate(root, node->parent);
                node = *root;
            }
        }
    }

    node->color = BLACK;
}

struct Node *minValueNode(struct Node *node)
{
    struct Node *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

struct Node *bstDelete(struct Node *root, int data)
{
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = bstDelete(root->left, data);
    else if (data > root->data)
        root->right = bstDelete(root->right, data);
    else
    {
        if (root->left == NULL)
        {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        struct Node *temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = bstDelete(root->right, temp->data);
    }

    return root;
}

void deleteNode(struct Node **root, int data)
{
    struct Node *node = bstDelete(*root, data);
    deleteFixUp(root, node);
}

void inorderTraversal(struct Node *root)
{
    if (root == NULL)
        return;

    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

int main()
{

    struct Node *root = NULL;
    int N, M, C = 0;
    int a, b = 0;

    scanf("%d %d", &N, &M);
    struct Node A[N];
    struct Node B[N];
    struct Node save[N];
    for (int i = 0; i < N; i++)
    {

        scanf("%d %d", &a, &b);
        if (a > b)
        {
            A[i].data = a;
            B[i].data = b;
        }
        else
        {
            A[i].data = b;
            B[i].data = a;
        }
        save[N].data = A[i].data - B[i].data;
        root = bstInsert(root, &save[N]);
    }
    inorderTraversal(root);
    int P, t, c, d, e, f, p1, p2;
    for (int i = 0; i < N; i++)
    {

        scanf("%d %d %d %d %d", &t, &c, &d, &e, &f);

        p1 = (c * (P % 1000000007) + d) % 1000000007;
        p2 = (e * (P % 1000000007) + f) % 1000000007;
        if (p1 > p2)
        {
            A[i - 1].data = p1;
            B[i - 1].data = p2;
        }
        else
        {
            A[i - 1].data = p2;
            B[i - 1].data = p1;
        }
    }
    deleteNode(&root, 18);

    return 0;
}
