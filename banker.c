#include <stdio.h>
#include <stdlib.h>

int isSafe(int n, int m, int available[], int max[][m], int allocation[][m]) {
    int work[m], finish[n];
    for (int i = 0; i < m; i++) work[i] = available[i];
    for (int i = 0; i < n; i++) finish[i] = 0;

    int count = 0;
    while (count < n) {
        int found = 0;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int canAllocate = 1;
                for (int r = 0; r < m; r++) {
                    if (max[p][r] - allocation[p][r] > work[r]) {
                        canAllocate = 0;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int r = 0; r < m; r++) work[r] += allocation[p][r];
                    finish[p] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (!found) return 0;  // unsafe
    }
    return 1;  // safe
}

int requestResources(int n, int m, int p, int request[], int available[], int max[][m], int allocation[][m]) {
    // Check if request <= need
    for (int i = 0; i < m; i++) {
        if (request[i] > max[p][i] - allocation[p][i]) {
            printf("Error: Process %d has exceeded its max claim.\n", p);
            return 0;
        }
    }
    // Check if request <= available
    for (int i = 0; i < m; i++) {
        if (request[i] > available[i]) {
            printf("Resources not available; process must wait.\n");
            return 0;
        }
    }

    // Pretend to allocate
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[p][i] += request[i];
    }

    if (isSafe(n, m, available, max, allocation)) {
        printf("Request granted; system is safe.\n");
        return 1;
    } else {
        printf("Request denied; system would be unsafe.\n");
        // Rollback
        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[p][i] -= request[i];
        }
        return 0;
    }
}

void printState(int n, int m, int available[], int max[][m], int allocation[][m]) {
    printf("\nCurrent System State:\n");
    printf("Available Resources: ");
    for (int i = 0; i < m; i++) printf("%d ", available[i]);
    printf("\n");

    printf("Processes Allocation and Max Demand:\n");
    printf("P\tAllocation\tMax\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t", i);
        for (int j = 0; j < m; j++) printf("%d ", allocation[i][j]);
        printf("\t");
        for (int j = 0; j < m; j++) printf("%d ", max[i][j]);
        printf("\n");
    }
}

int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int *available = malloc(m * sizeof(int));
    int **max = malloc(n * sizeof(int *));
    int **allocation = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        max[i] = malloc(m * sizeof(int));
        allocation[i] = malloc(m * sizeof(int));
    }

    printf("Enter available resources:\n");
    for (int i = 0; i < m; i++) scanf("%d", &available[i]);

    printf("Enter max demand matrix (process x resource):\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) scanf("%d", &max[i][j]);
    }

    printf("Enter allocation matrix (process x resource):\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) scanf("%d", &allocation[i][j]);
    }

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Check System Safety\n");
        printf("2. Request Resources\n");
        printf("3. Display System State\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (isSafe(n, m, available, max, allocation))
                printf("System is in a SAFE state.\n");
            else
                printf("System is NOT safe!\n");
        } 
        else if (choice == 2) {
            int p;
            printf("Enter process number making request (0 to %d): ", n - 1);
            scanf("%d", &p);
            if (p < 0 || p >= n) {
                printf("Invalid process number!\n");
                continue;
            }
            int *request = malloc(m * sizeof(int));
            printf("Enter request for each resource:\n");
            for (int i = 0; i < m; i++) scanf("%d", &request[i]);
            requestResources(n, m, p, request, available, max, allocation);
            free(request);
        } 
        else if (choice == 3) {
            printState(n, m, available, max, allocation);
        } 
        else if (choice == 4) {
            printf("Exiting...\n");
        } 
        else {
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(max[i]);
        free(allocation[i]);
    }
    free(max);
    free(allocation);
    free(available);

    return 0;
}
