vpath %.cc .
CC=g++
CFLAGS=-g

_TAR = testBigIntBase
_OBJ = $(patsubst %,%.o,$(_TAR)) BigIntBase.o

TAR = $(patsubst %,obj/%,$(_TAR))
OBJ = $(patsubst %,obj/%,$(_OBJ))

.PHONY: all clean print

all: $(TAR)

print: 
	echo $(OBJ)

$(TAR):$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
$(OBJ): | obj
obj:
	@mkdir -p $@

obj/%.o : %.cc %.h
	@echo $<
	$(CC) -c -o $@ $< $(CFLAGS)


	
#test.o testBigIntBase.o
#testBigIntBase: $(OBJ)
	#$(CC) $(CFLAGS)  $^ -o $@


#test: $(OBJ)
	#$(CC) $(CFLAGS)  $^ -o $@

#all:test testBigIntBase


.PHONY : clean
clean:
	rm -rf *.o obj/ testBigIntBase test BigIntBase
