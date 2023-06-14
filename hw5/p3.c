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
    enum Color color;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
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

void insert(struct Node **root, int data)
{
    struct Node *newNode = createNode(data);
    *root = bstInsert(*root, newNode);
    fixViolation(root, newNode);
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

    insert(&root, 7);
    insert(&root, 3);
    insert(&root, 18);
    insert(&root, 10);
    insert(&root, 22);
    insert(&root, 8);
    insert(&root, 11);
    insert(&root, 26);

    printf("Inorder traversal of the Red-Black Tree: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
