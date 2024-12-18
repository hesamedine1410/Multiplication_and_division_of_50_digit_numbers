#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 50

// Function to multiply two large numbers
void multiply(char num1[], char num2[], char result[]) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int temp_result[MAX_DIGITS * 2] = {0};

    // Multiply each digit of num1 by each digit of num2
    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int product = (num1[i] - '0') * (num2[j] - '0');
            int pos1 = i + j, pos2 = i + j + 1;

            int sum = product + temp_result[pos2];
            temp_result[pos2] = sum % 10;
            temp_result[pos1] += sum / 10;
        }
    }

    // Convert array to string
    int idx = 0, k = 0;
    while (idx < len1 + len2 && temp_result[idx] == 0) idx++;
    for (; idx < len1 + len2; idx++) {
        result[k++] = temp_result[idx] + '0';
    }
    if (k == 0) result[k++] = '0';
    result[k] = '\0';
}

// Function to divide two large numbers
void divide(char num1[], char num2[], char result[]) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    char temp[MAX_DIGITS] = {0};
    int temp_len = 0, k = 0;

    for (int i = 0; i < len1; i++) {
        temp[temp_len++] = num1[i];
        temp[temp_len] = '\0';

        // Find divisibility
        int quotient = 0;
        while (strcmp(temp, num2) >= 0) {
            int borrow = 0;
            for (int j = 0; j < len2 || borrow; j++) {
                int val = (temp[j] - '0') - (j < len2 ? num2[j] - '0' : 0) - borrow;
                borrow = val < 0;
                temp[j] = borrow ? val + 10 + '0' : val + '0';
            }
            while (temp_len > 0 && temp[temp_len - 1] == '0') temp_len--;
            temp[temp_len] = '\0';
            quotient++;
        }

        result[k++] = quotient + '0';
    }

    while (k > 1 && result[0] == '0') memmove(result, result + 1, k--);
    result[k] = '\0';
}

int main() {
    char num1[MAX_DIGITS + 1], num2[MAX_DIGITS + 1];
    char result[MAX_DIGITS * 2 + 1] = {0};

    printf("Enter first 50-digit number: ");
    scanf("%s", num1);
    printf("Enter second 50-digit number: ");
    scanf("%s", num2);

    // Calculate the multiplication
    multiply(num1, num2, result);
    printf("Multiplication Result: %s\n", result);

    // Calculate the division
    memset(result, 0, sizeof(result));
    divide(num1, num2, result);
    printf("Division Result: %s\n", result);

    return 0;
}
