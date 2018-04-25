#include "task_manager.h"

#include "scene.h"
#include "object.h"
#include "program_error.h"

#include <stdlib.h>

Action_data pack_loading_data(char *filename, Scene **scene_ptr)
{
	Action_data action_data;
	action_data.object_loading.filename = filename;
	action_data.object_loading.scene_ptr = scene_ptr;

	return action_data;
}

Action_data pack_rendering_data(Scene *scene_ptr, void (* draw_line)(Vertex v1, Vertex v2))
{
	Action_data action_data;
	action_data.object_rendering.scene_ptr = scene_ptr;
	action_data.object_rendering.draw_line = draw_line;

	return action_data;
}

Action_data pack_deleting_data(Scene *scene_ptr)
{
	Action_data action_data;
	action_data.object_deleting.scene_ptr = scene_ptr;

	return action_data;
}

Action_data pack_transposing_data(Scene *scene_ptr, double dx, double dy, double dz)
{
	Action_data action_data;
	action_data.object_transposing.scene_ptr = scene_ptr;
	action_data.object_transposing.dx = dx;
	action_data.object_transposing.dy = dy;
	action_data.object_transposing.dz = dz;

	return action_data;
}

Action_data pack_scaling_data(Scene *scene_ptr, double kx, double ky, double kz)
{
	Action_data action_data;
	action_data.object_scaling.scene_ptr = scene_ptr;
	action_data.object_scaling.kx = kx;
	action_data.object_scaling.ky = ky;
	action_data.object_scaling.kz = kz;

	return action_data;
}

Action_data pack_rotating_data(Scene *scene_ptr, double degrees, Axis axis)
{
	Action_data action_data;
	action_data.object_rotating.scene_ptr = scene_ptr;
	action_data.object_rotating.degrees = degrees;
	action_data.object_rotating.axis = axis;

	return action_data;
}


error_t unpack_loading_data(Action_data *action_data, Scene ***scene_ptr, char **filename)
{
	Object_loading_data object_loading = action_data->object_loading;
	*scene_ptr = object_loading.scene_ptr;
	*filename = object_loading.filename;

	return NO_ERROR;
}

error_t unpack_rendering_data(Action_data *action_data, Object **object, void (** draw_line)(Vertex v1, Vertex v2))
{
	Object_rendering_data object_rendering = action_data->object_rendering;
	get_object(object_rendering.scene_ptr, object);
	*draw_line = object_rendering.draw_line;

	return NO_ERROR;
}

error_t unpack_deleting_data(Action_data *action_data, Scene **scene_ptr)
{
	Object_deleting_data object_deleting = action_data->object_deleting;
	*scene_ptr = object_deleting.scene_ptr;

	return NO_ERROR;
}

error_t unpack_transposing_data(Action_data *action_data, Object **object, double *dx, double *dy, double *dz)
{
	Object_transposing_data object_transposing = action_data->object_transposing;
	get_object(object_transposing.scene_ptr, object);
	*dx = object_transposing.dx;
	*dy = object_transposing.dy;
	*dz = object_transposing.dz;

	return NO_ERROR;
}

error_t unpack_scaling_data(Action_data *action_data, Object **object, double *kx, double *ky, double *kz)
{
	Object_scaling_data object_scaling = action_data->object_scaling;
	get_object(object_scaling.scene_ptr, object);
	*kx = object_scaling.kx;
	*ky = object_scaling.ky;
	*kz = object_scaling.kz;

	return NO_ERROR;
}

error_t unpack_rotating_data(Action_data *action_data, Object **object, double *degrees, Axis *axis)
{
	Object_rotating_data object_rotating = action_data->object_rotating;
	get_object(object_rotating.scene_ptr, object);
	*degrees = object_rotating.degrees;
	*axis = object_rotating.axis;

	return NO_ERROR;
}

error_t task_manager(Action action, Action_data action_data)
{
	error_t error = NO_ERROR;

	switch (action)
	{
		Object *current_object = NULL;

		case LOAD_OBJECT:
			{
				Scene **current_scene_ptr = NULL;
				char *filename = NULL;
				unpack_loading_data(&action_data, &current_scene_ptr, &filename);
				error = load_object(filename, &current_object);
				if (error != NO_ERROR) { return error; }
				error = init_scene(current_scene_ptr, current_object);
			}
			break;

		Scene *current_scene = NULL;

		case DELETE_OBJECT:
		{
			unpack_deleting_data(&action_data, &current_scene);
			error = delete_scene(current_scene);
		}
			break;

		case RENDER_OBJECT:
		{
			void (* draw_line)(Vertex v1, Vertex v2) = NULL;
			unpack_rendering_data(&action_data, &current_object, &draw_line);
			error = render_object(current_object, draw_line);
		}
			break;

		case TRANSPOSE_OBJECT:
		{
			double dx, dy, dz;
			unpack_transposing_data(&action_data, &current_object, &dx, &dy, &dz);
			error = transpose_object(current_object, dx, dy, dz);
		}
			break;

		case SCALE_OBJECT:
		{
			double kx, ky, kz;
			unpack_scaling_data(&action_data, &current_object, &kx, &ky, &kz);
			error = scale_object(current_object, kx, ky, kz);
		}
			break;

		case ROTATE_OBJECT:
		{
			double degrees;
			Axis axis;
			unpack_rotating_data(&action_data, &current_object, &degrees, &axis);
			error = rotate_object(current_object, degrees, axis);
		}
			break;
	}

	return error;
}