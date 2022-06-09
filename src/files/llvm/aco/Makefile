acotsp: acotsp_standalone.o TSP.o utilities.o ants.o InOut.o timer.o ls.o parse.o
    gcc -ansi acotsp_standalone.o TSP.o utilities.o ants.o InOut.o timer.o parse.o ls.o -o acotsp -O -lm 
acotsp_standalone.o: acotsp_standalone.c
    gcc -c acotsp_standalone.c -o acotsp_standalone.o  -O -Wall -ansi -pedantic
TSP.o: TSP.c TSP.h
    gcc -c TSP.c -o TSP.o  -O -Wall -ansi -pedantic
ants.o: ants.c ants.h
    gcc -c ants.c -o ants.o  -O -Wall -ansi -pedantic
InOut.o: InOut.c InOut.h
    gcc -c InOut.c -o InOut.o  -O -Wall -ansi -pedantic
utilities.o: utilities.c utilities.h
    gcc -c utilities.c -o utilities.o  -O -Wall -ansi -pedantic
ls.o: ls.c ls.h
    gcc -c ls.c -o ls.o  -O -Wall -ansi -pedantic
parse.o: parse.c parse.h
    gcc -c parse.c -o parse.o  -O -Wall -ansi -pedantic
timer.o: timer.c timer.h
    gcc -c timer.c -o timer.o  -O -Wall -ansi -pedantic
clean:
    rm -f *.o acotsp
