#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void merge(char* arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    char* L[n1];
    char* R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(char* arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
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
    mergeSort(arr, 0, n - 1);
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
