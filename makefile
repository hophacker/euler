CFLAGS=-g
CC=g++
DEP=euler.h
OBJ=21
all:$(OBJ)
bigint-dir=BigInteger
bigint-objects =BigIntBase.o
bigint-lib=$(patsubst %,$(bigint-dir)/%,$(bigint-objects))


$(bigint-lib):

%.o:%.cc
	$(CC) $(CFLAGS) -c $< 

clean:
	rm $(OBJ) *.o
