OBJS = $(patsubst %.c,%.o, $(wildcard *.c))
OUT = LC3sim
CC = clang

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT).exe

LC3.o: LC3.c LC3.h operations.h
	$(CC) -c $<

operations.o: operations.c operations.h LC3.h
	$(CC) -c $<

clean:
	
	
	