#ifndef KE_TERM_H
#define KE_TERM_H
#include <termios.h>
#include <stddef.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include "tblinkedlist.h"
#include "../user/user.h"

struct user;

struct tparams {
  unsigned int disp_line_count:1;
};

struct ke_2x_linked_list *new_tbllbuff(char*, size_t*);

struct term_window {
  struct winsize (*ws)(struct term_window*);
  void (*display)(struct term_window*);
  struct ke_2x_linked_list *tb;
  struct tparams *tp;
  size_t lastline;
};

void tb_disp(struct term_window*);
struct winsize get_winsize(struct term_window *);
struct term_window *get_term_window(const char*);
int ke_run(struct term_window *, struct user*,char *);
void ke_wait(const size_t);

#endif // !KE_TERM_H
