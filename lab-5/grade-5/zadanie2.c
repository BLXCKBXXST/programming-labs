#include <stdio.h>
#include <math.h>

// Задание на оценку 5: Вариант 1
// Записать каждый второй элемент X в массив Y.
// Определить количество простых чисел в каждом массиве.
// Вычислить среднее арифметическое всех элементов массивов X и Y.

void printArray(int arr[], int size) {
    printf("[ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

int isPrime(int num) {
    if (num < 2) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    int limit = (int)sqrt((double)num);
    for (int i = 3; i <= limit; i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int countPrimes(int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (isPrime(arr[i])) count++;
    }
    return count;
}

double average(int arr[], int size) {
    if (size == 0) return 0.0;
    long long sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (double)sum / size;
}

int main() {
    int X[] = {3, 8, 7, 10, 5, 6, 2, 9, 13, 4};
    int n = sizeof(X) / sizeof(X[0]);

    int Y[n / 2 + 1];
    int k = 0;
    for (int i = 1; i < n; i += 2) {
        Y[k++] = X[i];
    }

    printf("Массив X: ");
    printArray(X, n);
    printf("Массив Y (каждый второй элемент X): ");
    printArray(Y, k);

    printf("\nКоличество простых чисел в X: %d\n", countPrimes(X, n));
    printf("Количество простых чисел в Y: %d\n", countPrimes(Y, k));

    printf("\nСреднее арифметическое X: %.2f\n", average(X, n));
    printf("Среднее арифметическое Y: %.2f\n", average(Y, k));

    return 0;
}
