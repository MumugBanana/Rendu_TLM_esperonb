CC=gcc
INCLUDE=-I. -I../../
CFLAGS=$(INCLUDE)
# ROOT=../../../..
# include $(ROOT)/Makefile.common

main.o: # TODO: dependancies
	$(CC)  $(CFLAGS) hal.h -o main.o
# echo "Unimplemented rule"; exit 1

.PHONY: clean realclean
clean:
	$(RM) main.o

realclean: clean
	-$(RM) *~
