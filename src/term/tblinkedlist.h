#ifndef KE_LINKED_LIST_H
#define KE_LINKED_LIST_H
#include <stddef.h>

struct ke_2xll_node {
  struct ke_2xll_node *next, *prev;
  size_t line_len;
  char *line;
};

struct ke_2x_linked_list {
  size_t len;
  struct ke_2xll_node *head, *tail;
};

void insert_ke_2xll(const size_t pos, char*, struct ke_2x_linked_list*);
void split_node_on_char(struct ke_2xll_node*, struct ke_2x_linked_list*, const char);
void split_whole_list(struct ke_2x_linked_list*, const char);

#endif
