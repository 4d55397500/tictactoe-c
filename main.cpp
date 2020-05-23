#include <iostream>
#include <MacTypes.h>

#define SIZE 3
#define EMPTY 'e'

enum Player {Player1 = 'x', Player2 = 'o'};

struct state {
    char arr[SIZE][SIZE];;
};

void printstate(struct state* s) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c", s->arr[i][j]);
            if ((j + 1) % SIZE == 0) {
                printf("\n");
            } else {
                printf(" ");
            }
        }
    }
}

// a string representation of the state, for
// efficient ordering and lookup
char* staterepr(struct state *s) {
    char *r = (char *) malloc(sizeof(char) * SIZE * SIZE);
    for (int i = 0; i < SIZE * SIZE; i++) {
        r[i] = s->arr[i / SIZE][i % SIZE];
    }
    return r;
}

struct state* statealloc() {
    struct state *s = (struct state*) malloc(sizeof(struct state));
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            s->arr[i][j] = EMPTY;
        }
    }
    return s;
}

bool iswin(struct state *s, Player player) {
    bool row1 = s->arr[0][0] == player && s->arr[0][1] == player && s->arr[0][2] == player;
    bool row2 = s->arr[1][0] == player && s->arr[1][1] == player && s->arr[1][2] == player;
    bool row3 = s->arr[2][0] == player && s->arr[2][1] == player && s->arr[2][2] == player;
    bool col1 = s->arr[0][0] == player && s->arr[1][0] == player && s->arr[2][0] == player;
    bool col2 = s->arr[0][1] == player && s->arr[1][1] == player && s->arr[2][1] == player;
    bool col3 = s->arr[0][2] == player && s->arr[1][2] == player && s->arr[2][2] == player;
    bool diag1 = s->arr[0][0] == player && s->arr[1][1] == player && s->arr[2][2] == player;
    bool diag2 = s->arr[0][2] == player && s->arr[1][1] == player && s->arr[2][0] == player;
    return row1 || row2 || row3 || col1 || col2 || col3 ||diag1 || diag2;
}

bool allfilled(struct state *s) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (s->arr[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

bool gameover(struct state *s) {
    return iswin(s, Player1) || iswin(s, Player2) || allfilled(s);
}

int overscore(struct state *s) {
    if (iswin(s, Player1)) return 1;
    else if (iswin(s, Player2)) return -1;
    else return 0;
}

Player other(Player player) {
    if (player == Player2) return Player1;
    return Player2;
}

bool stalemate(struct state *s) {
    return !iswin(s, Player1) && !iswin(s, Player2) && allfilled(s);
}

struct nextstates {
    struct state states[SIZE*SIZE];
    int n; // number of next states
};

struct nextstates* nextstatesalloc() {
    return (struct nextstates *) malloc(sizeof(nextstates));
}

struct state* nextalloc(struct state *s, Player player, int i, int j) {
    struct state *next = s;
    next->arr[i][j] = player;
    return next;
}

struct nextstates* allnext(struct state *s, Player player) {
    struct nextstates* ns = nextstatesalloc();
    ns->n = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (s->arr[i][j] == EMPTY) {
                ns->states[ns->n] = *nextalloc(s, player, i, j);
                ns->n++;
            }
        }
    }
    return ns;
}

struct scores {
    char *reprs[SIZE * SIZE];
    int n; // number of states scored so far
};

struct scores* scoresalloc() {
    return (struct scores *) malloc(sizeof(struct scores));
}

int minimax(struct state *s, Player player) {
    int best = (player == Player1) ? -100 : 100;
    if (!gameover(s)) {
        struct nextstates *ns = allnext(s, player);
        int nextscore;
        for (int k = 0; k < ns->n; k++) {
            nextscore = minimax(&ns->states[k], other(player));
            if (player == Player1 && nextscore > best) best = nextscore;
            else if (player == Player2 && nextscore < best) best = nextscore;
        }
    } else {
        best = overscore(s);
    }
    return best;
}

int main() {
    struct state* s = statealloc();
    printf("training minimax ...\n");
    int best = minimax(s, Player1);
    printf("%d\n", best);
    return 0;
}

