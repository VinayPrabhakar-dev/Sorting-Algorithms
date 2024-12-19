#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void bubbleSort(char A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                char temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
}

int main() {
    char A[102400];
    int n = 0;

    FILE* file = fopen("Char(100000).txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    while (fscanf(file, " %c", &A[n]) == 1) {
        n++;
    }

    fclose(file);

    clock_t start_time = clock();
    bubbleSort(A, n);
    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    for (int i = 0; i < n; i++) {
        printf("%c ", A[i]);
    }
    printf("\nSorting took %lf seconds to execute.\n", time_taken);

    return 0;
}
