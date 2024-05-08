#include "user.h"
#include "uinput.h"
#include <stdlib.h>
#include <unistd.h>

enum ke_run_status uhandler(struct user *user, struct term_window *win) {
  char ch = ke_getch();
  switch(ch) {
    case U_ARROW:
      win->tb->head = win->tb->head->next;
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
