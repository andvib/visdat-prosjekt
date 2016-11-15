#include "board.hpp"


unsigned int createBoardVAO(){

	const unsigned int VERTICES_PER_SQUARE = 6;
	const unsigned int rows = 5;
	const unsigned int columns = 8;
	const unsigned int SQUARES = rows*columns;

	float* vertices = new float[SQUARES * VERTICES_PER_SQUARE*3];
	unsigned int* indices = new unsigned int[SQUARES * VERTICES_PER_SQUARE];
	float* colors = new float[8 * VERTICES_PER_SQUARE * SQUARES];
	
	int vertices_idx = 0;
	int indices_idx = 0;
	int colors_idx = 0;
	int r = 1;
	int b = 0;
	for (int i =  0; i < columns; i++){
		for (int j = 0; j < rows; j++){
			// TRIANGLE 1
			vertices[vertices_idx + 0] = i;
			vertices[vertices_idx + 1] = j;
			vertices[vertices_idx + 2] = -15.0;
			vertices_idx += 3;
			
			colors[colors_idx++] = r;
			colors[colors_idx++] = 0;
			colors[colors_idx++] = b;
			colors[colors_idx++] = 1;

			vertices[vertices_idx + 0] = i+1;
			vertices[vertices_idx + 1] = j;
			vertices[vertices_idx + 2] = -15.0;
			vertices_idx += 3;

			colors[colors_idx++] = r;
			colors[colors_idx++] = 0;
			colors[colors_idx++] = b;
			colors[colors_idx++] = 1;

			vertices[vertices_idx + 0] = i+1;
			vertices[vertices_idx + 1] = j+1;
			vertices[vertices_idx + 2] = -15.0;
			vertices_idx += 3;

			colors[colors_idx++] = r;
			colors[colors_idx++] = 0;
			colors[colors_idx++] = b;
			colors[colors_idx++] = 1;

			indices[indices_idx] = indices_idx;
			indices[indices_idx+1] = indices_idx + 1;
			indices[indices_idx+2] = indices_idx + 2;
			indices_idx += 3;

			// TRIANGLE 2
			vertices[vertices_idx + 0] = i;
			vertices[vertices_idx + 1] = j;
			vertices[vertices_idx + 2] = -15.0;
			vertices_idx += 3;
				
			colors[colors_idx++] = r;
			colors[colors_idx++] = 0;
			colors[colors_idx++] = b;
			colors[colors_idx++] = 1;
			
			vertices[vertices_idx + 0] = i+1;
			vertices[vertices_idx + 1] = j+1;
			vertices[vertices_idx + 2] = -15.0;
			vertices_idx += 3;

			colors[colors_idx++] = r;
			colors[colors_idx++] = 0;
			colors[colors_idx++] = b;
			colors[colors_idx++] = 1;

			vertices[vertices_idx + 0] = i;
			vertices[vertices_idx + 1] = j+1;
			vertices[vertices_idx + 2] = -15.0;
			vertices_idx += 3;

			colors[colors_idx++] = r;
			colors[colors_idx++] = 0;
			colors[colors_idx++] = b;
			colors[colors_idx++] = 1;

			indices[indices_idx] = indices_idx;
			indices[indices_idx+1] = indices_idx + 1;
			indices[indices_idx+2] = indices_idx + 2;
			indices_idx += 3;

			if(r==1){
				r = 0;
				b = 1;
			}else{
				r = 1;
				b = 0;
			}
		}
	}

	unsigned int vao_id = set_vao(vertices, indices, colors, SQUARES*3*3*2);
	
	delete[] vertices;
	delete[] indices;
	delete[] colors;

	return vao_id;
}
