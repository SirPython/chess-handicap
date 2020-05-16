#ifndef UCI_H
#define UCI_H

#include "chess-handicap.h"

#define BUF_SIZE 256

typedef struct {
    char *fen;
    char moves[256][6];
    size_t size;
} game;
void game_init(game *g, char *fen) {
    g->fen = fen;
    g->size = 0;
}


void movelist_add(movelist *list, char *move) {

}

void init_uci(subproc *sub);

#endif