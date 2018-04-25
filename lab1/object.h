#ifndef _OBJECTH_
#define _OBJECTH_

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

error_t set_vertex(Vertex *vertex, double x, double y, double z);
error_t set_edge(Edge *edge, int v1, int v2);

error_t transpose_vertex(Vertex *vertex, double dx, double dy, double dz);
error_t scale_vertex(Vertex *vertex, double kx, double ky, double kz);
error_t rotate_vertex(Vertex *vertex, double degrees, Axis axis);
error_t project_vertex(Vertex *vertex);

error_t get_vertex_num(Object *object, int *vertex_num);
error_t get_vertices(Object *object, Vertex **vertices);
error_t get_edge_num(Object *object, int *edge_num);
error_t get_edges(Object *object, Edge **edges);
error_t get_vertices_from_edge(Vertex *vertices, Edge *edge, Vertex *v1, Vertex *v2);

error_t init_object(Object *object, int vert_num, Vertex* vert_array, int edge_num, Edge* edge_array);
error_t load_object(char *filename, Object **obj_ptr);
error_t copy_object(Object **dst, Object *src);
error_t delete_object(Object *obj_ptr);

error_t transpose_object(Object *obj_ptr, double dx, double dy, double dz);
error_t scale_object(Object *obj_ptr, double kx, double ky, double kz);
error_t rotate_object(Object *obj_ptr, double degrees, Axis axis);

error_t render_object(Object *obj_ptr, void (*draw_line)(Vertex v1, Vertex v2));

#endif

