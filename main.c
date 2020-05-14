#include "chess-handicap.h"

/**
 * 1. Take a start position
 * 2. Have UCI engines play this position: one starts with modified pos, other
 *   start normal.
 * 3. Run ~100 games or something.
 * 4. Calculate odds of winning
 */

int main(int argc, char **argv) {
    subproc sub;
    load_ipc(argv[1], &sub);

    char *msg = NULL;

    recv(sub, &msg);
    send(sub, "uci\n");
    recv(sub, &msg);
    send(sub, "isready\n");
    recv(sub, &msg);
    send(sub, "ucinewgame\n");
    send(sub, "position startpos\n");
    send(sub, "go\n");

    bool cont = true;
    while(cont) {
        recv(sub, &msg);
        char *line = strtok(msg, "\n");
        while(line != NULL) {
            if(line[0] == 'b') {
                printf("Found: %s\n", line);
                cont = false;
                break;
            }

            line = strtok(NULL, "\n");
        }
    }

    kill_ipc(&sub);
}