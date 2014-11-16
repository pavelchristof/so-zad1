/**
 * Systemy Operacyjne, zadanie nr 1.
 * Autor: Paweł Nowak 347193
 */

#include "socket.h"
#include "worker.h"
#include "err.h"

#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    /* Parse the input. */
    if (argc != 2) {
	fatal("Pascal: invalid number of parameters");
    }

    long row_number = atoi(argv[1]);
    if (row_number <= 0) {
	fatal("Pascal: invalid row number");
    }

    /* Spawn the first worker. */
    socket child_socket = spawn_worker(row_number, 1);

    /* Initialize the computation for each row. */
    for (long i = 1; i <= row_number; ++i) {
	socket_write(child_socket, i == 1 ? 1 : 0);
    }

    /* Collect and print the results. */
    for (long i = 1; i <= row_number; ++i) {
	long val = socket_read(child_socket);
	printf("%ld ", val);
    }
    printf("\n");

    /* Close the socket and wait for the child. */
    socket_close(child_socket);
    if (wait(NULL) == -1) {
	syserr("Pascal: wait failed");
    }

    return 0;
}
