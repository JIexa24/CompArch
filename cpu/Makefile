CC = gcc
CFLAGS = -g3 -std=c99

all: ./../lib/libCPU.a

./../lib/libCPU.a: ./obj/cpu.o ./obj/change.o ./obj/print.o ./obj/handlers.o ./obj/global.o ./obj/read.o ./obj/command.o
	ar rvs ./../lib/libCPU.a ./obj/cpu.o ./obj/change.o ./obj/print.o ./obj/handlers.o ./obj/global.o ./obj/read.o ./obj/command.o

./obj/cpu.o: ./src/cpu.c include/cpu.h
	$(CC) -c ./src/cpu.c -o ./obj/cpu.o $(CFLAGS)

./obj/change.o: ./src/change.c include/cpu.h
	$(CC) -c ./src/change.c -o ./obj/change.o -g3 -std=gnu99

./obj/print.o: ./src/print.c include/cpu.h
	$(CC) -c ./src/print.c -o ./obj/print.o $(CFLAGS)

./obj/read.o: ./src/read.c include/cpu.h
	$(CC) -c ./src/read.c -o ./obj/read.o $(CFLAGS)

./obj/handlers.o: ./src/handlers.c include/cpu.h
	$(CC) -c ./src/handlers.c -o ./obj/handlers.o $(CFLAGS)

./obj/global.o: ./src/global.c include/cpu.h
	$(CC) -c ./src/global.c -o ./obj/global.o $(CFLAGS)

./obj/command.o: ./src/command.c include/cpu.h
	$(CC) -c ./src/command.c -o ./obj/command.o $(CFLAGS)

clean:
	rm -f ./obj/*.o

restruct:
	make clean
	make all
