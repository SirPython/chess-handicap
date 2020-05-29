#include "chess-handicap.h"

void run_game(subproc uci, char *fen);

int main(int argc, char **argv) {
    if(argc < 3) {
        printf("Use: %s [path to UCI engine] [starting position in FEN string]\n", argv[0]);
        return 1;
    }

    subproc uci;
    load_ipc(argv[1], &uci);

    for(int i = 0; i < 10; i++) {
        run_game(uci, argv[2]);
    }

    kill_ipc(uci);


    return 0;
}

void run_game(subproc uci, char *fen) {
    puts("how?");

    uci_init(uci);
    game g;
    game_init(&g, fen);

    info_block info;

    printf("%d\n", info.mate);
    while(true) {
        puts("super brh");
        uci_calc(uci, g);
        uci_read_info(uci, &info);
        if(info.mate) {
            printf("***** %s won.\n", g.n_moves % 2 == 0 ? "Black" : "White");
            break;
        } else
        if(info.cp == 0 && info.move[0] == '(') { /* A draw was reached. */
            puts("***** It's a draw.");
            break;
        }

        printf("%s is playing %s\n", g.n_moves % 2 == 0 ? "Black" : "White", info.move);
        game_play(&g, info.move);
    }
}