#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void maxHeapify(int A[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A[left] > A[largest]) {
        largest = left;
    }

    if (right < n && A[right] > A[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        maxHeapify(A, n, largest);
    }
}

void heapSort(int A[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(A, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        int temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        maxHeapify(A, i, 0);
    }
}

int main() {
    int n = 0;
    FILE *file = fopen("Int(10000).txt", "r");

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
    heapSort(A, n);
    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\nSorting took %lf seconds to execute.\n", time_taken);

    free(A);

    return 0;
}
