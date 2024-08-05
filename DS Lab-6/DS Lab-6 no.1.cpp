//Write a program to test if a given relation is Reflexive, symmetric, asymmetric or transitive.
#include <stdio.h>
#define MAX 100

// Function to check if the relation is reflexive
int is_reflexive(int relation[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        if (relation[i][i] != 1) {
            return 0;
        }
    }
    return 1;
}

// Function to check if the relation is symmetric
int is_symmetric(int relation[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (relation[i][j] != relation[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

// Function to check if the relation is asymmetric
int is_asymmetric(int relation[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (relation[i][j] == 1 && relation[j][i] == 1) {
                return 0;
            }
        }
    }
    return 1;
}

// Function to check if the relation is transitive
int is_transitive(int relation[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (relation[i][j] == 1) {
                for (int k = 0; k < n; k++) {
                    if (relation[j][k] == 1 && relation[i][k] != 1) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

int main() {
    int n;
    int relation[MAX][MAX];

    printf("Enter the number of elements in the set (NxN): ");
    scanf("%d", &n);

    printf("Enter the relation matrix (space-separated rows, 0 or 1):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &relation[i][j]);
        }
    }

    if (is_reflexive(relation, n)) {
        printf("The relation is reflexive.\n");
    } else {
        printf("The relation is not reflexive.\n");
    }

    if (is_symmetric(relation, n)) {
        printf("The relation is symmetric.\n");
    } else {
        printf("The relation is not symmetric.\n");
    }

    if (is_asymmetric(relation, n)) {
        printf("The relation is asymmetric.\n");
    } else {
        printf("The relation is not asymmetric.\n");
    }

    if (is_transitive(relation, n)) {
        printf("The relation is transitive.\n");
    } else {
        printf("The relation is not transitive.\n");
    }

    return 0;
}

