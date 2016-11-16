#include "figure.hpp"

#define TRIANGLE 		1
#define STAR			2
#define PACMAN			3
#define	WHITE_HEX		4
#define BLACK_HEX		5
#define PARALLELOGRAM	6
#define A_ISH			7


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
		case STAR:{
			float vertices[] = {-0.32, 0.18, -14.9, -0.2, -0.05, -14.9, -0.1, 0.2, -14.9,
								0.0, 0.0, -14.9, -0.25, -0.3, -14.9, 0.0, -0.2, -14.9,
								0.25, -0.3, -14.9, 0.2, -0.05, -14.9, 0.32, 0.18, -14.9,
								0.1, 0.2, -14.9, 0.0, 0.4, -14.9};
			GLuint indices[] = {0, 1, 2, 2, 1, 3, 1, 4, 5, 5, 3, 1, 5, 6, 7, 7, 3, 5, 7, 8, 9, 9, 3, 7, 9, 10, 2, 2, 3, 9};
			float color[] = {0.0, 0.3, 0.6, 0.0, 0.3, 0.6, 0.0, 0.3, 0.6,
							0.0, 0.3, 0.6, 0.0, 0.3, 0.6, 0.0, 0.3, 0.6
							0.0, 0.3, 0.6, 0.0, 0.3, 0.6, 0.0, 0.3, 0.6
							0.0, 0.3, 0.6, 0.0, 0.3, 0.6, 1.0, 1.0, 1.0};
			figure->VAO = set_vao(vertices, indices, color, 33);
			break;
		}
		case PACMAN:{
			float vertices[] = {};
			GLuint indices[] = {};
			float color[] = {};
			figure->VAO = set_vao();
			break;
		}
		case WHITE_HEX:{
			float vertices[] = {-0.35, 0.0, -14.9, -0.2, -0.3, -14.9, 0.0, 0.0, -14.9, 0.2, -0.3, -14.9, 0.35, 0.0, -14.9, 0.2, 0.3, -14.9, -0.2, 0.3, -14.9};
			GLuint indices[] = {0, 1, 2, 2, 1, 3, 3, 4, 2, 2, 4, 5, 5, 2, 6, 6, 2, 0};
			float color[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
			figure->VAO = set_vao(vertices, indices, color, 21);
			break;
		}
		case BLACK_HEX:{
			float vertices[] = {-0.35, 0.0, -14.9, -0.2, -0.3, -14.9, 0.0, 0.0, -14.9, 0.2, -0.3, -14.9, 0.35, 0.0, -14.9, 0.2, 0.3, -14.9, -0.2, 0.3, -14.9};
			GLuint indices[] = {0, 1, 2, 2, 1, 3, 3, 4, 2, 2, 4, 5, 5, 2, 6, 6, 2, 0};
			float color[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0};
			figure->VAO = set_vao(vertices, indices, color, 21);
			break;
		}
		case PARALLELOGRAM:{
			float vertices[] = {-0.3, -0.3, -14.9, 0.1, -0.3, -14.9, -0.1, 0.3, -14.9, 0.3, 0.3, -14.9};
			GLuint indices[] = {0, 1, 2, 2, 1, 3};
			float color[] = {0.4, 0.8, 0, 0.4, 0.8, 0. 0.4, 0.8, 0. 0.4, 0.8, 0, 1.0, 1.0, 1.0};
			figure->VAO = set_vao(vertices, indices, color, 12);
			break;
		}
		case A_ISH:{
			float vertices[] = {-0.4, -0.4, -14.9, 0.4, -0.4, -14.9, 0.0, 0.4, -14.9, -0.25, -0.4, -14.9, 0.0, 0.2, -14.9, 0.25, -0.4, -14.9};
			GLuint indices[] = {0, 1, 2, 3, 4, 5};
			float color[] = {1.0, 1.0 ,0.2};
			figure->VAO = set_vao();
			break;
		}

		default:
			break;
	}

	return figure;
}

