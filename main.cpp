#include <iostream>

#define SIZE 3

struct board {
    char arr[SIZE][SIZE];
};


char * state(struct board *bd) {
    char *s = (char *) malloc(sizeof(char) * SIZE * SIZE);
    for (int i = 0; i < SIZE * SIZE; i++) {
        s[i] = bd->arr[i / SIZE][i % SIZE];
    }
    return s;
}


struct board* boardalloc() {
    struct board *bd = (struct board*) malloc(sizeof(struct board));
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            bd->arr[i][j] = 'e';
        }
    }
    return bd;
}

void printboard(struct board* bd) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c", bd->arr[i][j], i, j);
            if ((j + 1) % SIZE == 0) {
                printf("\n");
            } else {
                printf(" ");
            }
        }
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    struct board* bd = boardalloc();
    printboard(bd);
    return 0;
}


