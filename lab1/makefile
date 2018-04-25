CFLAGS := -framework OpenGl -framework GLUT
OBJS :=  3dviewer.o task_manager.o scene.o object.o main.o

oop1: $(OBJS) 
	gcc $(CFLAGS) -o oop1 $(OBJS)

main.o: main.c 3dviewer.h
	gcc -c main.c

object.o: object.c object.h program_error.h
	gcc -c object.c

scene.o: scene.c object.h program_error.h
	gcc -c scene.c

task_manager.o: task_manager.c scene.h object.h program_error.h
	gcc -c task_manager.c

3dviewer.o: 3dviewer.c task_manager.h program_error.h
	gcc -c -Wno-deprecated-declarations 3dviewer.c

clean:
	rm *.o