#ifndef IPC_H
#define IPC_H

#include "chess-handicap.h"

typedef void (*ipc_handler)(int, int);

/**
 * https://stackoverflow.com/questions/6171552/popen-simultaneous-read-and-write
 */
void ipc(char *proc, ipc_handler handler);

#endif