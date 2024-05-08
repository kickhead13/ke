#ifndef KE_USER_H
#define KE_USER_H
#include "../term/term.h"
#include "../term/tblinkedlist.h"

enum ke_umode{
  COMMAND = 0,
  INSERT = 1,
  VISUAL = 2
};

struct user {
  enum ke_run_status (*handler)(struct user*, struct term_window*);
  enum ke_umode umode;
  struct ke_2x_linked_list *cmdb;
};

enum ke_run_status uhandler(struct user*, struct term_window*);
struct user *get_user();

#endif
