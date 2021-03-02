OUTFILE_MAIN = music
OUTDIR = $(HOME)/cmpt433/public/myApps
TARGETS_MAIN = main.c gpio.c joystick.c shutdown.c util.c


CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)gcc
CFLAGS= -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror 


all: app done

app: 
	@echo "Making music app"
	$(CC_C) $(CFLAGS) $(TARGETS_MAIN) -o $(OUTDIR)/$(OUTFILE_MAIN) -lpthread -lm 


done:
	@echo "Finished Build"

clean: 
	rm $(OUTDIR)/$(OUTFILE)