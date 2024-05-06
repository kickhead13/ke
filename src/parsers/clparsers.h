#ifndef KE_CL_PARSERS_H
#define KE_CL_PARSERS_H
#include <stdio.h>
#include <string.h>
#include <stddef.h>

char ke_cl_bool_param(size_t, char**, size_t, const char**, char);
char *ke_cl_value_param(size_t, char**, size_t, const char**, char*);

#endif // DEBUG
