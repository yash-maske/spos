#include <stdio.h>

#define MAX 20

void display(int frames[], int f) {
    for (int i = 0; i < f; i++) {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
        else
            printf("- ");
    }
    printf("\n");
}

// FIFO
void fifo(int pages[], int n, int f) {
    int frames[MAX], index = 0, faults = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;

    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % f;
            faults++;
        }
        display(frames, f);
    }
    printf("Total Page Faults (FIFO): %d\n", faults);
}

// LRU
void lru(int pages[], int n, int f) {
    int frames[MAX], used[MAX], time = 0, faults = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;

    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                used[j] = time++;
                break;
            }
        }
        if (!found) {
            int lru_index = 0;
            for (int j = 1; j < f; j++) {
                if (frames[j] == -1 || used[j] < used[lru_index]) {
                    lru_index = j;
                }
            }
            frames[lru_index] = pages[i];
            used[lru_index] = time++;
            faults++;
        }
        display(frames, f);
    }
    printf("Total Page Faults (LRU): %d\n", faults);
}

// Optimal
void optimal(int pages[], int n, int f) {
    int frames[MAX], faults = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;

    printf("\nOptimal Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            int replace = -1, farthest = i + 1;
            for (int j = 0; j < f; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) break;
                }
                if (k > farthest) {
                    farthest = k;
                    replace = j;
                }
                if (k == n) {
                    replace = j;
                    break;
                }
            }
            if (replace == -1) replace = 0;
            frames[replace] = pages[i];
            faults++;
        }
        display(frames, f);
    }
    printf("Total Page Faults (Optimal): %d\n", faults);
}

int main() {
    int pages[MAX], n, f, choice;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    do {
        printf("\nMenu:\n1. FIFO\n2. LRU\n3. Optimal\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: fifo(pages, n, f); break;
            case 2: lru(pages, n, f); break;
            case 3: optimal(pages, n, f); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
