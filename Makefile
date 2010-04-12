tetrellis: main.o tetrellis.o block.o field.o shapes.o next_shape.o
	gcc -lSDL -o tetrellis main.o tetrellis.o block.o field.o shapes.o next_shape.o

main.o: main.c main.h tetrellis.h
	gcc -c main.c

tetrellis.o: tetrellis.c main.h tetrellis.h shapes.h field.h block.h next_shape.h
	gcc -c tetrellis.c

block.o: block.c main.h block.h field.h shapes.h
	gcc -c block.c

field.o: field.c main.h field.h shapes.h
	gcc -c field.c

shapes.o: shapes.c main.h shapes.h
	gcc -c shapes.c

next_shape.o: next_shape.c main.h next_shape.h shapes.h field.h
	gcc -c next_shape.c

clean:
	rm tetrellis main.o tetrellis.o block.o field.o shapes.o next_shape.o

