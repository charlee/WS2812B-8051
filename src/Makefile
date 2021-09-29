ifeq ($(OS),Windows_NT) 
RM = del /Q /F
CP = copy /Y
ifdef ComSpec
SHELL := $(ComSpec)
endif
ifdef COMSPEC
SHELL := $(COMSPEC)
endif
else
RM = rm -rf
CP = cp -f
endif


CC := sdcc
PACKIHX := packihx

.PHONY: all clean

all: ws2812b.hex

clean:
	-$(RM) -f *.asm *.lk *.lst *.map *.mem *.rel *.rst *.sym *.asm *.ihx *.hex

main.ihx: main.c
	$(CC) main.c

ws2812b.hex: main.ihx
	$(PACKIHX) main.ihx > ws2812b.hex

