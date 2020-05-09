#ifndef IPC_H
#define IPC_H

#include "chess-handicap.h"

typedef struct {
    int in;
    int out;
} subproc;

typedef void (*ipc_handler)(subproc);

/**
 * https://stackoverflow.com/questions/6171552/popen-simultaneous-read-and-write
 */
void ipc(char *proc, ipc_handler handler);

/**
 * One function to handle communication with another process
 *
 * Message to send in *send, recieved messed to be put in **recv
 */
void comm(subproc sub, char *send, char **recv);


#endif