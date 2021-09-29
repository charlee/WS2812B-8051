#include <8052.h>


#define DATA P2_0

void send_byte(unsigned char b) {
  __asm
      mov r7, dpl
      mov r6, #0x08

    begin:
      mov a, r7
      rlc a
      mov r7, a
      jc send_one

    send_zero:
  __endasm;

      DATA = 1;        // 250ns
      DATA = 0;         // 1250ns (clr + 2 x nop + sjmp)

  __asm
      nop
      nop
      sjmp end

    send_one:
  __endasm;

      DATA = 1;        // 750ns (setb + 2 x nop)
  __asm
      nop
      nop
  __endasm;

      DATA = 0;         // 250ns

  __asm
    end:
      dec r6
      mov a, r6
      jnz begin
  __endasm;
}



void delay() {
  unsigned int i = 20000;
  while (i--);
}

void send_color(unsigned char r, unsigned char g, unsigned char b) {
  send_byte(g);
  send_byte(r);
  send_byte(b);
}

void main() {
  int i, j;
  while(1) {

    for (i = 0; i < 24; i++) {
      for (j = 0; j <= i; j++) {
        send_color(7, 0, 0);
      }
      delay();
    }

    for (i = 0; i < 24; i++) {
      for (j = 0; j <= i; j++) {
        send_color(7, 7, 0);
      }
      delay();
    }

    for (i = 0; i < 24; i++) {
      for (j = 0; j <= i; j++) {
        send_color(0, 7, 0);
      }
      delay();
    }

    for (i = 0; i < 24; i++) {
      for (j = 0; j <= i; j++) {
        send_color(0, 7, 7);
      }
      delay();
    }

    for (i = 0; i < 24; i++) {
      for (j = 0; j <= i; j++) {
        send_color(0, 0, 7);
      }
      delay();
    }

    for (i = 0; i < 24; i++) {
      for (j = 0; j <= i; j++) {
        send_color(7, 0, 7);
      }
      delay();
    }

    for (i = 0; i < 24; i++) {
      for (j = 0; j <= i; j++) {
        send_color(0, 0, 0);
      }
      delay();
    }

    // gradient color
    for (j = 0; j <= 7; j++) {
      for (i = 0; i < 24; i++) {
        send_color(j, 0, 0);
      }
      delay();
    }

    for (j = 0; j <= 7; j++) {
      for (i = 0; i < 24; i++) {
        send_color(7, j, 0);
      }
      delay();
    }

    for (j = 7; j >= 0; j--) {
      for (i = 0; i < 24; i++) {
        send_color(j, 7, 0);
      }
      delay();
    }

    for (j = 0; j <= 7; j++) {
      for (i = 0; i < 24; i++) {
        send_color(0, 7, j);
      }
      delay();
    }

    for (j = 7; j >= 0; j--) {
      for (i = 0; i < 24; i++) {
        send_color(0, j, 7);
      }
      delay();
    }

    for (j = 0; j <= 7; j++) {
      for (i = 0; i < 24; i++) {
        send_color(j, 0, 7);
      }
      delay();
    }

    for (j = 0; j <= 7; j++) {
      for (i = 0; i < 24; i++) {
        send_color(7, j, 7);
      }
      delay();
    }

    for (j = 7; j >= 0; j--) {
      for (i = 0; i < 24; i++) {
        send_color(j, j, j);
      }
      delay();
    }
  }
}