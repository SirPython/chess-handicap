#include "chess-handicap.h"

double run_game(subproc uci, char *fen);

int main(int argc, char **argv) {
    if(argc < 4) {
        printf("Use: %s [path to UCI engine] [starting position in FEN string] [number of games]\n", argv[0]);
        return 1;
    }

    subproc uci;
    load_ipc(argv[1], &uci);

    long n_games = strtol(argv[3], NULL, 10);
    double white_score = 0.0;
    for(int i = 0; i < n_games; i++) {
        white_score += run_game(uci, argv[2]);
    }

    printf("White's score: %.2f/%ld\n", white_score, n_games);

    kill_ipc(uci);

    return 0;
}

double run_game(subproc uci, char *fen) {
    double ret;

    uci_init(uci);
    game g;
    game_init(&g, fen);

    info_block info;
    while(true) {
        uci_calc(uci, g);
        uci_read_info(uci, &info);
        if(info.mate) {
            ret = g.n_moves % 2 == 0 ? 0.0 : 1.0;
            break;
        } else
        if(info.cp == 0 && info.move[0] == '(') { /* A draw was reached. */
            ret = 0.5;
            break;
        }

        game_play(&g, info.move);
    }

    /* It's wild. If I don't do this, info will represent the same block of
     * memory next call. */
    info.cp = 0;
    info.mate = false;
    free(info.move);

    return ret;
}