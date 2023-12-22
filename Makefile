CC=gcc

%.o: %.c %.h
	${CC} -c $^

LC3sim: LC3.o operations.o
	${CC} $^ -o $@

clean:
	rm make.sh