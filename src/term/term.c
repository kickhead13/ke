#include "term.h"
#include "../fs/fs.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

size_t buff_len(struct tbuff *self) {
  return (size_t)(sizeof(self->buff)/sizeof(char));
}

void tb_disp(struct term_window *self) {
  struct winsize ws = (self->ws)(self);
  size_t rows = ws.ws_row;
  size_t line = 0;

  for(;line < self->lastline && line < rows; line++) {
    write(1, (self->tb[line]).buff, strlen((self->tb[line]).buff));
    if(line < rows - 1) write(1, "\n", 1);
  }
  for(;line < rows - 1; line++){
    write(1, "-\n", 2);
  }
}

size_t count_newlines(char *buff) {
  size_t iter = 0, count = 0, len = strlen(buff);
  for(;iter < len; iter++) {
    if(buff[iter] == '\n') count += 1;
  }
  return count;
  if(buff[len-1] == '\n') {
    count -= 1;
    buff[len-1] = '\0';
  }
  return count;
}

size_t chars_till_newline(char *buff) {
  size_t iter = 0, count = 0, len = strlen(buff);
  for(;iter < len; iter++) {
    if(buff[iter] == '\n') return count;
    count += 1;
  }
  return count;
}

struct tbuff *new_tbuff(char *buff, size_t *lastline) {
  size_t lines = count_newlines(buff) + 1;
  *lastline = lines;
  struct tbuff *tb =
    (struct tbuff*)malloc(lines * sizeof(struct tbuff));
  char *aux = buff;
  size_t offset = -1;
  for(size_t iter = 0; iter < lines; iter++) {
    aux = aux + (offset + 1);
    offset = chars_till_newline(aux);
    tb[iter].len = offset;
    tb[iter].buff =
      (char *)malloc((offset+1)*sizeof(char));
    for(size_t bter = 0; bter < offset; bter++) {
      (tb[iter].buff)[bter] = aux[bter];
    }
    (tb[iter].buff)[offset] = '\0';
  }
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

struct term_window *get_term_window(const char *filename) {
  struct term_window *win =
    (struct term_window*)malloc(sizeof(struct term_window));
  win->ws = get_winsize;
  size_t tbter = 0;
  win->tb = new_tbuff(file_contents(filename), &(win->lastline));
  win->display = tb_disp;//disptbuff;
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
