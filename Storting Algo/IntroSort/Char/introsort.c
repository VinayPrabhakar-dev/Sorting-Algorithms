#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define INSERTION_SORT_THRESHOLD 16
#define MAX_RECURSION_DEPTH 2 * (sizeof(size_t) * CHAR_BIT)

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

int partition(char A[], int low, int high) {
    char pivot = A[high];
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

void insertionSort(char A[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        char key = A[i];
        int j = i - 1;
        while (j >= low && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

void heapify(char A[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && A[left] > A[largest])
        largest = left;
    if (right < n && A[right] > A[largest])
        largest = right;
    if (largest != i) {
        swap(&A[i], &A[largest]);
        heapify(A, n, largest);
    }
}

void heapSort(char A[], int low, int high) {
    int n = high - low + 1;
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(A, n, low + i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(&A[low], &A[low + i]);
        heapify(A, i, low);
    }
}

void introsortUtil(char A[], int low, int high, int depthLimit);

void introsort(char A[], int low, int high) {
    int depthLimit = MAX_RECURSION_DEPTH * 2;
    introsortUtil(A, low, high, depthLimit);
}

void introsortUtil(char A[], int low, int high, int depthLimit) {
    while (high - low > INSERTION_SORT_THRESHOLD) {
        if (depthLimit == 0) {
            // If recursion depth exceeds the limit, switch to heapsort
            heapSort(A, low, high);
            return;
        }
        depthLimit--;

        int pivotIndex = partition(A, low, high);
        introsortUtil(A, pivotIndex + 1, high, depthLimit);
        high = pivotIndex - 1;
    }

    insertionSort(A, low, high);
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
    introsort(A, 0, n - 1);
    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print the sorted array of characters
    for (int i = 0; i < n; i++) {
        printf("%c ", A[i]);
    }
    printf("\nSorting took %lf seconds to execute.\n", time_taken);

    return 0;
}
