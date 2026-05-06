#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

typedef struct node NODE;

// Create node
NODE* create(int x) {
    NODE* newnode = (NODE*)malloc(sizeof(NODE));
    newnode->data = x;
    newnode->left = newnode->right = NULL;
    return newnode;
}

// Insert into BST
NODE* insert(NODE* root, int x) {
    if (root == NULL)
        return create(x);

    if (x < root->data)
        root->left = insert(root->left, x);
    else if (x > root->data)
        root->right = insert(root->right, x);

    return root;
}

// Inorder traversal without trailing space
void inorder(NODE* root, int *first) {
    if (root == NULL)
        return;

    inorder(root->left, first);

    if (*first) {
        printf("%d", root->data);
        *first = 0;
    } else {
        printf(" %d", root->data);
    }

    inorder(root->right, first);
}

int main() {
    int n, x, insert_val;
    NODE* root = NULL;

    // Read n
    if (scanf("%d", &n) != 1)
        return 0;

    // Invalid input case
    if (n == -1) {
        printf("Invalid input");
        return 0;
    }

    // Read initial nodes
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        root = insert(root, x);
    }

    // Read value to insert
    scanf("%d", &insert_val);
    root = insert(root, insert_val);

    // Print inorder (no trailing space)
    int first = 1;
    inorder(root, &first);

    return 0;
}
