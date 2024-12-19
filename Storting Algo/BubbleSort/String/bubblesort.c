#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void bubbleSort(char* arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                char* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n = 0;
    FILE* file = fopen("String(100000).txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    char buffer[102400];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        n++;
    }

    fseek(file, 0, SEEK_SET);

    char** arr = (char**)malloc(n * sizeof(char*));

    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (fgets(buffer, sizeof(buffer), file) != NULL) {
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
    bubbleSort(arr, n);
    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    for (int i = 0; i < n; i++) {
        printf("%s\n", arr[i]);
    }
    printf("Sorting took %lf seconds to execute.\n", time_taken);

    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
