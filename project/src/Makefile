# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: Main.elf 

#additional rules for files
Main.elf: ${COMMON_OBJECTS} main.o stateMachines.o led.o buzzer.o switches.o wdInterruptHandler.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: Main.elf
	msp430loader.sh Main.elf

clean:
	rm -f *.o *.elf

led.o: led.c led.h

buzzer.o: buzzer.h

switches.o: switches.h

wdInterruptHandler.o: stateMachines.h

stateMachines.o: stateMachines.h led.h buzzer.h switches.h
