#ifndef UCI_H
#define UCI_H

#include "chess-handicap.h"

typedef struct {
    char *cp;
    bool mate;
    char *move;
} info_block;
void uci_read_info(subproc *uci, info_block *b);

typedef struct {
    char *fen;
    char moves[256][6];
    size_t n_moves;
} game;
void game_init(game *g, char *fen);
void game_play(game *g, char *move);

/**
 * k and v are pointers to array of strings.
 *
 * Returns once a value has been found for every key.
 */
void uci_calc(subproc *uci);
void uci_init(subproc *sub);

#endif