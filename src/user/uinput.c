#include "uinput.h"
#include <curses.h>
#include <stdlib.h>

const char ke_getch() {
  system("/bin/stty raw");
  char ch = getchar();
  system("/bin/stty cooked");
  return ch;
}
