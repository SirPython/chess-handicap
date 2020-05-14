#ifndef IPC_H
#define IPC_H

#include "chess-handicap.h"

typedef struct {
    int in;
    int out;
    pid_t pid;
} subproc;

typedef void (*ipc_handler)(subproc);

/**
 * https://stackoverflow.com/questions/6171552/popen-simultaneous-read-and-write
 */
void load_ipc(char *proc, subproc *sub);
void kill_ipc(subproc *sub);

void send(subproc sub, char *msg);
void recv(subproc sub, char **msg);


#endif