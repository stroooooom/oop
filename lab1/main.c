#include "3dviewer.h"

int main(int argc, char **argv)
{
	int WINDOW_WIDTH = 500, WINDOW_HEIGHT = 500;
	int x_cord = 5, y_cord = 5;
	char *filename = argv[1];

	create_window(&argc, argv, WINDOW_WIDTH, WINDOW_HEIGHT, "OOP 1", x_cord, y_cord, filename);

	return 0;
}