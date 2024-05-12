#include "user.h"
#include "uinput.h"
#include <stdlib.h>
#include <unistd.h>
#include "../term/term.h"

const enum ke_run_status uhandler(struct user *user, struct term_window *win) {
  char ch = ke_getch();
  char sch;
  switch(ch) {
    case CURSE:
      sch = ke_getch();
      switch(ke_getch()) {
        case D_ARROW:
          if(win->tb->head && win->tb->head->next != NULL) {
            win->tb->head = win->tb->head->next;
          }
          break;
        case U_ARROW:
          if(win->tb->head && win->tb->head->prev != NULL) {
            win->tb->head = win->tb->head->prev;
          }
          break;
      }
      break;
    case q_BUTTON:
      return QUIT;
  }
  return KEEP_GOING;
}

struct user *get_user() {
  struct user *new_user =
    (struct user*)malloc(sizeof(struct user));
  new_user->handler = uhandler;
  new_user->umode = COMMAND; 
  return new_user;
}
