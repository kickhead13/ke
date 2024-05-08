#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  size_t input;
  char test[20];
  for(;;) {
    system("/bin/stty raw");
    input = getchar();
    system("/bin/stty cooked");
    sprintf(test, "%d", input);
    write(1, " ", 1);
    if(input == 97) break;
    write(1, test, strlen(test));
    write(1, "\n", 1);
  }
  return 0;
}
