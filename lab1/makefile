CFLAGS := -framework OpenGl -framework GLUT
OBJS := load_object.o main.o

oop1: $(OBJS)
	gcc $(CFLAGS) -o oop1 $(OBJS)

main.o: main.c load_object.h
	gcc $(CFLAGS) -c main.c

load_object.o : load_object.c load_object.h program_error.h
	gcc -c load_object.c