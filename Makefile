CC = cc

TESTING = 0

MAIN = rocket_controller
objects = main.o logger.o crc.o data_transmission.o motor_acquisition.o motor_control.o mcu_command.o
LFLAGS = -lpthread
CFLAGS = -Wall -pedantic -DTESTING=$(TESTING)
SUBDIRS = rocket-packet data-transmission motor
VPATH = $(SUBDIRS)


all : $(MAIN)

$(MAIN) : $(objects)
	$(CC) $^ -o $(MAIN) $(LFLAGS) $(CFLAGS)




$(objects) :


.PHONY : clean
clean :
	rm -f $(MAIN) $(objects)

