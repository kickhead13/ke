#include "user.h"
#include "uinput.h"
#include <stdlib.h>
#include <unistd.h>
#include "../term/term.h"

const enum ke_run_status chandler(struct user *user, struct term_window *win) {
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
        default:
          return QUIT;
      }
      break;
    case i_BUTTON:
      user->umode = INSERT;
      break;
    case q_BUTTON:
      return QUIT;
  }
  return KEEP_GOING;

}
const enum ke_run_status ihandler(struct user *user, struct term_window *win) {
  char ch = ke_getch();
  switch(ch) {
    case q_BUTTON:
    case CURSE:
      user->umode = COMMAND;
      break;
    default:
      break;
  }
  return KEEP_GOING;
}
const enum ke_run_status vhandler(struct user *user, struct term_window *win) {
  char ch = ke_getch();
  return KEEP_GOING;
}
const enum ke_run_status uhandler(struct user *user, struct term_window *win) {
  switch(user->umode) {
    case COMMAND:
      return chandler(user, win);
    case INSERT:
      return ihandler(user, win);
    case VISUAL:
      return vhandler(user, win);
  }
}

struct user *get_user() {
  struct user *new_user =
    (struct user*)malloc(sizeof(struct user));
  new_user->handler = uhandler;
  new_user->umode = COMMAND; 
  return new_user;
}
