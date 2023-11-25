gcc -c LC3.c
gcc -c operations.c
gcc LC3.o operations.o -lm -o LC3sim
./LC3sim