#include "term.h"
#include "../fs/fs.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "cursor.h"
#include "../user/uinput.h"

struct user *r;

void tb_disp(struct term_window *self) {
  ke_term_clear();
  ke_cursor_goto(0,0);
 
  struct winsize ws = (self->ws)(self);
  size_t rows = ws.ws_row;
  size_t line = 0;

  struct ke_2xll_node *head = self->tb->head;
  while(head && line < rows) {
    write(1, head->line, strlen(head->line));
    head = head->next;
    line++;
    if(head) write(1, "\n", 1);
  }
  for(;line < rows; line++){
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

struct ke_2x_linked_list *new_tbllbuff(char *buff, size_t *lastline) {
  struct ke_2x_linked_list *list = 
    (struct ke_2x_linked_list*)malloc(sizeof(struct ke_2x_linked_list));
  list->head = NULL;
  list->tail = NULL;
  list->len = 0;

  size_t iter = 0, len = strlen(buff), lines = count_newlines(buff) + 1;
  char *aux = buff;
  size_t offset = -1;
  for(;iter < lines; iter++) {
    aux = aux + (offset + 1);
    offset = chars_till_newline(aux);
    aux[offset] = '\0';
    insert_ke_2xll(list->len, aux, list);
  }

  *lastline = list->len;
  free(buff);
  return list;
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
  win->tb = new_tbllbuff(file_contents(filename), &(win->lastline));
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

#define TENTH_OF_SECOND 100000
int ke_run(struct term_window *win, struct user *user, char *filename) {
  while((user->handler)(user, win)) {
    (win->display)(win);
    usleep(TENTH_OF_SECOND);
  }
  return 0;
}
