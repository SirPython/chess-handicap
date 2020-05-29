#ifndef UCI_H
#define UCI_H

#include "chess-handicap.h"

typedef struct {
    long cp;
    bool mate;
    char *move;
} info_block;
void uci_read_info(subproc uci, info_block *b);
void uci_init(subproc uci);

typedef struct {
    char *fen;
    char moves[256][6];
    size_t n_moves;
} game;
void game_init(game *g, char *fen);
void game_play(game *g, char *move);

void uci_calc(subproc uci, game g);

#endif