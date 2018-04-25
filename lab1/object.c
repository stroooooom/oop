#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

error_t set_vertex(Vertex *vertex, double x, double y, double z)
{
	vertex->x = x;
	vertex->y = y;
	vertex->z = z;

	return NO_ERROR;
}

error_t set_edge(Edge *edge, int v1, int v2)
{
	edge->v1 = v1;
	edge->v2 = v2;

	return NO_ERROR;
}

error_t transpose_vertex(Vertex *vertex, double dx, double dy, double dz)
{
	vertex->x += dx;
	vertex->y += dy;
	vertex->z += dz;

	return NO_ERROR;
}

error_t scale_vertex(Vertex *vertex, double kx, double ky, double kz)
{
	vertex->x *= kx;
	vertex->y *= ky;
	vertex->z *= kz;

	return NO_ERROR;
}

error_t rotate_vertex(Vertex *vertex, double degrees, Axis axis) // rotating relative to the point (0, 0, 0)
{
	double angle = degrees * 3.14/180;

	switch (axis) {
		case X:
		{
			double y = vertex->y;
			double z = vertex->z;

			vertex->y =  y*cos(angle) + z*sin(angle);
			vertex->z = -y*sin(angle) + z*cos(angle);
		}
			break;
		case Y:
		{
			double x = vertex->x;
			double z = vertex->z;

			vertex->x = x*cos(angle) - z*sin(angle);
			vertex->z = x*sin(angle) + z*cos(angle);
		}
			break;
		case Z:
		{
			double x = vertex->x;
			double y = vertex->y;

			vertex->x =  x*cos(angle) + y*sin(angle);
			vertex->y = -x*sin(angle) + y*cos(angle);
		}
			break;
	}

	return NO_ERROR;
}

error_t project_vertex(Vertex *vertex) // vertex projection onto a plane XY 
{
	vertex->z = 0;

	return NO_ERROR;
}

error_t get_vertex_num(Object *object, int *vertex_num)
{
	*vertex_num = object->v_num;

	return NO_ERROR;
}

error_t get_vertices(Object *object, Vertex **vertices)
{
	*vertices = object->vertices;

	return NO_ERROR;
}

error_t get_vertices_from_edge(Vertex *vertices, Edge *edge, Vertex *v1, Vertex *v2)
{
	int v1_num = edge->v1;
	int v2_num = edge->v2;

	*v1 = vertices[v1_num];
	*v2 = vertices[v2_num];

	return NO_ERROR;
}

error_t get_edge_num(Object *object, int *edge_num)
{
	*edge_num = object->e_num;

	return NO_ERROR;
}

error_t get_edges(Object *object, Edge **edges)
{
	*edges = object->edges;

	return NO_ERROR;
}

error_t init_object(Object *object, int vert_num, Vertex* vert_array, int edge_num, Edge* edge_array)
{
	object->v_num = vert_num;
	object->vertices = vert_array;
	object->e_num = edge_num;
	object->edges = edge_array;

	return NO_ERROR;
}

error_t load_object(char *filename, Object **obj_ptr)
{
	FILE *file = fopen(filename, "r");
	if (!file) { return FILE_CANNOT_BE_OPENED; }


	int vert_num = 0;
	int scanned_symbols = fscanf(file, "%d", &vert_num);
	if (scanned_symbols != 1 || vert_num < 2)
	{
		fclose(file);
		return FILE_CONTAINS_INVALID_VALUES;
	}

	Vertex *vert_array = (Vertex*) malloc(sizeof(Vertex) * vert_num);
	if (!vert_array)
	{
		fclose(file);
		return ALLOCATION_ERROR;
	}

	double x, y, z;
	for (int i = 0; i < vert_num; i++)
	{
		if (fscanf(file, "%lf %lf %lf", &x, &y, &z) != 3)
		{
			free(vert_array);
			fclose(file);
			return FILE_CONTAINS_INVALID_VALUES;
		}
		set_vertex(vert_array+i, x, y, z);
	}
	

	int edge_num = 0;
	scanned_symbols = fscanf(file, "%d", &edge_num);
	if (scanned_symbols != 1 || edge_num < 1)
	{
		fclose(file);
		return FILE_CONTAINS_INVALID_VALUES;
	}

	Edge *edge_array = (Edge*) malloc(sizeof(Edge) * edge_num);
	if (!edge_array)
	{
		fclose(file);
		return ALLOCATION_ERROR;
	}

	int v1, v2;
	for (int i = 0; i < edge_num; i++)
	{
		scanned_symbols = fscanf(file, "%d %d", &v1, &v2);
		if (scanned_symbols != 2 || v1 < 0 || v2 < 0)
		{
			free(edge_array);
			fclose(file);
			return FILE_CONTAINS_INVALID_VALUES;
		}
		set_edge(edge_array+i, v1, v2);
	}


	fclose(file);

	Object *object = (Object *) malloc(sizeof(Object));
	if (!object)
	{
		fclose(file);
		return ALLOCATION_ERROR;
	}

	init_object(object, vert_num, vert_array, edge_num, edge_array);

	*obj_ptr = object;
	return NO_ERROR;
}

