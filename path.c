/**
 * Systemy Operacyjne, zadanie nr 1.
 * Autor: Paweł Nowak 347193
 */

#include "path.h"
#include "err.h"

#include <linux/limits.h>
#include <libgen.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void get_executable_path(char* buffer)
{
    pid_t pid = getpid();

    char proc_exe[PATH_MAX];
    if (snprintf(proc_exe, PATH_MAX, "/proc/%d/exe", pid) < 0) {
	fatal("get_executable_path: cannot format path");
    }

    if (readlink(proc_exe, buffer, PATH_MAX) == -1) {
	syserr("get_executable_path: readlink failed with %s", proc_exe);
    }
}

void get_executable_dir(char* buffer)
{
    get_executable_path(buffer);

    /* Documentation about dirname is awful. Is seems that it can modify the buffer,
       or maybe allocate a new string, or return a pointer to some static memory...
       Copy the returned string into buffer just to be sure. Use memmove because
       strings can overlap. */

    char* dir = dirname(buffer);
    size_t size = strlen(dir) + 1;

    if (size > PATH_MAX) {
	fatal("get_executable_dir: buffer overflow");
    }

    memmove(buffer, dir, size);
}
