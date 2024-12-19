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
    int n = 0; // Number of elements to read
    FILE *file = fopen("Int(1000).txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1; // Exit with an error code
    }

    // Determine the number of elements in the file
    int number;
    while (fscanf(file, "%d", &number) == 1) {
        n++;
    }

    // Reset the file pointer to the beginning
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the array
    int *A = (int *)malloc(n * sizeof(int));

    if (A == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1; // Exit with an error code
    }

    // Read the data from the file into the array
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d", &A[i]) != 1) {
            printf("Error reading data from the file.\n");
            fclose(file);
            free(A);
            return 1; // Exit with an error code
        }
    }

    fclose(file);

    clock_t start_time = clock();
    quickSort(A, 0, n - 1);
    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print the sorted array
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\nSorting took %lf seconds to execute.\n", time_taken);
    // Free the allocated memory
    free(A);

    return 0;
}
