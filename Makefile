tetrellis: tetrellis.o shapes.o
	gcc -lSDL -o tetrellis tetrellis.o shapes.o

tetrellis.o: tetrellis.c shapes.h
	gcc -c tetrellis.c

shapes.o: shapes.c shapes.h
	gcc -c shapes.c
