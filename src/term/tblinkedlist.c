#include "tblinkedlist.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void insert_ke_2xll(const size_t pos, char *line, struct ke_2x_linked_list *list) {
  list->len++;
  struct ke_2xll_node *head = list -> head;
  struct ke_2xll_node *prev = NULL;
  struct ke_2xll_node *new_node =
    (struct ke_2xll_node*)malloc(sizeof(struct ke_2xll_node));
  new_node->line_len = strlen(line);
  new_node->line =
    (char*)malloc((new_node->line_len + 1)*sizeof(char));
  strcpy(new_node->line, line);
  

  if(head == NULL) {
    list->head = new_node;
    list->tail = new_node;
    new_node->next = NULL;
    new_node->prev = NULL;
    return;
  }

  size_t iter = 0;
  while(iter < pos && head) {
    prev = head;
    head = head -> next;
    iter += 1;
  }
  if(head) head -> prev = new_node;
  new_node -> next = head;
  new_node -> prev = prev;
  if(prev) prev->next = new_node;
  if(new_node -> next == NULL) list->tail = new_node;
  if(new_node -> prev == NULL) list->head = new_node; 
}

void split_node_on_char(struct ke_2xll_node *node, struct ke_2x_linked_list *list, const char c) {
  struct ke_2xll_node *next = node->next;

  size_t iter = 0;
  while(iter < node->line_len && node->line[iter] != c) {
    iter += 1;
  }
  if(iter == node->line_len) return; 
  node->line[iter] = '\0';
  
  struct ke_2xll_node *new_node =
    (struct ke_2xll_node*)malloc(sizeof(struct ke_2xll_node));
  new_node->line_len = strlen((node->line) + iter + 1);
  new_node->line = 
    (char*)malloc((new_node->line_len)*sizeof(char));
  strcpy(new_node->line, (node->line) + iter + 1);
  new_node->prev = node;
  new_node->next = node->next;
  node->next = new_node;
  if(next) next->prev = new_node;
  else {
    list->tail = new_node;
  }
  
  node->line_len = strlen(node->line);
  /*
  char *new_line = (char*)realloc(node->line, node->line_len);
  if(new_line) {
    node->line = new_line;
  }
  */
  /*
  write(1, node->line, strlen(node->line));
  write(1, "\n", 1);
  if(list->len == 46) {
    write(1, "!\n!\n!", 5);
    write(1, new_node->line, strlen(new_node->line));
  }*/
  list->len++;
}

void split_whole_list(struct ke_2x_linked_list *list, const char c) {
  struct ke_2xll_node *head = list->head;
  while(head) {
    split_node_on_char(head, list, c);
    head = head->next;
  }
}
