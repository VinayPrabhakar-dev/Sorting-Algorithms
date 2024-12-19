#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define INSERTION_SORT_THRESHOLD 16
#define MAX_RECURSION_DEPTH 2 * (sizeof(size_t) * CHAR_BIT)

void swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

int partition(char* arr[], int low, int high) {
    char* pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (strcmp(arr[j], pivot) <= 0) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void insertionSort(char* arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        char *key = arr[i];
        int j = i - 1;
        while (j >= low && strcmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void heapify(char* arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && strcmp(arr[left], arr[largest]) > 0)
        largest = left;
    if (right < n && strcmp(arr[right], arr[largest]) > 0)
        largest = right;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(char* arr[], int low, int high) {
    int n = high - low + 1;
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, low + i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[low], &arr[low + i]);
        heapify(arr, i, low);
    }
}

void introsortUtil(char* arr[], int low, int high, int depthLimit);

void introsort(char* arr[], int low, int high) {
    int depthLimit = MAX_RECURSION_DEPTH * 2;
    introsortUtil(arr, low, high, depthLimit);
}

void introsortUtil(char* arr[], int low, int high, int depthLimit) {
    while (high - low > INSERTION_SORT_THRESHOLD) {
        if (depthLimit == 0) {
            heapSort(arr, low, high);
            return;
        }
        depthLimit--;

        int pivotIndex = partition(arr, low, high);
        introsortUtil(arr, pivotIndex + 1, high, depthLimit);
        high = pivotIndex - 1;
    }

    insertionSort(arr, low, high);
}

int main() {
    int n = 0; // Number of elements to read
    FILE *file = fopen("String(100000).txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1; // Exit with an error code
    }

    // Determine the number of elements in the file
    char buffer[102400];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        n++;
    }

    // Reset the file pointer to the beginning
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the array of strings
    char** arr = (char**)malloc(n * sizeof(char*));

    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1; // Exit with an error code
    }

    // Read the data from the file into the array
    for (int i = 0; i < n; i++) {
        if (fgets(buffer, sizeof(buffer), file) != NULL) {
            // Remove the newline character
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            }
            arr[i] = strdup(buffer);
        } else {
            printf("Error reading data from the file.\n");
            fclose(file);
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            return 1; // Exit with an error code
        }
    }

    fclose(file);

    clock_t start_time = clock();
    introsort(arr, 0, n - 1);
    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print the sorted array of strings
    for (int i = 0; i < n; i++) {
        printf("%s\n", arr[i]);
    }
    printf("Sorting took %lf seconds to execute.\n", time_taken);

    // Free the allocated memory
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
