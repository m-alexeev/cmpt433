OUTFILE = hello
OUTDIR = $(HOME)/cmpt433/public/myApps

CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)gcc
CFLAGS= -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror


all: app done

app: 
	$(CC_C) $(CFLAGS) hello.c leds.c gpio.c -o $(OUTDIR)/$(OUTFILE)

done:
	@echo "Finished Build"

clean: 
	rm $(OUTDIR)/$(OUTFILE)
