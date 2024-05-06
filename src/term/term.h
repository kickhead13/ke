#ifndef KE_TERM_H
#define KE_TERM_H
#include <termios.h>
#include <stddef.h>
#include <sys/ioctl.h>
#include <stdio.h>

struct tbuff {
  char *buff;
  size_t len;
};

size_t buff_len(struct tbuff*); 
struct tbuff *new_tbuff(size_t);
void tbuff_fill_test(struct tbuff *,char);

struct term_window {
  struct winsize (*ws)(struct term_window*);
  void (*display)(struct term_window*);
  struct tbuff *tb;
};

void disptbuff(struct term_window*);
struct winsize get_winsize(struct term_window *);
struct term_window *get_term_window();
int ke_run(struct term_window *, char *);

#define KE_WAIT(cycles)  for(size_t clock = 0; clock < (cycles); clock++){ clock += 1; clock -= 1;}


#endif // !KE_TERM_H
