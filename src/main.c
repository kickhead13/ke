#include <stdio.h>
#include <stdlib.h>
#include "term/term.h"
#include "parsers/clparsers.h"

int main(size_t argc, char **argv) {

  struct term_window *win = get_term_window();
  tbuff_fill_test(win->tb, 'a'); 
  printf("%d", win->tb->len);

  const char *fparam[2] = {"-f", "--file"};

  char *filename = ke_cl_value_param(argc, argv, 2, fparam, "./");
  printf("%s\n", filename);
  

  return ke_run(win, filename);

} 
