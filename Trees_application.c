#include <stdio.h>
#include <stdlib.h>

struct Node {
    int studentID;
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(int id) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->studentID = id;
    newNode->left   = NULL;
    newNode->right  = NULL;
    return newNode;
}

struct Node* insert(struct Node *root, int id) {
    if (root == NULL) return createNode(id);
    if (id < root->studentID)
        root->left = insert(root->left, id);
    else if (id > root->studentID)
        root->right = insert(root->right, id);
    else
        printf("StudentID %d already exists.\n", id);
    return root;
}

void search(struct Node *root, int id) {
    if (root == NULL) { printf("StudentID %d NOT FOUND.\n", id); return; }
    if (id == root->studentID)      printf("StudentID %d FOUND.\n", id);
    else if (id < root->studentID)  search(root->left, id);
    else                         search(root->right, id);
}

struct Node* findMin(struct Node *root) {
    while (root->left != NULL) root = root->left;
    return root;
}

struct Node* deleteNode(struct Node *root, int id) {
    if (root == NULL) { printf("StudentID %d NOT FOUND.\n", id); return NULL; }

    if (id < root->studentID)
        root->left = deleteNode(root->left, id);
    else if (id > root->studentID)
        root->right = deleteNode(root->right, id);
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root); return NULL;
        } else if (root->left == NULL) {
            struct Node *temp = root->right; free(root); return temp;
        } else if (root->right == NULL) {
            struct Node *temp = root->left; free(root); return temp;
        } else {
            struct Node *successor = findMin(root->right);
            root->studentID = successor->studentID;
            root->right = deleteNode(root->right, successor->studentID);
        }
    }
    return root;
}

void inorder(struct Node *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d  ", root->studentID);
    inorder(root->right);
}

void freeTree(struct Node *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    struct Node *root = NULL;
    int choice, id;

    do {
        printf("\n------- MENU -------\n");
        printf("1. Insert StudentID\n");
        printf("2. Search StudentID\n");
        printf("3. Delete StudentID\n");
        printf("4. Display All (Sorted)\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter StudentID to insert: ");
                scanf("%d", &id);
                root = insert(root, id);
                printf("Inserted %d successfully.\n", id);
                break;
            case 2:
                printf("Enter StudentID to search: ");
                scanf("%d", &id);
                search(root, id);
                break;
            case 3:
                printf("Enter StudentID to delete: ");
                scanf("%d", &id);
                root = deleteNode(root, id);
                printf("Deleted %d successfully.\n", id);
                break;
            case 4:
                if (root == NULL) printf("No records found.\n");
                else { printf("StudentIDs (sorted): "); inorder(root); printf("\n"); }
                break;
            case 5:
                freeTree(root);
                printf("Exiting. Goodbye!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
