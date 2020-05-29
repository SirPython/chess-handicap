#include "chess-handicap.h"

void uci_init(subproc uci) {
    char *_t = NULL;

    //recv(uci, &_t);
    send(uci, "uci\n");
    recv(uci, &_t);
    send(uci, "setoption name UCI_LimitStrength value true\n");
    send(uci, "setoption name UCI_Elo value 2850\n");
    send(uci, "setoption name Skill Level value 20\n");
    send(uci, "isready\n");
    recv(uci, &_t);
    send(uci, "ucinewgame\n");
}

void uci_calc(subproc uci, game g) {
    send(uci, "position fen ");
    send(uci, g.fen);
    send(uci, " moves ");
    for(int i = 0; i < g.n_moves; i++ ) {

        send(uci, g.moves[i]);
        send(uci, " ");
    }
    send(uci, "\ngo\n");
}

void uci_read_info(subproc uci, info_block *b) {
    char *buf = NULL;
    char *last = NULL;

    bool done = false;
    while(!done) {
        recv(uci, &buf);

        char *line = strtok(buf, "\n");
        while(line != NULL) {
            if(line[0] == 'b') {
                b->move = malloc(5 + 1);
                memcpy(b->move, line + 9, 5);
                b->move[6] = '\0';

                printf("%s\n", last);

                char *tok = strtok(last, " "); // this is a lame way to do this... there is string searching...
                while(tok != NULL) {
                    if(strcmp(tok, "cp") == 0) {
                        b->cp = strtol(strtok(NULL, " "), NULL, 10);
                    } else
                    if(strcmp(tok, "mate") == 0) {
                        tok = strtok(NULL, " ");
                        if(strtol(tok, NULL, 10) > 0) {
                            b->mate = true;
                        }
                    }

                    tok = strtok(NULL, " ");
                }



                done = true;
                break;
            } else {
                last = line;
            }

            line = strtok(NULL, "\n");
        }
    }
}

void game_init(game *g, char *fen) {
    g->fen = fen;
    g->n_moves = 0;
}
void game_play(game *g, char *move) {
    memcpy(g->moves[g->n_moves], move, 5);
    g->moves[g->n_moves][5] = '\0';
    g->n_moves = g->n_moves + 1;
}