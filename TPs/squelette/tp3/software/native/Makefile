CC=gcc
INCLUDE=-I. -I../../ -I../
CFLAGS=$(INCLUDE)

main.o: ../main.c hal.h
	$(CC) $(CFLAGS) -o main.o -c ../main.c

.PHONY: clean realclean
clean:
	$(RM) main.o

realclean: clean
	-$(RM) *~
