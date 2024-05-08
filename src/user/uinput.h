#ifndef KE_UINPUT_H
#define KE_UINPUT_H

enum uinput {
  U_ARROW = '^[[A',
  D_ARROW = '^[[B',
  R_ARROW = '^[[C',
  L_ARROW = '^[[D',
  SPACE = 32,
  W_BUTTON = 87,
  A_BUTTON = 65,
  S_BUTTON = 83,
  D_BUTTON = 68,
  w_BUTTON = 119,
  a_BUTTON = 97,
  s_BUTTON = 115,
  d_BUTTON = 100,
  q_BUTTON = 113
};

enum ke_run_status {
  QUIT = 0,
  KEEP_GOING = 1
};

const char ke_getch();

#endif // !KE_UINPUT_H
