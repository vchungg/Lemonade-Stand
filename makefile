
lemonade: lemonade.o keyboard.o xterm_control.o
	  gcc lemonade.o keyboard.o xterm_control.o -lm -o lemonade

lemonade.o:	lemonade.c keyboard.h xterm_control.h
	gcc -c lemonade.c

keyboard.o:	keyboard.c keyboard.h
	gcc -c keyboard.c

xterm_control.o: xterm_control.h xterm_control.c
	gcc -c xterm_control.c

