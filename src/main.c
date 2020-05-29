#include <stdio.h>
#include "constants.h"



struct state* randomnext(struct state *s, Player player) {
    struct nextstates *ns = allnext(s, player);
    return &ns->states[rand() % ns->n];
}


void playgame() {
    srand(time(0));
    printf("training minimax ...\n");
    Player player = Player1;
    int best = minimax(statealloc(), player);
    printf("best: %d\n", best);
    //printscores(calcscores);
    struct state *s = statealloc();
    printf("playing game, with player %c using minimax, player %c playing randomly.\n",
            Player1, Player2);
    while (!gameover(s)) {
        if (player == Player1) {
            s = transition(s, player);
        } else {
            s = randomnext(s, player);
            // playing both players from minimax strategy will result in stalemate
            //s = transition(s, player);
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

