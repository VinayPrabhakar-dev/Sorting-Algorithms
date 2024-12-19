#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(double A[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    double L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = A[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = A[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(double A[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(A, left, mid);
        mergeSort(A, mid + 1, right);

        merge(A, left, mid, right);
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
    mergeSort(A, 0, n - 1);
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
