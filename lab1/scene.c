#include "scene.h"

#include <stdlib.h>

error_t init_scene(Scene **scene_ptr, Object *obj_ptr)
{
	Scene *new_scene = (Scene*) malloc(sizeof(Scene));
	if (!new_scene) { return ALLOCATION_ERROR; }

	new_scene->object = obj_ptr;
	new_scene->command = TRANSPOSE;

	*scene_ptr = new_scene;
	return NO_ERROR;
}

error_t delete_scene(Scene *scene_ptr)
{
	if (!scene_ptr) { return SCENE_IS_NOT_INITIALISED; }

	delete_object(scene_ptr->object);
	free(scene_ptr);

	return NO_ERROR;
}

error_t get_command(Scene *scene_ptr, Command *command)
{
	if (!scene_ptr) { return SCENE_IS_NOT_INITIALISED; }

	*command = scene_ptr->command;

	return NO_ERROR;
}

error_t set_command(Scene *scene_ptr, Command new_command)
{
	if (!scene_ptr) { return SCENE_IS_NOT_INITIALISED; }

	scene_ptr->command = new_command;

	return NO_ERROR;
}

error_t get_object(Scene *scene_ptr, Object **object)
{
	if (!scene_ptr) { return SCENE_IS_NOT_INITIALISED; }

	*object = scene_ptr->object;

	return NO_ERROR;
}

