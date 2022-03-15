#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

// STRUCTURE

typedef struct lines {
        int count;
        int *line;
} lines;

typedef struct matrix {
        int count_lines;
        lines *mtrx;
} matrix;

// ENTERING INTEGERS

int get_int() {
        char *input = readline("");
        if (input == NULL) {
                free(input);
                return 0;
        }
        if (atoi(input) == 0){
                free(input);
                return 0;
        }
        int output = atoi(input);
        free(input);
        return output;
}

// FREEING UP  MEMORY

int clean (matrix *arr) {
        if (arr == NULL) return 0;
        for (int i = 0; i < arr->count_lines; i++) free(arr->mtrx[i].line);
        free(arr->mtrx);
        arr->count_lines = 0;
        arr->mtrx = NULL;
        return 0;
}

// CHECK LINE SIGN

int is_positive (matrix arr, int row) {
        int *count = arr.mtrx[row].line;
        for (int j = 0; j < arr.mtrx[row].count; j++, count++) {
                if (*count < 0) return 1;
        }
        return 0;
}

// CREATE RESULT ARRAY

int result(matrix *res, matrix *arr) {
        res->mtrx = (lines *) malloc(sizeof(lines));
        res->count_lines = 1;
        res->mtrx[0].line = (int *) malloc(arr->count_lines*sizeof(int));
        res->mtrx[0].count = arr->count_lines;
        for (int i = 0; i < res->mtrx[0].count; i++) {
                if (check_sign(*arr, i) == 0) {
                        res->mtrx[0].line[i] = arr->mtrx[i].line[0];
                } else {
                        res->mtrx[0].line[i] = arr->mtrx[i].line[arr->mtrx[i].count - 1];
                }
        }
        return 1;
}

// INPUT FROM CONSOLE

int input (matrix *arr) {
        int lines_c = 0;
        do {
                printf("Enter number of lines => ");
                lines_c = get_int();
                if (lines_c <= 0) printf("ERROR: Incorrectly set. Try again.");
        } while (lines_c <= 0);
        arr->count_lines = lines_c;
        arr->mtrx = (lines *) calloc(lines_c, sizeof(lines));
        int items = 0;
        for (int i = 0; i < arr->count_lines; i++) {
                do {
                        printf("Enter number of items in line %d => ", i + 1);
                        items = get_int();
                        if (items <= 0) printf("ERROR: Incorrectly set. Try again.");
                } while (items <= 0);
                arr->mtrx[i].count = items;
                int *temp = (int *) malloc(sizeof(int)*items);
                arr->mtrx[i].line = temp;
                printf("Enter items for line\n", i + 1);
                for (int j = 0; j < items; j++, temp++) {
                        printf("Enter %d item => ", j + 1);
                        *temp = get_int();
                }
        }
        return 1;
}

// OUTPUT FUNCTION

int output (const char *print, matrix arr) {
        printf("%s\n", print);
        for (int i = 0; i < arr.count_lines; i++) {
                int *temp = arr.mtrx[i].line;
                for (int j = 0; j < arr.mtrx[i].count; j++, temp++) printf("%d ", *temp);
                printf("\n");
        }
        return 1;
}

// MAIN

int main() {
        matrix arr = {0, NULL};
        matrix res = {0, NULL};
        double out;
        if (input(&arr) == 0) {
                printf("ERROR: Input error. Program is stopped with code 1.\n");
                return 1;
        }
        output("Matrix:", arr);
        result(&res, &arr);
        output("Result:", res);
        clean(&arr);
        clean(&res);
        return 0;
}
