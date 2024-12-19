#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int A[], int low, int high) {
    int pivot = A[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (A[j] <= pivot) {
            i++;
            swap(&A[i], &A[j]);
        }
    }

    swap(&A[i + 1], &A[high]);
    return i + 1;
}

void quickSort(int A[], int low, int high) {
    if (low < high) {
        int pi = partition(A, low, high);
        quickSort(A, low, pi - 1);
        quickSort(A, pi + 1, high);
    }
}

int main() {
    int n = 0;
    FILE *file = fopen("int(100).txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }


    int number;
    while (fscanf(file, "%d", &number) == 1) {
        n++;
    }


    fseek(file, 0, SEEK_SET);

    int *A = (int *)malloc(n * sizeof(int));

    if (A == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d", &A[i]) != 1) {
            printf("Error reading data from the file.\n");
            fclose(file);
            free(A);
            return 1;
        }
    }

    fclose(file);

    clock_t start_time = clock();
    quickSort(A, 0, n - 1);
    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\nSorting took %lf seconds to execute.\n", time_taken);
    free(A);

    return 0;
}
