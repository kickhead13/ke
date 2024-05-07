#!/bin/bash

mkdir ./target 2> /dev/null

gcc -o ./target/ke \
  ./src/main.c \
  ./src/term/term.c \
  ./src/parsers/clparsers.c \
  ./src/fs/fs.c
