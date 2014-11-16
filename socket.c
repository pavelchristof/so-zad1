/**
 * Systemy Operacyjne, zadanie nr 1.
 * Autor: Paweł Nowak 347193
 */

#include "socket.h"
#include "err.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

socket socket_exec(const char* path)
{
    int parent_to_child_fd[2];
    int child_to_parent_fd[2];

    if (pipe(parent_to_child_fd) == -1 ||
	pipe(child_to_parent_fd) == -1) {
	syserr("socket_exec: cannot create pipe");
    }

    switch(fork()) {
    case -1:
	syserr("socket_exec: fork failed");

    case 0: {
	if (close(parent_to_child_fd[1]) == -1 ||
	    close(child_to_parent_fd[0]) == -1) {
	    syserr("socket_exec: close failed");
	}

	char in_fd[16];
	char out_fd[16];

	if (snprintf(in_fd, 16, "%d", parent_to_child_fd[0]) < 0 ||
	    snprintf(out_fd, 16, "%d", child_to_parent_fd[1]) < 0) {
	    fatal("socket_exec: cannot format pipe fd");
	}

	if (execl(path, path, in_fd, out_fd, (const char*) NULL) == -1) {
	    syserr("socket_exec: execl failed with path \"%s\"", path);
        }
    }
	
    default: {
	if (close(parent_to_child_fd[0]) == -1 ||
	    close(child_to_parent_fd[1]) == -1) {
	    syserr("socket_exec: close failed");
	}

	socket s;
	s.in_fd = child_to_parent_fd[0];
	s.out_fd = parent_to_child_fd[1];
	return s;
    }

    }
}

socket socket_init(int argc, char* argv[])
{
    if (argc != 3) {
	fatal("socket_init: invalid number of arguments");
    }

    socket s;
    s.in_fd = atoi(argv[1]);
    s.out_fd = atoi(argv[2]);
    return s;
}

socket socket_null()
{
    socket s;

    if ((s.in_fd = open("/dev/null", O_RDONLY)) == -1) {
	syserr("socket_null: cannot open /dev/null");
    }

    if ((s.out_fd = open("/dev/null", O_WRONLY)) == -1) {
	syserr("socket_null: cannot open /dev/null");
    }

    return s;
}

void socket_close(socket s)
{
    if (close(s.in_fd) == -1) {
	syserr("socket_close: cannot close in_fd");
    }

    if (close(s.out_fd) == -1) {
	syserr("socket_close: cannot close out_fd");
    }
}

void socket_write(socket s, long val)
{
    if (write(s.out_fd, &val, sizeof(long)) == -1) {
	syserr("socket_write: write failed");
    }
}

long socket_read(socket s)
{
    long val;
    if (read(s.in_fd, &val, sizeof(long)) == -1) {
	syserr("socket_read: read failed");
    }
    return val;
}
