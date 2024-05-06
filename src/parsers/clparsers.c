#include "clparsers.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

char ke_cl_bool_param(size_t argc, char **argv, size_t ptc, const char **param_tags, char def) {
  size_t iter = 0;
  for(;iter < argc; iter++) {
    for(size_t pter = 0;pter < ptc; pter++) {
      if(strcmp(argv[iter], param_tags[pter]) == 0) return 1;
    }
  }
  return def;
}

char *ke_cl_value_param(size_t argc, char **argv, size_t ptc, const char **param_tags, char *def) {
  size_t iter = 0;
  for(;iter < argc; iter++) {
    for(size_t pter = 0;pter < ptc; pter++) {
      if(strcmp(argv[iter], param_tags[pter]) == 0 && iter + 1 < argc) return argv[iter+1]; 
    }
  }
  return def;
}
