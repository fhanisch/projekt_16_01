#Compiler
CC = gcc

#Libraries
LIB = -lSDL -lGL -lGLEW -lm

#Objekte
OBJ = build/main.o build/renderobject.o build/geo_objects.o

projekt_16_01: $(OBJ)
	$(CC) -o projekt_16_01 $(OBJ) $(LIB)

build/main.o: src/main.c src/renderobject.h
	$(CC) -c src/main.c -o $@

build/renderobject.o: src/renderobject.c src/renderobject.h
	$(CC) -c src/renderobject.c -o $@

build/geo_objects.o: src/geo_objects.c src/geo_objects.h
	$(CC) -c src/geo_objects.c -o $@

clean:
	rm build/*.o

