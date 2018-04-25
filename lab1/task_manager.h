#ifndef _TASK_MANAGER_
#define _TASK_MANAGER_

#include "scene.h"
#include "object.h"

typedef enum {
	LOAD_OBJECT,
	RENDER_OBJECT,
	DELETE_OBJECT,

	TRANSPOSE_OBJECT,
	SCALE_OBJECT,
	ROTATE_OBJECT,
} Action;


typedef struct {
	char *filename;
	Scene **scene_ptr;
} Object_loading_data;

typedef struct {
	Scene *scene_ptr;
	void (* draw_line)(Vertex v1, Vertex v2);
} Object_rendering_data;

typedef struct {
	Scene *scene_ptr;
} Object_deleting_data;

typedef struct Object_transposing_data {
	Scene *scene_ptr;
	double dx;
	double dy;
	double dz;
} Object_transposing_data;

typedef struct {
	Scene *scene_ptr;
	double kx;
	double ky;
	double kz;
} Object_scaling_data;

typedef struct {
	Scene *scene_ptr;
	double degrees;
	Axis axis;
} Object_rotating_data;

typedef union {
	Object_loading_data object_loading;
	Object_rendering_data object_rendering;
	Object_deleting_data object_deleting;

	Object_transposing_data object_transposing;
	Object_scaling_data	object_scaling;
	Object_rotating_data object_rotating;
} Action_data;


Action_data pack_loading_data(char *filename, Scene **scene_ptr);
Action_data pack_rendering_data(Scene *scene_ptr, void (* draw_line)(Vertex v1, Vertex v2));
Action_data pack_deleting_data(Scene *scene_ptr);
Action_data pack_transposing_data(Scene *scene_ptr, double dx, double dy, double dz);
Action_data pack_scaling_data(Scene *scene_ptr, double kx, double ky, double kz);
Action_data pack_rotating_data(Scene *scene_ptr, double degrees, Axis axis);


error_t unpack_loading_data(Action_data *action_data, Scene ***scene_ptr, char **filename);
error_t unpack_rendering_data(Action_data *action_data, Object **object, void (** draw_line)(Vertex v1, Vertex v2));
error_t unpack_deleting_data(Action_data *action_data, Scene **scene_ptr);
error_t unpack_transposing_data(Action_data *action_data, Object **object, double *dx, double *dy, double *dz);
error_t unpack_scaling_data(Action_data *action_data, Object **object, double *kx, double *ky, double *kz);
error_t unpack_rotating_data(Action_data *action_data, Object **object, double *degrees, Axis *axis);

error_t task_manager(Action action, Action_data action_data);

#endif