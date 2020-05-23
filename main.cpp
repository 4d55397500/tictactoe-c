#include <iostream>
#include <MacTypes.h>
#include <search.h>

#define SIZE 3
#define EMPTY 'e'
#define BIGNUM 100
#define MAXNUMSTATES 10000

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
    struct state *next = statealloc();
    for (int q = 0; q < SIZE; q++) {
        for (int v = 0; v < SIZE; v++) {
            next ->arr[q][v] = s->arr[q][v];
        }
    }
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
    char *reprs[MAXNUMSTATES];
    int scores[MAXNUMSTATES];
    int n; // number of states scored so far
};

// tbd
void sortscores(struct scores *sc) {}

int lookupscore(struct scores *sc, struct state *s) {
    char *r = staterepr(s);
    for (int i = 0; i < sc->n; i++) {
        if (strcmp(r, sc->reprs[i]) == 0) {
            return sc->scores[i];
        }
    }
    return BIGNUM;
}

void printscores(struct scores *sc) {
    for (int i = 0; i < sc->n; i++) {
        printf("state: %s score: %d\n", sc->reprs[i], sc->scores[i]);
    }
}

struct scores *add(struct scores *sc, struct state *s, int score) {
    sc->reprs[sc->n] = staterepr(s);
    sc->scores[sc->n] = score;
    sc->n++;
    return sc;
}

struct scores* scoresalloc() {
    return (struct scores *) malloc(sizeof(struct scores));
}

static scores *calcscores;

int minimax(struct state *s, Player player) {
    if (calcscores == nullptr) {
        calcscores = scoresalloc();
        calcscores->n = 0;
    }
    int cached = lookupscore(calcscores, s);
    if (cached != BIGNUM) {
        return cached;
    }
    int best = (player == Player1) ? -BIGNUM: BIGNUM;
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
        add(calcscores, s, best);
    }
    return best;
}

struct state* randomnext(struct state *s, Player player) {
    struct nextstates *ns = allnext(s, player);
    return &ns->states[rand() % ns->n];
}

// learned state transition
struct state *transition(struct state *s, Player player) {
    struct nextstates *ns = allnext(s, player);
    struct state* next;
    int nextscore = (player == Player1) ? -BIGNUM: BIGNUM;
    int candidatescore;
    int candidate = 0;
    for (int i = 0; i < ns->n; i++) {
        candidatescore = lookupscore(calcscores, &ns->states[i]);
        if ((player == Player1 && candidatescore > nextscore) ||
        (player == Player2 && candidatescore < nextscore)) {
            nextscore = candidatescore;
            candidate = i;
        }
    }
    return &ns->states[candidate];
}

void playgame() {
    srand(time(0));
    printf("training minimax ...\n");
    Player player = Player1;
    int best = minimax(statealloc(), player);
    printf("best: %d\n", best);
    struct state *s = statealloc();
    printf("playing game, with player %c using minimax, player %c playing randomly.\n",
            Player1, Player2);
    while (!gameover(s)) {
        if (player == Player1) {
            s = transition(s, player);
        } else {
            s = randomnext(s, player);
        }
        printf("player %c played:\n", player);
        printstate(s);
        player = other(player);
    }
    if (iswin(s, Player1)) printf("player %c wins.\n", Player1);
    else if (iswin(s, Player2)) printf("player %c wins.\n", Player2);
    else printf("stalemate.\n");

}

int main() {
    playgame();
    return 0;
}

