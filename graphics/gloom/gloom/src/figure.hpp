#include "program.hpp"
#include "gloom/gloom.hpp"

#define TRIANGLE 	1
#define PACMAN		2

typedef struct Figure {
	// Current figure position
	float currX, currY, currZ;
	
	// Figure position on board
	int X, Y, Z;

	// Figure object
	GLuint VAO;
} Figure;


Figure* createFigure(int x, int y, int z, int shape);
void updatePosition(Figure* figure, double time);
