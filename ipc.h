#ifndef IPC_H
#define IPC_H

typedef void (*ipc_handler)(int, int);

void ipc(char *proc, ipc_handler handler);

#endif