#include "load_object.h"

int load_object(char *filename, Object **obj_ptr)
{
	FILE *file = fopen(filename, "r");
	if (!file) { return FILE_CANNOT_BE_OPENED; }

	int vert_num = 0;

	if (fscanf(file, "%d", &vert_num) != 1)
	{
		fclose(file);
		return FILE_CONTAINS_INVALID_VALUES;
	}
	if (vert_num < 2)
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

	for (int i = 0; i < vert_num; i++)
	{
		if (fscanf(file, "%lf %lf %lf", &((vert_array+i)->x), &((vert_array+i)->y), &((vert_array+i)->z)) != 3)
		{
			(vert_array+i)->z = 1;
			free(vert_array);
			fclose(file);
			return FILE_CONTAINS_INVALID_VALUES;
		}
	}
	
	int edge_num = 0;

	if (fscanf(file, "%d", &edge_num) != 1)
	{
		fclose(file);
		return FILE_CONTAINS_INVALID_VALUES;
	}
	if (edge_num < 1)
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

	for (int i = 0; i < edge_num; i++)
	{
		if (fscanf(file, "%d %d", &((edge_array+i)->v1), &((edge_array+i)->v2)) != 2)
		{
			free(edge_array);
			fclose(file);
			return FILE_CONTAINS_INVALID_VALUES;
		}
	}

	Object *object = (Object *) malloc(sizeof(Object));
	if (!object)
	{
		fclose(file);
		return ALLOCATION_ERROR;
	}

	object->v_num = vert_num;
	object->vertices = vert_array;
	object->e_num = edge_num;
	object->edges = edge_array;

	*obj_ptr = object;

	fclose(file);
	return NO_ERROR;
}

int delete_object(Object *obj_ptr)
{
	if (!obj_ptr) { return OBJECT_IS_NOT_INITIALISED; }

	free(obj_ptr->vertices);
	free(obj_ptr->edges);
	obj_ptr = NULL;

	return NO_ERROR;
}

int transpose_object(Object *obj_ptr, double dx, double dy, double dz)
{
	if (!obj_ptr) { return OBJECT_IS_NOT_INITIALISED; }

	for (int i = 0; i < obj_ptr->v_num; i++)
	{
		obj_ptr->vertices[i].x += dx;
		obj_ptr->vertices[i].y += dy;
		obj_ptr->vertices[i].z += dz;
	}

	return NO_ERROR;
}

int scale_object(Object *obj_ptr, double kx, double ky, double kz)
{
	if (!obj_ptr) { return OBJECT_IS_NOT_INITIALISED; }

	for (int i = 0; i < obj_ptr->v_num; i++)
	{
		obj_ptr->vertices[i].x *= kx;
		obj_ptr->vertices[i].y *= ky;
		obj_ptr->vertices[i].z *= kz;
	}

	return NO_ERROR;
}

// rotation rel to Z
// x = xc + (x - xc)*cos(rad) + (y - yc)*sin(rad)
// y = yc + (y - yc)*cos(rad) - (x - xc)*sin(rad)

int rotate_object(Object *obj_ptr, double degrees, Axis axis) // rotating relative to the point (0, 0, 0)
{
	if (!obj_ptr) { return OBJECT_IS_NOT_INITIALISED; }

	double angle = degrees * 3.14/180;

	switch (axis) {
		case X:
			for (int i = 0; i < obj_ptr->v_num; i++)
			{
				double y = obj_ptr->vertices[i].y;
				double z = obj_ptr->vertices[i].z;

				obj_ptr->vertices[i].y =  y*cos(angle) + z*sin(angle);
				obj_ptr->vertices[i].z = -y*sin(angle) + z*cos(angle);
			}
			break;
		case Y:
			for (int i = 0; i < obj_ptr->v_num; i++)
			{
				double x = obj_ptr->vertices[i].x;
				double z = obj_ptr->vertices[i].z;

				obj_ptr->vertices[i].x = x*cos(angle) - z*sin(angle);
				obj_ptr->vertices[i].z = x*sin(angle) + z*cos(angle);
			}
			break;
		case Z:
			for (int i = 0; i < obj_ptr->v_num; i++)
			{
				double x = obj_ptr->vertices[i].x;
				double y = obj_ptr->vertices[i].y;

				obj_ptr->vertices[i].x =  x*cos(angle) + y*sin(angle);
				obj_ptr->vertices[i].y = -x*sin(angle) + y*cos(angle);
			}
			break;
		default:
			return WRONG_FUNCTION_ARGUMENT;
	}

	return NO_ERROR;
}

int copy_object(Object **dst, Object *src)
{
	Object *new_object = (Object*) malloc(sizeof(Object));
	if (!new_object) { return ALLOCATION_ERROR; }

	new_object->vertices = (Vertex*) malloc(sizeof(Vertex) * src->v_num);
	if (!new_object->vertices) { return ALLOCATION_ERROR; }
	for (int i = 0; i < src->v_num; i++) {new_object->vertices[i] = src->vertices[i]; }
	new_object->v_num = src->v_num;

	new_object->edges = (Edge*) malloc(sizeof(Edge) * src->e_num);
	if (!new_object->edges) { return ALLOCATION_ERROR; }
	for (int i = 0; i < src->e_num; i++) {new_object->edges[i] = src->edges[i]; }
	new_object->e_num = src->e_num;

	*dst = new_object;

	return NO_ERROR;
}

int render_object(Object *obj_ptr, void (*line)(Vertex v1, Vertex v2))
{
	Object *rendered_obj = NULL;
	int err = copy_object(&rendered_obj, obj_ptr);
	if (err != NO_ERROR) { return RENDERING_ERROR; }
//	rotate_object(rendered_obj, 10, Y);
//	rotate_object(rendered_obj, 99, X);
	for (int i = 0; i < rendered_obj->v_num; i++)
	{ rendered_obj->vertices[i].z = 0; }

	for (int i = 0; i < rendered_obj->e_num; i++)
	{
		Edge edge = rendered_obj->edges[i];
		Vertex v1 = rendered_obj->vertices[edge.v1];
		Vertex v2 = rendered_obj->vertices[edge.v2];

		line(v1, v2);
	}
	delete_object(rendered_obj);

	return NO_ERROR;
}
