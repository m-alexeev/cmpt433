OUTFILE = display
OUTDIR = $(HOME)/cmpt433/public/myApps
TARGETS = segDisplay.c


CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)gcc
CFLAGS= -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror 


all: app done

app: 
	$(CC_C) $(CFLAGS) $(TARGETS) -o $(OUTDIR)/$(OUTFILE) -lpthread -lm 

done:
	@echo "Finished Build"

clean: 
	rm $(OUTDIR)/$(OUTFILE)