#include "fs.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

enum filetype get_file_type(char *filename) {
  return RW_FILE;
}

char *file_contents(const char *filename) {
  int fd = open(filename, O_CREAT | O_RDWR, FILE_PERMS);
  size_t bytes_read = 0;
  if(fd < 0) return NULL; 
  int chunk_size = 1024;
  
  char *comp_buff=(char*)malloc(chunk_size*sizeof(char)), *new_buff;
  size_t buff_size = 0;
  char *part_buff = (char *)malloc(chunk_size * sizeof(char));
  while((bytes_read = read(fd, part_buff, chunk_size)) > 0) {
    part_buff[bytes_read] = '\0';
    buff_size += chunk_size;
    if((new_buff = (char*)realloc(comp_buff, buff_size)) != NULL) {
      comp_buff = new_buff;
      strcat(comp_buff, part_buff);
    }
  }
  printf("%s", comp_buff);
  return comp_buff;
}
