#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void heapify(double A[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A[left] > A[largest])
        largest = left;

    if (right < n && A[right] > A[largest])
        largest = right;

    if (largest != i) {
        double temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;

        heapify(A, n, largest);
    }
}

void heapSort(double A[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(A, n, i);

    for (int i = n - 1; i > 0; i--) {
        double temp = A[0];
        A[0] = A[i];
        A[i] = temp;

        heapify(A, i, 0);
    }
}

int main() {
    int n = 0; // Number of elements to read
    FILE *file = fopen("Float(100000).txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1; // Exit with an error code
    }

    // Determine the number of elements in the file
    double number;
    while (fscanf(file, "%lf", &number) == 1) {
        n++;
    }

    // Reset the file pointer to the beginning
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the array
    double *A = (double *)malloc(n * sizeof(double));

    if (A == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1; // Exit with an error code
    }

    // Read the data from the file into the array
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%lf", &A[i]) != 1) {
            printf("Error reading data from the file.\n");
            fclose(file);
            free(A);
            return 1; // Exit with an error code
        }
    }

    fclose(file);

    clock_t start_time = clock();
    heapSort(A, n);
    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print the sorted array
    for (int i = 0; i < n; i++) {
        printf("%.6f ", A[i]);
    }
    printf("\nSorting took %lf seconds to execute.\n", time_taken);

    // Free the allocated memory
    free(A);

    return 0;
}
