#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "term/term.h"
#include "parsers/clparsers.h"
#include "term/tblinkedlist.h"

int main(size_t argc, char **argv) {

  const char *fparam[2] = {"-f", "--file"};
  char *filename = ke_cl_value_param(argc, argv, 2, fparam, "./");
  struct term_window *win = get_term_window(filename); 

  printf("%d", strlen("\033["));

  return ke_run(win, filename);
} 
