/**
 * Systemy Operacyjne, zadanie nr 1.
 * Autor: Paweł Nowak 347193
 */

#include "socket.h"
#include "worker.h"
#include "err.h"

#include <stdio.h>
#include <sys/wait.h>

long row_number;
long worker_index;

socket parent_socket;
socket child_socket;

long value;

void compute_row()
{
    /* Send our previous value to the child. */
    socket_write(child_socket, value);

    /* Read the parents previous value. */
    long parent_val = socket_read(parent_socket);

    value += parent_val;
}

/* Collects the results from child workers and passes it to the parent. */
void collect_results()
{
    /* Write our value first. */
    socket_write(parent_socket, value);

    /* Forward the values from child to parent. */
    for (long i = worker_index + 1; i <= row_number; ++i) {
	socket_write(parent_socket, socket_read(child_socket));
    }
}

int main(int argc, char* argv[])
{
    /* Connect to the parent process. */
    parent_socket = socket_init(argc, argv);
    row_number = socket_read(parent_socket);
    worker_index = socket_read(parent_socket);

    /* We start with no child worker and spawn it just before it is needed. */
    child_socket = socket_null();
    for (long i = worker_index; i <= row_number; ++i) {
	if (i == worker_index + 1) {
	    socket_close(child_socket);
	    child_socket = spawn_worker(row_number, worker_index + 1);
	}
	compute_row();
    }
    collect_results();

    /* Close the sockets and wait for the child. */
    socket_close(parent_socket);
    socket_close(child_socket);
    if (row_number != worker_index && wait(NULL) == -1) {
	syserr("W: wait failed");
    }

    return 0;
}
