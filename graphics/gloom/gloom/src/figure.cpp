#include "figure.hpp"


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
			float triangles[] = {-0.25, -0.25, 0.25, -0.25, 0.0, 0.25};
			float color[] = {0.4, 0.0, 0.4, 1.0};


			figure->VAO = extrude(triangles, color, 1);
			figure->no_vertices = 3*3*7*1;
			break;
		}
		case STAR:{
			float triangles[] = {-0.32, 0.18, -0.2, -0.05, -0.1, 0.2,
									-0.1, 0.2, -0.2, -0.05, 0.0, 0.0,
								 -0.2, -0.05, -0.25, -0.3, 0.0, -0.2,
									0.0, -0.2, 0.0, 0.0, -0.2, -0.05,
								   0.0, -0.2, 0.25, -0.3, 0.2, -0.05,
									 0.2, -0.05, 0.0, 0.0, 0.0, -0.2,
									0.2, -0.05, 0.32, 0.18, 0.1, 0.2,
								   	  0.1, 0.2, 0.0, 0.0, 0.2, -0.05,
								       -0.1, 0.2, 0.0, 0.0, 0.1, 0.2,
									   0.1, 0.2, 0.0, 0.4, -0.1, 0.2};
			float color[] = {0.0, 0.3, 0.6, 1.0};


			figure->VAO = extrude(triangles, color, 10);
			figure->no_vertices = 3*3*7*10;

			break;
		}
		case PACMAN:{
			const int NUM_TRIANGLES = 270;
			float rad = (((270/NUM_TRIANGLES)*PI)/180);
			float sum_rad = 0;
			float radius = 0.4;
			float last_coord[] = {0.0, radius};
			float triangles[6*NUM_TRIANGLES];
			for (int i = 0; i < (6*NUM_TRIANGLES); i+=6){
				sum_rad += rad;
				triangles[i]		= 0.0;
				triangles[i+1]	= 0.0;
				triangles[i+2]	= last_coord[0];
				triangles[i+3]	= last_coord[1];
				triangles[i+4]	= -(sin(sum_rad)*radius);
				triangles[i+5]	= (cos(sum_rad)*radius);
				last_coord[0] = triangles[i+4];
				last_coord[1] = triangles[i+5];
			}

			float color[] = {1.0, 0.3, 0.3, 1.0};

			figure->VAO = extrude(triangles, color, NUM_TRIANGLES);
			figure->no_vertices = 3*3*7*NUM_TRIANGLES;

			break;
		}

		case WHITE_HEX:{
			float triangles[] = {-0.35, 0.0, -0.2, -0.3, 0.0, 0.0,
								  0.0, 0.0, -0.2, -0.3, 0.2, -0.3,
								   0.2, -0.3, 0.35, 0.0, 0.0, 0.0,
									0.0, 0.0, 0.35, 0.0, 0.2, 0.3,
									0.2, 0.3, -0.2, 0.3, 0.0, 0.0,
								  -0.2, 0.3, -0.35, 0.0, 0.0, 0.0};
			float color[] = {1.0, 1.0, 1.0, 1.0};


			figure->VAO = extrude(triangles, color, 6);
			figure->no_vertices = 3*3*7*6;
			break;
		}
		case BLACK_HEX:{
			float triangles[] = {-0.35, 0.0, -0.2, -0.3, 0.0, 0.0,
								  0.0, 0.0, -0.2, -0.3, 0.2, -0.3,
								   0.2, -0.3, 0.35, 0.0, 0.0, 0.0,
									0.0, 0.0, 0.35, 0.0, 0.2, 0.3,
									0.2, 0.3, -0.2, 0.3, 0.0, 0.0,
								  -0.2, 0.3, -0.35, 0.0, 0.0, 0.0};
			float color[] = {0.0, 0.0, 0.0, 1.0};


			figure->VAO = extrude(triangles, color, 6);
			figure->no_vertices = 3*3*7*6;
			break;
		}
		case PARALLELOGRAM:{
			float triangles[] = {-0.3, -0.3, 0.1, -0.3, -0.1, 0.3,
									0.1, -0.3, 0.3,0.3, -0.1, 0.3};
			float color[] = {0.4, 0.8, 0.0, 1.0};


			figure->VAO = extrude(triangles, color, 2);
			figure->no_vertices = 3*3*7*2;
			break;
		}
		case V_SHAPE:{
			float triangles[] = {-0.4, -0.4, -0.25, -0.4, 0.0, 0.4,
								   0.0, 0.4, -0.25, -0.4, 0.0, 0.2,
								    0.0, 0.4, 0.0, 0.2, 0.25, -0.4,
								   0.0, 0.4, 0.25, -0.4, 0.4, -0.4};
			float color[] = {1.0, 1.0 ,0.2, 1.0};


			figure->VAO = extrude(triangles, color, 4);
			figure->no_vertices = 3*3*7*4;
			break;
		}
		default:
			break;
		}
	return figure;
}

