CC = cc
MAIN = rocket_controller
objects = main.o data_transmission.o
LFLAGS = -lpthread
CFLAGS = -Wall -g


all : $(objects)
	$(CC) $^ -o $(MAIN) $(LFLAGS) $(CFLAGS)


$(objects) :


.PHONY : clean
clean :
	rm $(MAIN) $(objects)

