tetrellis: main.o tetrellis.o shapes.o
	gcc -lSDL -o tetrellis main.o tetrellis.o shapes.o

main.o: main.c tetrellis.h shapes.h
	gcc -c main.c

tetrellis.o: tetrellis.c shapes.h
	gcc -c tetrellis.c

shapes.o: shapes.c shapes.h
	gcc -c shapes.c

clean:
	rm tetrellis main.o tetrellis.o shapes.o

