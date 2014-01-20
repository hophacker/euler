CC=g++
CFLAGS=-g


all:test testBigIntBase

test: test.o BigIntBase.o
	$(CC) $(CFLAGS)  $^ -o $@

testBigIntBase: testBigIntBase.o BigIntBase.o
	$(CC) $(CFLAGS)  $^ -o $@

%.o:%.cc %.h
	$(CC) $(CFLAGS) -c $< 

%.o:%.cc 
	$(CC) $(CFLAGS) -c $< 

clean:
	rm *.o testBigIntBase test BigIntBase.o
