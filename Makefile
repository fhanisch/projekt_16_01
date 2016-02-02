LIB = -lSDL -lGL -lGLEW
OBJ = build/main.o build/renderobject.o build/geo_objects.o

projekt_16_01: $(OBJ)
	gcc -o projekt_16_01 $(OBJ) $(LIB)

build/main.o: src/main.c
	gcc -c src/main.c -o $@

build/renderobject.o: src/renderobject.c src/renderobject.h
	gcc -c src/renderobject.c -o $@

build/geo_objects.o: src/geo_objects.c src/geo_objects.h
	gcc -c src/geo_objects.c -o $@

clean:
	rm build/*.o

