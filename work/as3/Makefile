OUTFILE_MAIN = music
OUTDIR = $(HOME)/cmpt433/public/myApps
TARGETS_MAIN = main.c gpio.c input.c i2c.c shutdown.c util.c joystick.c mixer.c controller.c


CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)gcc
CFLAGS= -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror 
LFLAGS=-L$(HOME)/cmpt433/public/asound_lib_BBB


all: app wav done

app: 
	@echo "Making music app"
	$(CC_C) $(CFLAGS) $(TARGETS_MAIN) -o $(OUTDIR)/$(OUTFILE_MAIN) $(LFLAGS) -lpthread -lasound -lm 

wav: 
	@echo "Copying Music"
	mkdir -p $(OUTDIR)/beatbox-wav-files/ 
	cp -R beatbox-wave-files/* $(OUTDIR)/beatbox-wav-files/ 


done:
	@echo "Finished Build"

clean: 
	rm $(OUTDIR)/$(OUTFILE)