#include "figure.hpp"

#define TRIANGLE 	1
#define PACMAN		2


Figure* createFigure(int x, int y, int z, int shape){
	Figure* figure = new Figure;

	figure->X = x;
	figure->Y = y;
	figure->Z = z;

	figure->currX = (float) x;
	figure->currY = (float) y;
	figure->currZ = (float) z;

	switch(shape){
		case TRIANGLE:{
			float vertices[] = {-0.25, -0.25, -14.9, 0.25, -0.25, -14.9, 0.0, 0.25, -14.9};
			GLuint indices[] = {0, 1, 2};
			float color[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

			figure->VAO = set_vao(vertices, indices, color, 9);
			
			break;
		}

		default:
			break;
	}

	return figure;
}
