CC=gcc
#CC=arm-none-linux-gnueabi-gcc
AFLAGS= -c -g
LDFLAGS= -lpthread
OBJS=main.o serial.o server.o data_global.o

smart_home :$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
	
$(OBJS):%.o:%.c
	$(CC) $(AFLAGS) $< -o $@

.PHONY:clean lib
clean:
	rm *.o smart_home libmylib.a

lib:
	ar crs libmylib.a serial.o server.o data_global.o
#gcc main.c -o server -L.. -lmylib -lpthread