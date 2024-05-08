#ifndef KE_CURSOR_H
#define KE_CURSOR_H
#include <unistd.h>
#include <string.h>

void ke_cursor_goto(size_t, size_t);
void ke_term_clear();

#endif
