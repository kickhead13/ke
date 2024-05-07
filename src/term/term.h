#ifndef KE_TERM_H
#define KE_TERM_H
#include <termios.h>
#include <stddef.h>
#include <sys/ioctl.h>
#include <stdio.h>

struct tparams {
  unsigned int disp_line_count:1;
};

struct tbuff {
  char *buff;
  size_t len;
};

size_t buff_len(struct tbuff*); 
struct tbuff *new_tbuff(char*, size_t*);
void tbuff_fill_test(struct tbuff *,char);
size_t count_newlines(char *buff);

struct term_window {
  struct winsize (*ws)(struct term_window*);
  void (*display)(struct term_window*);
  struct tbuff *tb;
  struct tparams *tp;
  size_t lastline;
};

void tb_disp(struct term_window*);
struct winsize get_winsize(struct term_window *);
struct term_window *get_term_window(const char*);
int ke_run(struct term_window *, char *);
void ke_wait(const size_t);

#endif // !KE_TERM_H
