OBJS = $(patsubst %.c,%.o, $(wildcard *.c))
OUT = LC3sim
CC = gcc

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

LC3.o: LC3.c LC3.h operations.h
	$(CC) -c $< -o $@

operations.o: operations.c operations.h LC3.h
	$(CC) -c $< -o $@

clean:
	$(RM) $(OUT)
	$(RM) $(wildcard *.o)
	