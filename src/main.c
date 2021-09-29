#include <8052.h>


#define DATA P2_0

/**
 * Send one byte to WS2812B.
 * 
 * Note in order to use the DATA macro defiend above,
 * this function has to be broken into several `__asm` blocks, 
 * which makes it a little bit harder to understand.
 */
void send_byte(unsigned char b) {
  __asm
      mov r7, dpl       ; move function argument `b` to `r7`
      mov r6, #0x08     ; r6 is the loop counter

    begin:
      mov a, r7         ; move to accumulator for rlc
      rlc a             ; rotate MSB to carry flag
      mov r7, a         ; copy rotated byte back to r7
      jc send_one       ; if carry (was MSB) is 1, jump

    send_zero:          ; send 0 code
  __endasm;

      DATA = 1;         // setb _P2_0    -- 250ns
      DATA = 0;         // clr _P2_0     -- 1250ns (clr + 2 x nop + sjmp)

  __asm
      nop
      nop
      sjmp end

    send_one:           ; send 1 code
  __endasm;

      DATA = 1;         // setb _P2_0    --750ns (setb + 2 x nop)
  __asm
      nop
      nop
  __endasm;

      DATA = 0;         // clr _P2_0     -- 250ns

  __asm
    end:
      dec r6            ; handle loop counter, run the code for 8 times
      mov a, r6
      jnz begin
  __endasm;
}



/**
 * Send reset code to the WS2812B.
 * According to the datasheet, a reset code is a 0-code longer than 50us.
 */
void reset() {
  unsigned char i = 50;
  DATA = 0;

  // the loop compiles to:
  //   mov ar6,r7   ; 1 cycle
  //   dec r7       ; 1 cycle
  //   mov a,r6     ; 1 cycle
  //   jnz loop     ; 2 cycle
  // Each loop takes 5 cycle = 250ns * 5 = 1.25us, so 50 loops take 62.5us,
  // long enough for WS2812B to consider it as a reset.
  while (i--);
}


// Delay function for animation, not part of the WS2812B driver.
void delay() {
  unsigned int i = 20000;
  while (i--);
}

/**
 */
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
      reset();
      delay();
    }

    for (i = 0; i < 24; i++) {
      for (j = 0; j <= i; j++) {
        send_color(7, 7, 0);
      }
      reset();
      delay();
    }

    for (i = 0; i < 24; i++) {
      for (j = 0; j <= i; j++) {
        send_color(0, 7, 0);
      }
      reset();
      delay();
    }

    for (i = 0; i < 24; i++) {
      for (j = 0; j <= i; j++) {
        send_color(0, 7, 7);
      }
      reset();
      delay();
    }

    for (i = 0; i < 24; i++) {
      for (j = 0; j <= i; j++) {
        send_color(0, 0, 7);
      }
      reset();
      delay();
    }

    for (i = 0; i < 24; i++) {
      for (j = 0; j <= i; j++) {
        send_color(7, 0, 7);
      }
      reset();
      delay();
    }

    for (i = 0; i < 24; i++) {
      for (j = 0; j <= i; j++) {
        send_color(0, 0, 0);
      }
      reset();
      delay();
    }

    // gradient color
    for (j = 0; j <= 7; j++) {
      for (i = 0; i < 24; i++) {
        send_color(j, 0, 0);
      }
      reset();
      delay();
    }

    for (j = 0; j <= 7; j++) {
      for (i = 0; i < 24; i++) {
        send_color(7, j, 0);
      }
      reset();
      delay();
    }

    for (j = 7; j >= 0; j--) {
      for (i = 0; i < 24; i++) {
        send_color(j, 7, 0);
      }
      reset();
      delay();
    }

    for (j = 0; j <= 7; j++) {
      for (i = 0; i < 24; i++) {
        send_color(0, 7, j);
      }
      reset();
      delay();
    }

    for (j = 7; j >= 0; j--) {
      for (i = 0; i < 24; i++) {
        send_color(0, j, 7);
      }
      reset();
      delay();
    }

    for (j = 0; j <= 7; j++) {
      for (i = 0; i < 24; i++) {
        send_color(j, 0, 7);
      }
      reset();
      delay();
    }

    for (j = 0; j <= 7; j++) {
      for (i = 0; i < 24; i++) {
        send_color(7, j, 7);
      }
      reset();
      delay();
    }

    for (j = 7; j >= 0; j--) {
      for (i = 0; i < 24; i++) {
        send_color(j, j, j);
      }
      reset();
      delay();
    }
  }
}