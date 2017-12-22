CC=gcc
INCLUDE=-I. -I../../ -I../
CFLAGS=$(INCLUDE)
# ROOT=../../../..
# include $(ROOT)/Makefile.common

main.o: ../main.c hal.h # TODO: dependancies (il en manque surement)
	$(CC) $(CFLAGS) -o main.o -c ../main.c

.PHONY: clean realclean
clean:
	$(RM) main.o

realclean: clean
	-$(RM) *~
