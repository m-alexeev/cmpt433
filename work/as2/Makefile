OUTFILE_MAIN = sorter
OUTFILE_DEBUG = noworky
OUTDIR = $(HOME)/cmpt433/public/myApps
TARGETS_MAIN = main.c sorter.c util.c i2c.c network.c shutdown.c driver.c display.c knob.c gpio.c
TARGET_DEBUG = noworky.c

CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)gcc
CFLAGS= -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror 


all: app noworky  done

app: 
	@echo "Making sorter app"
	$(CC_C) $(CFLAGS) $(TARGETS_MAIN) -o $(OUTDIR)/$(OUTFILE_MAIN) -lpthread -lm 

noworky: 
	@echo "Making noworky"
	$(CC_C) $(CFLAGS) $(TARGET_DEBUG) -o $(OUTDIR)/$(OUTFILE_DEBUG) 

done:
	@echo "Finished Build"

clean: 
	rm $(OUTDIR)/$(OUTFILE)