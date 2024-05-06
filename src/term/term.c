#include "term.h"
#include <stdlib.h>
#include <unistd.h>

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
    if(__builtin_expect((iter % cols != 0), 1)) {
      write(1, (self->tb->buff) + iter, 1);
    } else {
      write(1, "\n", 1);
    }
  }
  size_t screen_left = cols * rows;
  for(;iter < screen_left; iter++) {
    if(__builtin_expect((iter % cols != 0), 1)) {
      write(1, " ", 1);
    } else {
      write(1, "\n", 1);
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

void ke_wait(const size_t cycles) {
  for(size_t clock = 0; clock < cycles; clock ++) {
    clock += 1;
    clock -= 1;
  }
}

int ke_run(struct term_window *win, char *filename) {
  while(1) {
    //printf("%d\n", ((win->ws)(win)).ws_col);
    (win->display)(win);
    sleep(1);
  }
  return 0;
}
