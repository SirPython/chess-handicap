#include "chess-handicap.h"

/**
 * 1. Take a start position
 * 2. Have UCI engines play this position: one starts with modified pos, other
 *   start normal.
 * 3. Run ~100 games or something.
 * 4. Calculate odds of winning
 */

int main(int argc, char **argv) {
    subproc uci;
    load_ipc(argv[1], &uci);

    uci_init(&uci);

    char moves[256][6];
    int n_moves = 0;

    bool whitewins = true;

    bool ended = false;
    while(!ended) {
        white = !white;

        uci_load_pos(argv[1], moves, n_moves);

        uci_calc(&uci);

        bool cont = true;
        while(cont) {
            recv(&uci, &msg);
            char *tok = strtok(msg, " \n");
            while(tok != NULL) {
                if(line[0] == 'b') {
                    memcpy(moves + (n_moves), line + 9, 5);
                    moves[n_moves++][5] = '\0';

                    if(moves[n_moves-1][0] == '(') {
                        ended = true;
                    }
                    cont = false;
                    break;
                }

                if(strcmp(tok, "score")) {

                }

                tok = strtok(NULL, "\n");
            }
        }
    }

    for(int i = 0; i < n_moves; i++) {
        printf("%s\n", moves[i]);
    }

    printf("%s won.\n", whitewins ? "White" : "Black");

    kill_ipc(&uci);
}