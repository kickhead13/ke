#include <stdio.h>
#include <stdlib.h>
#include "term/term.h"

int main() {

  struct term_window *win = get_term_window();
  tbuff_fill_test(win->tb, 'a'); 
  printf("%d", win->tb->len);
  while(1) {
    //printf("%d\n", ((win->ws)(win)).ws_col);
    (win->display)(win);
  }
  return 0;

} 
