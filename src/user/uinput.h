#ifndef KE_UINPUT_H
#define KE_UINPUT_H

enum uinput {
  CURSE = 27,
  U_ARROW = 65,
  D_ARROW = 66,
  R_ARROW = 67,
  L_ARROW = 68,
  SPACE = 32,
  W_BUTTON = 87,
  A_BUTTON = 65,
  S_BUTTON = 83,
  D_BUTTON = 68,
  w_BUTTON = 119,
  a_BUTTON = 97,
  s_BUTTON = 115,
  d_BUTTON = 100,
  q_BUTTON = 113,
  i_BUTTON = 105
};

enum ke_run_status {
  QUIT = 0,
  KEEP_GOING = 1
};

const char ke_getch();

#endif // !KE_UINPUT_H
