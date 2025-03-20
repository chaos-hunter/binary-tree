a3q1: a3q1_main.c a3q1_header.h a3q1_functions.c
        gcc -Wall -std=c99 -pedantic a3q1_main.c a3q1_functions.c -o a3q1
a3q2: a3q2_main.c a3q2_header.h a3q2_functions.c
        gcc -Wall -std=c99 -pedantic a3q2_main.c a3q2_functions.c -o a3q2
clean:
        rm *.o a3q1 a3q2
