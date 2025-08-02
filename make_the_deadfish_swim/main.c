#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

size_t get_length(const char *program);
int *parse (const char *program);

int main() {
    const char *program = "idoiido";
    printf("Input: %s\n", program);

    int *result = parse(program);
    size_t array_length = get_length(program);

    printf("Output: ");
    for (size_t i = 0; i < array_length; i++) {
        if (i > 0) printf(", ");
        printf("%d", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}

int *parse (const char *program) {
	// return a heap-allocated int array
	// its length shall be at least equal to
	// the count of 'o' commands in the program
  
    size_t array_length = get_length(program);

    int *result = malloc(array_length * sizeof(int));
    if (!result) return NULL;

    int num = 0;
    size_t pos = 0;

    for (size_t i = 0; program[i] != '\0'; i++) {
        if (program[i] == 'i') {
            num += 1;
        } else if (program[i] == 's') {
            num *= num;
        } else if (program[i] == 'd') {
            num -= 1;
        } else if (program[i] == 'o'){
            result[pos++] = num;
        } else {
            return NULL;
        }
    }

    return result;
}

size_t get_length(const char *program) {
    size_t count = 0;

    for (size_t i = 0; program[i] != '\0'; i++) {
        if (program[i] == 'o') {
            count += 1;
        }
    }
    return count;
}