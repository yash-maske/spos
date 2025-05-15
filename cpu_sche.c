#include <stdio.h>

#define MAX 10

int bt[MAX], at[MAX], pr[MAX], wt[MAX], tat[MAX], rt[MAX];
int n;

void input() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority (smaller is higher): ");
        scanf("%d", &pr[i]);
        rt[i] = bt[i];
    }
}

void fcfs() {
    printf("\n--- FCFS ---\n");
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < at[i]) time = at[i];
        wt[i] = time - at[i];
        time += bt[i];
        tat[i] = wt[i] + bt[i];
    }
    printf("PID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], wt[i], tat[i]);
}

void sjf() {
    printf("\n--- SJF (Preemptive) ---\n");
    int time = 0, done = 0, smallest;
    int min, i;
    int finish[MAX] = {0};
    while (done < n) {
        min = 9999;
        smallest = -1;
        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && rt[i] < min) {
                min = rt[i];
                smallest = i;
            }
        }
        if (smallest == -1) {
            time++;
            continue;
        }
        rt[smallest]--;
        if (rt[smallest] == 0) {
            done++;
            int end = time + 1;
            tat[smallest] = end - at[smallest];
            wt[smallest] = tat[smallest] - bt[smallest];
        }
        time++;
    }
    printf("PID\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], wt[i], tat[i]);
}

void priority() {
    printf("\n--- Priority (Non-Preemptive) ---\n");
    int done = 0, time = 0, i, high;
    int finish[MAX] = {0};
    while (done < n) {
        int min = 9999;
        high = -1;
        for (i = 0; i < n; i++) {
            if (at[i] <= time && finish[i] == 0 && pr[i] < min) {
                min = pr[i];
                high = i;
            }
        }
        if (high == -1) {
            time++;
            continue;
        }
        wt[high] = time - at[high];
        time += bt[high];
        tat[high] = wt[high] + bt[high];
        finish[high] = 1;
        done++;
    }
    printf("PID\tAT\tBT\tPR\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], pr[i], wt[i], tat[i]);
}

void round_robin() {
    printf("\n--- Round Robin ---\n");
    int time, tq, done = 0;
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);
    int rem_bt[MAX], finish[MAX] = {0};
    for (int i = 0; i < n; i++) rem_bt[i] = bt[i];
    time = 0;

    while (done < n) {
        int flag = 0;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rem_bt[i] > 0) {
                flag = 1;
                if (rem_bt[i] > tq) {
                    time += tq;
                    rem_bt[i] -= tq;
                } else {
                    time += rem_bt[i];
                    wt[i] = time - bt[i] - at[i];
                    tat[i] = wt[i] + bt[i];
                    rem_bt[i] = 0;
                    done++;
                }
            }
        }
        if (!flag) time++;
    }

    printf("PID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], wt[i], tat[i]);
}

int main() {
    int choice;
    input();
    do {
        printf("\nMenu:\n");
        printf("1. FCFS\n2. SJF (Preemptive)\n3. Priority (Non-Preemptive)\n4. Round Robin\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: fcfs(); break;
            case 2: sjf(); break;
            case 3: priority(); break;
            case 4: round_robin(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);
    return 0;
}
