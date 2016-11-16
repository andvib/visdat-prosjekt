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
			/*float vertices[] = {-0.25, -0.25, 0.25, -0.25, 0.0, 0.25};
			GLuint indices[] = {0, 1, 2};
			float color[] = {1.0, 1.0, 1.0, 1.0};
			figure->VAO = set_vao(vertices, indices, color, 9);*/

			float triangles[] = {-0.25, -0.25, 0.25, -0.25, 0.0, 0.25};
			float color[] = {1.0, 1.0, 1.0, 1.0};


			figure->VAO = extrude(triangles, color, 1);

			break;
		}
		case STAR:{
			/*float vertices[] = {0 = -0.32, 0.18, -14.9,
														1= -0.2, -0.05, -14.9,
														2 = -0.1, 0.2, -14.9,
														3 = 0.0, 0.0, -14.9,
														4 = -0.25, -0.3, -14.
														5 = 0.0, -0.2, -14.9,
														6 = 0.25, -0.3, -14.9
														7 = 0.2, -0.05, -14.9,
														8 = 0.32, 0.18, -14.9,
														9 = 0.1, 0.2, -14.9,
														10 = 0.0, 0.4, -14.9};

			GLuint indices[] = {0, 1, 2, 2, 1, 3, 1, 4, 5, 5, 3, 1, 5, 6, 7, 7, 3, 5, 7, 8, 9, 9, 3, 7, 9, 10, 2, 2, 3, 9};
			float color[] = {0.0, 0.3, 0.6, 1.0, 0.0, 0.3, 0.6, 1.0, 0.0, 0.3, 0.6, 1.0,
                            0.0, 0.3, 0.6, 1.0, 0.0, 0.3, 0.6, 1.0, 0.0, 0.3, 0.6, 1.0,
                            0.0, 0.3, 0.6, 1.0, 0.0, 0.3, 0.6, 1.0, 0.0, 0.3, 0.6, 1.0,
							0.0, 0.3, 0.6, 1.0, 0.0, 0.3, 0.6, 1.0};
			figure->VAO = set_vao(vertices, indices, color, 100);*/

			float triangles[] = {-0.32, 0.18, -0.2, -0.05, -0.1, 0.2,
													-0.1, 0.2, -0.2, -0.05, 0.0, 0.0,
													-0.2, -0.05, -0.25, -0.3, 0.0, -0.2,
													0.0, -0.2, 0.0, 0.0, -0.2, -0.05,
													0.0, -0.2, 0.25, -0.3, 0.2, -0.05,
													0.2, -0.05, 0.0, 0.0, 0.0, -0.2,
													0.2, -0.05, 0.32, 0.18, 0.1, 0.2,
													0.1, 0.2, 0.0, 0.0, 0.2, -0.05,
													-0.1, 0.2, 0.0, 0.0, 0.1, 0.2,
													0.1, 0.2, 0.0, 0.4, -0.1, 0.2
													};
			float color[] = {0.0, 0.3, 0.6, 1.0};


			figure->VAO = extrude(triangles, color, 10);


			break;
		}
		case PACMAN:{
				break;
			}

		case WHITE_HEX:{
			/*float vertices[] = {-0.35, 0.0, -14.9, -0.2, -0.3, -14.9, 0.0, 0.0, -14.9, 0.2, -0.3, -14.9, 0.35, 0.0, -14.9, 0.2, 0.3, -14.9, -0.2, 0.3, -14.9};
			GLuint indices[] = {0, 1, 2, 2, 1, 3, 3, 4, 2, 2, 4, 5, 5, 6, 2, 6, 0, 2};
			float color[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
			figure->VAO = set_vao(vertices, indices, color, 54);*/

			float triangles[] = {-0.35, 0.0, -0.2, -0.3, 0.0, 0.0,
													0.0, 0.0, -0.2, -0.3, 0.2, -0.3,
													0.2, -0.3, 0.35, 0.0, 0.0, 0.0,
													0.0, 0.0, 0.35, 0.0, 0.2, 0.3,
													0.2, 0.3, -0.2, 0.3, 0.0, 0.0,
													-0.2, 0.3, -0.35, 0.0, 0.0, 0.0};
			float color[] = {1.0, 1.0, 1.0, 1.0};


			figure->VAO = extrude(triangles, color, 6);

			break;
		}
		case BLACK_HEX:{
			/*float vertices[] = {-0.35, 0.0, -14.9, -0.2, -0.3, -14.9, 0.0, 0.0, -14.9, 0.2, -0.3, -14.9, 0.35, 0.0, -14.9, 0.2, 0.3, -14.9, -0.2, 0.3, -14.9};
			GLuint indices[] = {0, 1, 2, 2, 1, 3, 3, 4, 2, 2, 4, 5, 5, 6, 2, 6, 0, 2};
			float color[] = {0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
			figure->VAO = set_vao(vertices, indices, color, 54);*/

			float triangles[] = {-0.35, 0.0, -0.2, -0.3, 0.0, 0.0,
													0.0, 0.0, -0.2, -0.3, 0.2, -0.3,
													0.2, -0.3, 0.35, 0.0, 0.0, 0.0,
													0.0, 0.0, 0.35, 0.0, 0.2, 0.3,
													0.2, 0.3, -0.2, 0.3, 0.0, 0.0,
													-0.2, 0.3, -0.35, 0.0, 0.0, 0.0};
			float color[] = {0.0, 0.0, 0.0, 1.0};


			figure->VAO = extrude(triangles, color, 6);

			break;
		}
		case PARALLELOGRAM:{
			/*float vertices[] = {-0.3, -0.3, -14.9, 0.1, -0.3, -14.9, -0.1, 0.3, -14.9, 0.3, 0.3, -14.9};
			GLuint indices[] = {0, 1, 2, 2, 1, 3};
            float color[] = {0.4, 0.8, 0.0, 1.0, 0.4, 0.8, 0.0, 1.0, 0.4, 0.8, 0.0, 1.0, 0.4, 0.8, 0.0, 1.0};
			figure->VAO = set_vao(vertices, indices, color, 18);*/

			float triangles[] = {-0.3, -0.3, 0.1, -0.3, -0.1, 0.3, 0.1, -0.3, 0.3,0.3, -0.1, 0.3};
			float color[] = {0.4, 0.8, 0.0, 1.0};


			figure->VAO = extrude(triangles, color, 2);
			break;
		}
		case A_ISH:{
			/*float vertices[] = {-0.4, -0.4, -14.9, -0.25, -0.4, -14.9, 0.0, 0.4, -14.9, 0.0, 0.2, -14.9, 0.25, -0.4, -14.9, 0.4, -0.4, -14.9};
			GLuint indices[] = {0, 1, 2, 2, 1, 3, 3, 4, 2, 2, 4, 5};
			float color[] = {1.0, 1.0 ,0.2, 1.0, 1.0, 1.0 ,0.2, 1.0, 1.0, 1.0 ,0.2, 1.0,
											1.0, 1.0 ,0.2, 0.0, 1.0, 1.0 ,0.2, 0.0, 1.0, 1.0 ,0.2, 0.0,};
			figure->VAO = set_vao(vertices, indices, color, 36);*/

			float triangles[] = {-0.4, -0.4, -0.25, -0.4, 0.0, 0.4, 0.0, 0.4, -0.25, -0.4, 0.0, 0.2, 0.0, 0.4, 0.0, 0.2, 0.25, -0.4, 0.0, 0.4, 0.25, -0.4, 0.4, -0.4};
			float color[] = {1.0, 1.0 ,0.2, 1.0};


			figure->VAO = extrude(triangles, color, 4);

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

	return set_vao(vertices, indices, colors, 700);

}
