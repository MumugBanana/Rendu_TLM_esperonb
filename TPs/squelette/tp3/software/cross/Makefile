ifndef CROSS_COMPILE
CROSS_COMPILE=microblaze-xilinx-linux-gnu-
endif

TARGET_CC = $(CROSS_COMPILE)gcc
TARGET_LD = $(CROSS_COMPILE)ld
TARGET_OBJDUMP = $(CROSS_COMPILE)objdump
TARGET_READELF = $(CROSS_COMPILE)readelf
HOST_CC = gcc
HOST_LD = ld
HOST_OBJDUMP = objdump
HOST_READELF = readelf

INCLUDE = -I. -I../..

OBJS = main.o boot.o it.o
EXEC = a.out

# Disassembly of the generated executable.
dump.dis: $(EXEC)
	$(TARGET_OBJDUMP) -d $< > $@

# Summary of the sections and their size.
sections.txt: $(EXEC)
	$(TARGET_READELF) -S $< > $@


$(EXEC): $(OBJS) ldscript # TODO: dependencies
	$(TARGET_LD) $(OBJS) -o $@ -T ldscript
# echo "Rule for linking not implemented."; exit 1
# TODO: use $(TARGET_LD), and use the -T option to point to linker script ldscript

main.o: ../main.c hal.h # TODO: dependancies (il en manque surement)
	$(TARGET_CC) $(INCLUDE) -o main.o -c ../main.c
# TODO: compile with target C compiler

%.o: %.s
	$(TARGET_CC) -o $@ -c $<
	# echo "Rule for assembly not implemented"; exit 1

.PHONY: clean realclean
clean:
	-$(RM) $(OBJS) $(EXEC) dump.dis sections.txt

realclean: clean
	-$(RM) *~
