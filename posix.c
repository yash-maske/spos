#include <stdio.h>
#include <pthread.h>

// Structure to hold operands and result
typedef struct {
    int a, b;
    int result;
} Operands;

// Thread function for addition
void* add(void* arg) {
    Operands* op = (Operands*) arg;
    op->result = op->a + op->b;
    printf("Addition: %d + %d = %d\n", op->a, op->b, op->result);
    return NULL;
}

// Thread function for subtraction
void* subtract(void* arg) {
    Operands* op = (Operands*) arg;
    op->result = op->a - op->b;
    printf("Subtraction: %d - %d = %d\n", op->a, op->b, op->result);
    return NULL;
}

// Thread function for multiplication
void* multiply(void* arg) {
    Operands* op = (Operands*) arg;
    op->result = op->a * op->b;
    printf("Multiplication: %d * %d = %d\n", op->a, op->b, op->result);
    return NULL;
}

// Thread function for division
void* divide(void* arg) {
    Operands* op = (Operands*) arg;
    if (op->b != 0) {
        op->result = op->a / op->b;
        printf("Division: %d / %d = %d\n", op->a, op->b, op->result);
    } else {
        printf("Division: Division by zero error!\n");
    }
    return NULL;
}

int main() {
    pthread_t tid[4];
    Operands op = {20, 5, 0};

    pthread_create(&tid[0], NULL, add, &op);
    pthread_create(&tid[1], NULL, subtract, &op);
    pthread_create(&tid[2], NULL, multiply, &op);
    pthread_create(&tid[3], NULL, divide, &op);

    for (int i = 0; i < 4; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}
