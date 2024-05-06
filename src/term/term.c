#include "term.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

size_t buff_len(struct tbuff *self) {
  return (size_t)(sizeof(self->buff)/sizeof(char));
}

void disptbuff(struct term_window *self) {
  struct winsize ws = (self->ws)(self);
  size_t cols = ws.ws_col;
  size_t rows = ws.ws_row;
  size_t iter = 0;
  size_t bufflen = self->tb->len;
  size_t screen_left = cols * rows;
  size_t linec = 1;
  size_t slinec = 0;

  if(self->tp->disp_line_count) {
    char last_line_str[20], line_str[20];
    sprintf(last_line_str, "%d", self->lastline);
    sprintf(line_str, "%d", linec);
    size_t lciter = 0;
    size_t llsmls = strlen(last_line_str)-strlen(line_str);
    for(;lciter < llsmls; lciter++) {
      write(1, " ", 1);
    }
    write(1, line_str, strlen(line_str));
    write(1, " ", 1);
  }

  for(;iter < bufflen;iter++) {
    if(__builtin_expect((iter % cols != 0 || iter == 0), 1)) {
      write(1, (self->tb->buff) + iter, 1);
      if((self->tb->buff)[iter] == '\n') {
        linec++;
        slinec++;
        if(linec > self->lastline) self->lastline = linec;
        if(self->tp->disp_line_count) {
          char last_line_str[20], line_str[20];
          sprintf(last_line_str, "%d", self->lastline);
          sprintf(line_str, "%d", linec);
          size_t lciter = 0;
          size_t llsmls = strlen(last_line_str)-strlen(line_str);
          for(;lciter < llsmls; lciter++) {
            write(1, " ", 1);
          }
          write(1, line_str, strlen(line_str));
          write(1, " ", 1);
        }
      }
    } else {
      slinec++;
    }
  }
  for(;slinec < rows; slinec++) {
    write(1, "\n", 1);
  }
}

struct tbuff *new_tbuff(size_t len) {
  struct tbuff *tb =
    (struct tbuff*)malloc(sizeof(struct tbuff));
  tb->len = len;
  tb->buff = (char *)malloc(len * sizeof(char));
  strcpy(tb->buff, "testjdsfkjgdsfghkdsfghkdshfgkjdhsfgkjdhs\ntest\ntest");
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

struct tparams *get_tp() {
  struct tparams *ret = 
    (struct tparams *)malloc(sizeof(struct tparams));
  ret->disp_line_count = 1;
  return ret;
}

struct term_window *get_term_window() {
  struct term_window *win =
    (struct term_window*)malloc(sizeof(struct term_window));
  win->ws = get_winsize;
  win->tb = new_tbuff(100);
  win->display = disptbuff;
  win->lastline = 0;
  win->tp = get_tp();
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
    (win->display)(win);
    usleep(100000);
  }
  return 0;
}
