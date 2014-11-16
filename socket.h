/**
 * Systemy Operacyjne, zadanie nr 1.
 * Autor: Paweł Nowak 347193
 */

#ifndef SOCKET_H
#define SOCKET_H

typedef struct {
    int in_fd;
    int out_fd;
} socket;

/* Creates a new process with a socket connecting it to the parent. */
socket socket_exec(const char* path);

/* Retrieves a socket connected with the parent process. */
socket socket_init(int argc, char* argv[]);

/* Creates a socket that ignores writes and blocks on reads. */
socket socket_null();

/* Closes a socket. Should be called for both sides of a connection. */
void socket_close(socket s);

/* Writes a long to a socket. */
void socket_write(socket s, long val);

/* Reads a long from a socket. */
long socket_read(socket s);

#endif
