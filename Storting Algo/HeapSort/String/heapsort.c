#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to heapify a subtree rooted with node i which is an index in arr[]
void heapify(char* arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // left = 2*i + 1
    int right = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (left < n && strcmp(arr[left], arr[largest]) > 0)
        largest = left;

    // If right child is larger than largest so far
    if (right < n && strcmp(arr[right], arr[largest]) > 0)
        largest = right;

    // If largest is not root
    if (largest != i) {
        char* temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// main function to do heap sort
void heapSort(char* arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        char* temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int main() {
    int n = 0; // Number of elements to read
    FILE* file = fopen("String(100000).txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Determine the number of elements in the file
    char buffer[102400];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Remove the newline character
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        n++;
    }

    // Reset the file pointer to the beginning
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the array of strings
    char** arr = (char**)malloc(n * sizeof(char*));

    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1;
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
            return 1;
        }
    }

    fclose(file);

    clock_t start_time = clock();
    heapSort(arr, n);
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
