/**
 * Systemy Operacyjne, zadanie nr 1.
 * Autor: Paweł Nowak 347193
 */

#ifndef PATH_H
#define PATH_H

/* Finds the current executable path. Buffer size should be PATH_MAX. */
void get_executable_path(char* buffer);

/* Finds the directory that the current executable is located in. 
   Buffer size should be PATH_MAX. */
void get_executable_dir(char* buffer);

#endif
