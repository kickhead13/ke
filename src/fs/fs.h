#ifndef KE_FS_H
#define KE_FS_H

enum filetype {
  RW_FILE = 1,
  RO_FILE = 2,
  WO_FILE = 3,
  NP_FILE = 4,
  DIRECTORY = 0
};

#define FILE_PERMS S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP
enum filetype get_file_type(char *);
char *file_contents(const char *);

#endif
