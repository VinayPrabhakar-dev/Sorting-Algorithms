#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(double A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                double temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n = 0;
    FILE *file = fopen("Float(100000).txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    double number;
    while (fscanf(file, "%lf", &number) == 1) {
        n++;
    }

    fseek(file, 0, SEEK_SET);

    double *A = (double *)malloc(n * sizeof(double));

    if (A == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%lf", &A[i]) != 1) {
            printf("Error reading data from the file.\n");
            fclose(file);
            free(A);
            return 1;
        }
    }

    fclose(file);

    clock_t start_time = clock();
    bubbleSort(A, n);
    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    for (int i = 0; i < n; i++) {
        printf("%.6f ", A[i]);
    }
    printf("\nSorting took %lf seconds to execute.\n", time_taken);

    free(A);

    return 0;
}
