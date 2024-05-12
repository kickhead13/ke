#!/bin/bash

mkdir ./target 2> /dev/null

mkdir ~/.config/ke/ 2> /dev/null
touch ~/.config/ke/ke.conf 

gcc -o ./target/ke \
  ./src/user/uinput.c \
  ./src/user/user.c \
  ./src/term/tblinkedlist.c \
  ./src/term/term.c \
  ./src/main.c \
  ./src/parsers/clparsers.c \
  ./src/fs/fs.c \
  ./src/term/cursor.c
