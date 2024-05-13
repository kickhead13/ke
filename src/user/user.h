#ifndef KE_USER_H
#define KE_USER_H
#include "../term/term.h"
#include "../term/tblinkedlist.h"

struct term_window;

enum ke_umode{
  COMMAND = 0,
  INSERT = 1,
  VISUAL = 2
};

struct user {
  const enum ke_run_status (*handler)(struct user*, struct term_window*);
  enum ke_umode umode;
  struct ke_2x_linked_list *cmdb;
};

const enum ke_run_status uhandler(struct user*, struct term_window*);
const enum ke_run_status chandler(struct user*, struct term_window*);
const enum ke_run_status ihandler(struct user*, struct term_window*);
const enum ke_run_status vhandler(struct user*, struct term_window*);
struct user *get_user();

#endif
