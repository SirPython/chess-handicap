#ifndef UCI_H
#define UCI_H

#include "chess-handicap.h"

#define BUF_SIZE 256

/**
 * Reads an entire message from fd, putting the message in **msg and returning
 * the number of bytes read.
 *
 * **msg is null-terminated.
 *
 * It's somehwat inefficient in that it calls realloc a lot. An alternative
 * method could be to allocate more than enough memory and truncate down
 * at the end, but I doubt that would significantly improve performance.
 */
int read_msg(int fd, char **msg);

void uci_interface(int in, int out);

#endif