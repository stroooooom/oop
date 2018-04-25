#ifndef _SCENE_
#define _SCENE_

#include "object.h"
#include "program_error.h"

typedef enum {
	TRANSPOSE,
	SCALE,
	ROTATE,
} Command;

typedef struct {
	Object *object;
	Command command;
} Scene;

error_t init_scene(Scene **scene_ptr, Object *obj_ptr);
error_t delete_scene(Scene *scene_ptr);

error_t get_command(Scene *scene_ptr, Command *command);
error_t set_command(Scene *scene_ptr, Command new_command);

error_t get_object(Scene *scene_ptr, Object **object);

#endif