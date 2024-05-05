#include "term.h"
#include <stdlib.h>


size_t buff_len(struct tbuff *self) {
  return (size_t)(sizeof(self->buff)/sizeof(char));
}

void disptbuff(struct term_window *self) {
  struct winsize ws = (self->ws)(self);
  size_t cols = ws.ws_col;
  size_t rows = ws.ws_row;
  
  size_t iter = 0;
  size_t bufflen = self->tb->len;
  for(;iter < bufflen;iter++) {
    if(iter % cols) {
      printf("%c", (self->tb->buff)[iter]);
    } else {
      printf("\n");
    }
  }
}

struct tbuff *new_tbuff(size_t len) {
  struct tbuff *tb =
    (struct tbuff*)malloc(sizeof(struct tbuff));
  tb->len = len;
  tb->buff = (char *)malloc(len * sizeof(char));
  return tb;
}

void tbuff_fill_test(struct tbuff *tb, char c) {
  size_t iter = 0;
  size_t blen = tb->len;
  for(;iter < blen;iter++){
    tb->buff[iter] = c;
  }
}

struct winsize get_winsize(struct term_window *self) {
  struct winsize ws;
  ioctl(0, TIOCGWINSZ, &ws);
  return ws;
}

struct term_window *get_term_window() {
  struct term_window *win =
    (struct term_window*)malloc(sizeof(struct term_window));
  win->ws = get_winsize;
  win->tb = new_tbuff(100);
  win->display = disptbuff;
  return win;
}
