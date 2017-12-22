CC=gcc
INCLUDE=-I. -I../../ -I../
CFLAGS=$(INCLUDE)
# ROOT=../../../..
# include $(ROOT)/Makefile.common

main.o: ../main.c # TODO: dependancies
	$(CC) $(CFLAGS) -o main.o -c ../main.c 
# echo "Unimplemented rule"; exit 1

.PHONY: clean realclean
clean:
	$(RM) main.o

realclean: clean
	-$(RM) *~
