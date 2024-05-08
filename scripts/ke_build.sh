#!/bin/bash

mkdir ./target 2> /dev/null

mkdir ~/.config/ke/ 2> /dev/null
touch ~/.config/ke/ke.conf 

gcc -o ./target/ke \
  ./src/main.c \
  ./src/term/term.c \
  ./src/parsers/clparsers.c \
  ./src/fs/fs.c \
  ./src/term/tblinkedlist.c \
  ./src/term/cursor.c
