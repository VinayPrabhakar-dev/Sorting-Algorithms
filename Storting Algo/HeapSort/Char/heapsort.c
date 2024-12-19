#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void heapify(char A[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A[left] > A[largest])
        largest = left;

    if (right < n && A[right] > A[largest])
        largest = right;

    if (largest != i) {
        char temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;

        heapify(A, n, largest);
    }
}

void heapSort(char A[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(A, n, i);

    for (int i = n - 1; i > 0; i--) {
        char temp = A[0];
        A[0] = A[i];
        A[i] = temp;

        heapify(A, i, 0);
    }
}

int main() {
    char A[102400];  // Array to store characters
    int n = 0;

    // Read data from the file and insert it into the array
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
    heapSort(A, n);
    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print the sorted array of characters
    for (int i = 0; i < n; i++) {
        printf("%c ", A[i]);
    }
    printf("\nSorting took %lf seconds to execute.\n", time_taken);

    return 0;
}
