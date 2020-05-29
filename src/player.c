
#include "player.h"

enum Player other(enum Player player) {
    if (player == Player2) return Player1;
    return Player2;
}