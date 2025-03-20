a3q1: a3q1_main.c a3q1_header.h a3q1_functions.c
        gcc -Wall -std=c99 -pedantic a3q1_main.c a3q1_functions.c -o a3q1

clean:
        rm *.o a3q1 a3q2
