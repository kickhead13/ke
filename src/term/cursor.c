#include "cursor.h"
#include <stdio.h>
#include <unistd.h>

void ke_term_clear() {
  write(1, "\033[H\033[J", 6); 
}
  
void ke_cursor_goto(size_t x, size_t y) {
  char test[30];
  sprintf(test, "\033[%d;%dH", x, y);
  write(1, test, strlen(test));
}



