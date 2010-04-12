tetrellis: main.o tetrellis.o block.o field.o shapes.o
	gcc -lSDL -o tetrellis main.o tetrellis.o block.o field.o shapes.o

main.o: main.c tetrellis.h shapes.h
	gcc -c main.c

tetrellis.o: tetrellis.c tetrellis.h shapes.h field.h block.h
	gcc -c tetrellis.c

block.o: block.c block.h field.h shapes.h
	gcc -c block.c

field.o: field.c field.h shapes.h
	gcc -c field.c

shapes.o: shapes.c shapes.h
	gcc -c shapes.c

clean:
	rm tetrellis main.o tetrellis.o block.o field.o shapes.o