GLuint extrude(float* triangles, float* color, int num_triangles){
	float* vertices = new float[3*3*7*num_triangles];
	float* colors = new float[4*3*7*num_triangles];
	GLuint* indices = new GLuint[3*7*num_triangles];

	float z = 0.3;
	int vertice_index = 0;

	for (int i = 0; i < num_triangles*2*3; i+=6){
		float x1 = triangles[i];
		float y1 = triangles[i+1];

		float x2 = triangles[i+2];
		float y2 = triangles[i+3];

		float x3 = triangles[i+4];
		float y3 = triangles[i+5];

		// Surface
		vertices[vertice_index] = x1;
		vertices[vertice_index+1] = y1;
		vertices[vertice_index+2] = z;
		vertice_index += 3;

		vertices[vertice_index] = x2;
		vertices[vertice_index+1] = y2;
		vertices[vertice_index+2] = z;
		vertice_index += 3;

		vertices[vertice_index] = x3;
		vertices[vertice_index+1] = y3;
		vertices[vertice_index+2] = z;
		vertice_index += 3;

		// Side 1
		vertices[vertice_index] = x1;
		vertices[vertice_index+1] = y1;
		vertices[vertice_index+2] = z;
		vertice_index += 3;

		vertices[vertice_index] = x1;
		vertices[vertice_index+1] = y1;
		vertices[vertice_index+2] = 0.0;
		vertice_index += 3;

		vertices[vertice_index] = x2;
		vertices[vertice_index+1] = y2;
		vertices[vertice_index+2] = 0.0;
		vertice_index += 3;

		vertices[vertice_index] = x1;
		vertices[vertice_index+1] = y1;
		vertices[vertice_index+2] = z;
		vertice_index += 3;

		vertices[vertice_index] = x2;
		vertices[vertice_index+1] = y2;
		vertices[vertice_index+2] = 0.0;
		vertice_index += 3;

		vertices[vertice_index] = x2;
		vertices[vertice_index+1] = y2;
		vertices[vertice_index+2] = z;
		vertice_index += 3;

		// Side 2
		vertices[vertice_index] = x2;
		vertices[vertice_index+1] = y2;
		vertices[vertice_index+2] = z;
		vertice_index += 3;

		vertices[vertice_index] = x2;
		vertices[vertice_index+1] = y2;
		vertices[vertice_index+2] = 0.0;
		vertice_index += 3;

		vertices[vertice_index] = x3;
		vertices[vertice_index+1] = y3;
		vertices[vertice_index+2] = 0.0;
		vertice_index += 3;

		vertices[vertice_index] = x2;
		vertices[vertice_index+1] = y2;
		vertices[vertice_index+2] = z;
		vertice_index += 3;

		vertices[vertice_index] = x3;
		vertices[vertice_index+1] = y3;
		vertices[vertice_index+2] = 0.0;
		vertice_index += 3;

		vertices[vertice_index] = x3;
		vertices[vertice_index+1] = y3;
		vertices[vertice_index+2] = z;
		vertice_index += 3;

		// Side 3
		vertices[vertice_index] = x3;
		vertices[vertice_index+1] = y3;
		vertices[vertice_index+2] = z;
		vertice_index += 3;

		vertices[vertice_index] = x3;
		vertices[vertice_index+1] = y3;
		vertices[vertice_index+2] = 0.0;
		vertice_index += 3;

		vertices[vertice_index] = x1;
		vertices[vertice_index+1] = y1;
		vertices[vertice_index+2] = 0.0;
		vertice_index += 3;

		vertices[vertice_index] = x3;
		vertices[vertice_index+1] = y3;
		vertices[vertice_index+2] = z;
		vertice_index += 3;

		vertices[vertice_index] = x1;
		vertices[vertice_index+1] = y1;
		vertices[vertice_index+2] = 0.0;
		vertice_index += 3;

		vertices[vertice_index] = x1;
		vertices[vertice_index+1] = y1;
		vertices[vertice_index+2] = z;
		vertice_index += 3;
	}

	for(int j = 0; j < 3*7*num_triangles; j++){
		indices[j] = j;
	}

	for(int k = 0; k < 4*3*7*num_triangles; k += 4){
		colors[k] = color[0];
		colors[k+1] = color[1];
		colors[k+2] = color[2];
		colors[k+3] = color[3];
	}

	return set_vao(vertices, indices, colors, 3*3*7*num_triangles);

}

void updatePosition(Figure* figure, double time){
	float speed = 0.1;

	if((figure->X - figure->currX) > 0.05){
		figure->currX = figure->currX + speed;
	}else if ((figure->currX - figure->X) > 0.05){
		figure->currX = figure->currX - speed;
	}else{
		figure->currX = (float) figure->X;
	}

	if((figure->Y - figure->currY) > 0.05){
		figure->currY = figure->currY + speed;
	}else if ((figure->currY - figure->Y) > 0.05){
		figure->currY = figure->currY - speed;
	}else{
		figure->currY = (float) figure->Y;
	}

}
