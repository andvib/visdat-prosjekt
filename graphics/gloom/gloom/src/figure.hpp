#include "program.hpp"
#include "gloom/gloom.hpp"

#define TRIANGLE 		1
#define STAR			2
#define PACMAN			3
#define	WHITE_HEX		4
#define BLACK_HEX		5
#define PARALLELOGRAM	6
#define A_ISH			7

typedef struct Figure {
	// Current figure position
	float currX, currY, currZ;

	// Figure position on board
	int X, Y, Z;

	// Figure object
	GLuint VAO;
	int no_vertices;
} Figure;

GLuint extrude(float* triangles, float* color, int num_triangles);
Figure* createFigure(int x, int y, int z, int shape);
void updatePosition(Figure* figure, double time);
