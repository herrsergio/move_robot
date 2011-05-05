CC = gcc
P = -Wall -O2 

move_robot : main.c init_serial.o init_socket.o move_robot.o read_serial.o read_socket.o cssl.o 
	$(CC) $(P) -g -o move_robot  main.c init_serial.o init_socket.o move_robot.o read_serial.o read_socket.o  cssl.o -lpthread -lm

init_serial.o : init_serial.h init_serial.c
	$(CC) $(P) -g -c init_serial.c

init_socket.o : init_socket.h init_socket.c
	$(CC) $(P) -g -c init_socket.c

move_robot.o : move_robot.h move_robot.c
	$(CC) $(P) -std=c99 -lm -g -c move_robot.c

read_serial.o : read_serial.h read_serial.c
	$(CC) $(P) -g -c read_serial.c

read_socket.o : read_socket.h read_socket.c
	$(CC) $(P) -g -c read_socket.c

cssl.o : cssl.h cssl.c
	$(CC) $(P) -g -c cssl.c

clean:
	rm *.o move_robot
