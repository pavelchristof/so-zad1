/**
 * Systemy Operacyjne, zadanie nr 1.
 * Autor: Paweł Nowak 347193
 */

#include "worker.h"
#include "path.h"
#include "err.h"

#include <linux/limits.h>
#include <stdio.h>

socket spawn_worker(int row_number, int worker_index)
{
    /* Find the worker executable. */
    char exe_dir[PATH_MAX];
    get_executable_dir(exe_dir);

    char worker_path[PATH_MAX];
    if (snprintf(worker_path, PATH_MAX, "%s/W", exe_dir) < 0) {
	fatal("spawn_worker: cannot format worker path");
    }

    /* Start the worker and initialize it. */
    socket worker_socket = socket_exec(worker_path);
    socket_write(worker_socket, row_number);
    socket_write(worker_socket, worker_index);

    return worker_socket;
}
