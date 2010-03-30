tetrellis: main.o tetrellis.o field.o shapes.o
	gcc -lSDL -o tetrellis main.o tetrellis.o field.o shapes.o

main.o: main.c tetrellis.h shapes.h
	gcc -c main.c

tetrellis.o: tetrellis.c shapes.h field.h
	gcc -c tetrellis.c

field.o: field.c field.h shapes.h
	gcc -c field.c

shapes.o: shapes.c shapes.h
	gcc -c shapes.c

clean:
	rm tetrellis main.o tetrellis.o field.o shapes.o