error_t delete_object(Object *obj_ptr)
{
	if (!obj_ptr) { return OBJECT_IS_NOT_INITIALISED; }

	free(obj_ptr->vertices);
	free(obj_ptr->edges);
	obj_ptr = NULL;

	return NO_ERROR;
}

error_t copy_object(Object **dst, Object *src)
{
	int src_vertex_number, src_edge_number;
	Vertex *src_vertices = NULL;
	Edge *src_edges = NULL;

	get_vertex_num(src, &src_vertex_number);
	get_vertices(src, &src_vertices);
	get_edge_num(src, &src_edge_number);
	get_edges(src, &src_edges);

	Object *object_copy = (Object*) malloc(sizeof(Object));
	Vertex *vertices_copy = (Vertex*) malloc(sizeof(Vertex) * src_vertex_number);
	Edge *edges_copy = (Edge*) malloc(sizeof(Edge) * src_edge_number);

	if (!object_copy || !vertices_copy || !edges_copy) { return ALLOCATION_ERROR; }

	memcpy(vertices_copy, src_vertices, sizeof(Vertex) * src_vertex_number);
	memcpy(edges_copy, src_edges, sizeof(Edge) * src_edge_number);

	init_object(object_copy, src_vertex_number, vertices_copy, src_edge_number, edges_copy);

	*dst = object_copy;

	return NO_ERROR;
}

error_t transpose_object(Object *obj_ptr, double dx, double dy, double dz)
{
	int vertex_num;
	Vertex *vertices = NULL;
	get_vertex_num(obj_ptr, &vertex_num);
	get_vertices(obj_ptr, &vertices);

	for (int i = 0; i < vertex_num; i++)
	{
		transpose_vertex(vertices+i, dx, dy, dz);
	}

	return NO_ERROR;
}

error_t scale_object(Object *obj_ptr, double kx, double ky, double kz)
{
	int vertex_num;
	Vertex *vertices = NULL;
	get_vertex_num(obj_ptr, &vertex_num);
	get_vertices(obj_ptr, &vertices);

	for (int i = 0; i < vertex_num; i++)
	{
		scale_vertex(vertices+i, kx, ky, kz);
	}

	return NO_ERROR;
}

error_t rotate_object(Object *obj_ptr, double degrees, Axis axis) // rotating relative to the point (0, 0, 0)
{
	int vertex_num;
	Vertex *vertices = NULL;
	get_vertex_num(obj_ptr, &vertex_num);
	get_vertices(obj_ptr, &vertices);

	for (int i = 0; i < vertex_num; i++)
	{
		rotate_vertex(vertices+i, degrees, axis);
	}

	return NO_ERROR;
}

error_t render_object(Object *obj_ptr, void (*draw_line)(Vertex v1, Vertex v2))
{
	Object *rendered_obj = NULL;
	int err = copy_object(&rendered_obj, obj_ptr);
	if (err != NO_ERROR) { return RENDERING_ERROR; }

	int rend_obj_vertex_num, rend_obj_edge_num;
	Vertex *rend_obj_vertices = NULL;
	Edge *rend_obj_edges = NULL;
	get_vertex_num(rendered_obj, &rend_obj_vertex_num);
	get_edge_num(rendered_obj, &rend_obj_edge_num);
	get_vertices(rendered_obj, &rend_obj_vertices);
	get_edges(rendered_obj, &rend_obj_edges);

	rotate_object(rendered_obj, 90, X);
	for (int i = 0; i < rend_obj_vertex_num; i++)
	{
		project_vertex(rend_obj_vertices+i);
	}

	Vertex v1, v2;
	for (int i = 0; i < rend_obj_edge_num; i++)
	{
		get_vertices_from_edge(rend_obj_vertices, rend_obj_edges+i, &v1, &v2);
		draw_line(v1, v2);
	}
	delete_object(rendered_obj);

	return NO_ERROR;
}
