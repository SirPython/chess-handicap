#include "chess-handicap.h"

/**
 * 1. Take a start position
 * 2. Have UCI engines play this position: one starts with modified pos, other
 *   start normal.
 * 3. Run ~100 games or something.
 * 4. Calculate odds of winning
 */

int main(int argc, char **argv) {
    if(argc < 3) {
        printf("Use: %s [path to UCI engine] [starting position in FEN string]\n", argv[0]);
        return 1;
    }

    subproc uci;
    load_ipc(argv[1], &uci);
    uci_init(uci);

    game g;
    game_init(&g, argv[2]);

    info_block info;
    while(true) {
        uci_calc(uci, g);
        uci_read_info(uci, &info);
        if(info.mate) {
            printf("%s won.\n", g.n_moves % 2 == 0 ? "White" : "Black");
            break;
        } else
        if(info.cp == 0 && info.move[0] == '(') { /* A draw was reached. */
            puts("It's a draw.");
            break;
        }
        game_play(&g, info.move);
    }

    kill_ipc(uci);
    return 0;
}