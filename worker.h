/**
 * Systemy Operacyjne, zadanie nr 1.
 * Autor: Paweł Nowak 347193
 */

#ifndef WORKER_H
#define WORKER_H

#include "socket.h"

/* Spawns a new worker and connects to it. */
socket spawn_worker(int row_number, int worker_index);

#endif
