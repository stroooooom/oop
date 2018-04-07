#ifndef _OBJECTH_
#define _OBJECTH_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "program_error.h"

typedef enum {
	X, Y, Z
} Axis;

typedef struct {
	double x;
	double y;
	double z;
} Vertex;

typedef struct {
	int v1;
	int v2;
} Edge;

typedef struct {
	int v_num;
	Vertex *vertices;
	int e_num;
	Edge *edges;
} Object;

int load_object(char *filename, Object **obj_ptr);
int copy_object(Object **dst, Object *src);
int delete_object(Object *obj_ptr);

int transpose_object(Object *obj_ptr, double dx, double dy, double dz);
int scale_object(Object *obj_ptr, double kx, double ky, double kz);
int rotate_object(Object *obj_ptr, double degrees, Axis axis); // rotating relative to the point (0, 0, 0)

int render_object(Object *obj_ptr, void (*line)(Vertex v1, Vertex v2));

#endif

