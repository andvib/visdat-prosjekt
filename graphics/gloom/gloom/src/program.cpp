// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"
#include "board.hpp"
#include "figure.hpp"
#include "../vendor/glm/glm/mat4x4.hpp"
#include "../vendor/glm/glm/gtc/type_ptr.hpp"
#include "../vendor/glm/glm/gtx/transform.hpp"
#include "../vendor/glm/glm/vec3.hpp"
#include "../vendor/glm/glm/gtc/matrix_transform.hpp"


// Global variables for keypresses
float horizontal = 0.0;
float vertical = 0.0;
float forward = 1.0;
float horizontal_rot = 0.0;
float vertical_rot = 0.0;

int ROWS = 5;
int COLUMNS = 8;
int square_taken[5][8] = {0};

int no_of_figures = 16;
Figure* list_of_figures = new Figure[no_of_figures];
int fig_idx = 0;

Figure* chosen_fig;
Figure* curr_fig;
Figure* triangle;
Figure* triangle2;
Figure* triangle3;
Figure* triangle4;
Figure* triangle5;
Figure* triangle6;
Figure* triangle7;
Figure* triangle8;
Figure* triangle9;
Figure* triangle10;
Figure* triangle11;
Figure* triangle12;
Figure* triangle13;
Figure* triangle14;
Figure* triangle15;
Figure* triangle16;

int board_no = 1;
bool new_board_no = true;

GLuint set_vao(float* coord, GLuint* indices, float* colors, int arrayLength){
	// Create and bind VAO
	GLuint array = 0;
	glGenVertexArrays(1, &array);
	glBindVertexArray(array);

	// Create and bind VBO
	uint buffer = 0;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// Put data to VBO
	glBufferData(GL_ARRAY_BUFFER, arrayLength * sizeof(float), coord, GL_STATIC_DRAW);

	// Set vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Enable VBO
	glEnableVertexAttribArray(0);

	// Create and bind index VBO
	uint index_buffer = 0;
	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

	// Fill index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (arrayLength/3)*sizeof(GLuint), indices, GL_STATIC_DRAW);

	// Create and bind color VBO
	uint color_buffer = 0;
	glGenBuffers(1, &color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);

	// Fill color buffer
	glBufferData(GL_ARRAY_BUFFER, (arrayLength/3)*4*sizeof(GLuint), colors, GL_STATIC_DRAW);

	// Set vertex attributes
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	printGLError();

	return array;
}
// Copied from assignment 3
static std::chrono::steady_clock::time_point _previousTimePoint = std::chrono::steady_clock::now();
double getTimeDeltaSeconds() {
	// Determine the current time
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();

	// Calculate the number of nanoseconds that elapsed since the previous call to this function
	long long timeDelta = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - _previousTimePoint).count();
	// Convert the time delta in nanoseconds to seconds
	double timeDeltaSeconds = (double)timeDelta / 1000000000.0;

	// Store the previously measured current time
	_previousTimePoint = currentTime;

	// Return the calculated time delta in seconds
	return timeDeltaSeconds;
}


void runProgram(GLFWwindow* window)
{
    // Set GLFW callback mechanism(s)
    glfwSetKeyCallback(window, keyboardCallback);

    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    glEnable(GL_CULL_FACE);

    // Set default colour after clearing the colour buffer
    glClearColor(0.3f, 0.3f, 0.4f, 1.0f);

    // Set up your scene here (create Vertex Array Objects, etc.)
	Gloom::Shader shader;
	shader.makeBasicShader("../gloom/shaders/simple.vert",
						   "../gloom/shaders/simple.frag");
	shader.link();

	glm::mat4x4 trans_mat(1.0f);

	GLuint board = createBoardVAO(ROWS, COLUMNS);

    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
			if(new_board_no == true){
				new_board_no = false;

				// Create the figures for rendering based on which board is used
				switch (board_no) {
					case 1:{ // easy01.png
						triangle = createFigure(7, 0, 0, PACMAN);
						triangle2 = createFigure(7, 4, 0, PACMAN);
						triangle3 = createFigure(3, 3, 0, STAR);
						triangle4 = createFigure(6, 2, 0, STAR);
						triangle5 = createFigure(6, 1, 0, WHITE_HEX);
						triangle6 = createFigure(1, 0, 0, WHITE_HEX);
						triangle7 = createFigure(2, 1, 0, WHITE_HEX);
						triangle8 = createFigure(3, 2, 0, WHITE_HEX);
						triangle9 = createFigure(0, 0, 0, BLACK_HEX);
						triangle10 = createFigure(1, 2, 0, BLACK_HEX);
						triangle11 = createFigure(3, 1, 0, BLACK_HEX);
						triangle12 = createFigure(5, 3, 0, BLACK_HEX);
						triangle13 = createFigure(1, 3, 0, PARALLELOGRAM);
						triangle14 = createFigure(3, 4, 0, PARALLELOGRAM);
						triangle15 = createFigure(4, 4, 0, V_SHAPE);
						triangle16 = createFigure(4, 0, 0, TRIANGLE);
						break;
					}
					case 2: { //easy02.png
						triangle = createFigure(1, 1, 0, PACMAN);
						triangle2 = createFigure(2, 4, 0, PACMAN);
						triangle3 = createFigure(1, 2, 0, STAR);
						triangle4 = createFigure(4, 1, 0, STAR);
						triangle5 = createFigure(2, 3, 0, WHITE_HEX);
						triangle6 = createFigure(4, 2, 0, WHITE_HEX);
						triangle7 = createFigure(5, 3, 0, WHITE_HEX);
						triangle8 = createFigure(5, 4, 0, WHITE_HEX);
						triangle9 = createFigure(3, 2, 0, BLACK_HEX);
						triangle10 = createFigure(4, 3, 0, BLACK_HEX);
						triangle11 = createFigure(6, 2, 0, BLACK_HEX);
						triangle12 = createFigure(6, 3, 0, BLACK_HEX);
						triangle13 = createFigure(1, 3, 0, PARALLELOGRAM);
						triangle14 = createFigure(3, 0, 0, PARALLELOGRAM);
						triangle15 = createFigure(3, 1, 0, V_SHAPE);
						triangle16 = createFigure(2, 2, 0, TRIANGLE);
						break;
					}
					case 3: { // difficult01.png
						triangle = createFigure(0, 0, 0, PACMAN);
						triangle2 = createFigure(7, 0, 0, PACMAN);
						triangle3 = createFigure(2, 0, 0, STAR);
						triangle4 = createFigure(5, 0, 0, STAR);
						triangle5 = createFigure(0, 1, 0, WHITE_HEX);
						triangle6 = createFigure(1, 1, 0, WHITE_HEX);
						triangle7 = createFigure(2, 1, 0, WHITE_HEX);
						triangle8 = createFigure(3, 1, 0, WHITE_HEX);
						triangle9 = createFigure(4, 1, 0, BLACK_HEX);
						triangle10 = createFigure(5, 1, 0, BLACK_HEX);
						triangle11 = createFigure(6, 1, 0, BLACK_HEX);
						triangle12 = createFigure(7, 1, 0, BLACK_HEX);
						triangle13 = createFigure(1, 0, 0, PARALLELOGRAM);
						triangle14 = createFigure(6, 0, 0, PARALLELOGRAM);
						triangle15 = createFigure(3, 0, 0, V_SHAPE);
						triangle16 = createFigure(4, 0, 0, TRIANGLE);
						break;
					}
					case 4: { // difficult02.png
						triangle = createFigure(7, 1, 0, PACMAN);
						triangle2 = createFigure(7, 3, 0, PACMAN);
						triangle3 = createFigure(2, 1, 0, STAR);
						triangle4 = createFigure(4, 0, 0, STAR);
						triangle5 = createFigure(1, 4, 0, WHITE_HEX);
						triangle6 = createFigure(2, 3, 0, WHITE_HEX);
						triangle7 = createFigure(3, 0, 0, WHITE_HEX);
						triangle8 = createFigure(6, 0, 0, WHITE_HEX);
						triangle9 = createFigure(0, 2, 0, BLACK_HEX);
						triangle10 = createFigure(0, 3, 0, BLACK_HEX);
						triangle11 = createFigure(4, 3, 0, BLACK_HEX);
						triangle12 = createFigure(5, 3, 0, BLACK_HEX);
						triangle13 = createFigure(1, 3, 0, PARALLELOGRAM);
						triangle14 = createFigure(6, 3, 0, PARALLELOGRAM);
						triangle15 = createFigure(5, 1, 0, V_SHAPE);
						triangle16 = createFigure(3, 2, 0, TRIANGLE);
						break;
						}
					}
}

			Figure* list_of_figures[] = {triangle, triangle2, triangle3, triangle4,
																	triangle5, triangle6, triangle7, triangle8,
																	triangle9, triangle10, triangle11, triangle12,
																	triangle13, triangle14, triangle15, triangle16};

			double time_elapsed = 0;

			// resets all squares to zero for the figure_in_square function
			for (int i = 0; i<5; i++){
				for (int j = 0; j<8; j++){
					square_taken[i][j] = 0;
				}
			}
			// Updates square_taken if a figure is in the square
			for (int i = 0; i<no_of_figures; i++){
				square_taken[4-list_of_figures[i]->Y][list_of_figures[i]->X] = 1;
			}

		chosen_fig = list_of_figures[fig_idx];

        // Clear colour and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Calculate rotation matrices
		glm::mat4x4 rotation_y = glm::rotate(horizontal_rot, glm::vec3(0,1,0));
		glm::mat4x4 rotation_x = glm::rotate(vertical_rot, glm::vec3(1,0,0));
		glm::mat4x4 translation = glm::translate(glm::vec3(-horizontal, -vertical, forward));

		glm::mat4x4 projection = glm::perspective(glm::radians(90.0),
												  	4.0 / 3.0,
													1.0, 100.0);

		trans_mat = projection*translation*rotation_x*rotation_y;

		glm::mat4x4 figure_translation = glm::translate(glm::vec3(triangle->X+0.5, triangle->Y+0.5, 0.0));

		// Draw your scene here
		shader.activate();
		glUniform1f(5, 0.0);
		glUniformMatrix4fv(3, 1, GL_FALSE, glm::value_ptr(trans_mat));

		glBindVertexArray(board);
		glDrawElements(GL_TRIANGLES, 5*8*3*3, GL_UNSIGNED_INT, 0);
		printGLError();

		time_elapsed = getTimeDeltaSeconds();
		Figure* curr_figure;

		for(int j = 0; j < no_of_figures; j++){
			curr_figure = list_of_figures[j];

			updatePosition(curr_figure, time_elapsed);
			glBindVertexArray(curr_figure->VAO);
			figure_translation = glm::translate(glm::vec3(curr_figure->currX+0.5,
												curr_figure->currY+0.5, -15.0));
			glUniformMatrix4fv(3, 1, GL_FALSE, glm::value_ptr(trans_mat*figure_translation));
			if (j==fig_idx){
				glUniform1f(5, 1.0);
			} else {
				glUniform1f(5, 0.0);
			}
			glDrawElements(GL_TRIANGLES, curr_figure->no_vertices, GL_UNSIGNED_INT, 0);
			printGLError();
		}

		shader.deactivate();

        // Handle other events
        glfwPollEvents();

        // Flip buffers
        glfwSwapBuffers(window);
    }
}


void keyboardCallback(GLFWwindow* window, int key, int scancode,
                      int action, int mods)
{
    // Use escape key for terminating the GLFW window
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);

    } if (key == GLFW_KEY_W){
		forward += 0.1;
	} if (key == GLFW_KEY_S){
		forward -= 0.1;
	} if (key == GLFW_KEY_A){
		horizontal -= 1.0;
	} if (key == GLFW_KEY_D){
		horizontal += 1.0;
	} if (key == GLFW_KEY_UP){
		vertical_rot -= 0.1;
	} if (key == GLFW_KEY_DOWN){
		vertical_rot += 0.1;
	} if (key == GLFW_KEY_LEFT){
		horizontal_rot -= 0.1;
	} if (key == GLFW_KEY_RIGHT){
		horizontal_rot += 0.1;
	} if (key == GLFW_KEY_Q){
		vertical += 1.0;
	}if (key == GLFW_KEY_E){
		vertical -= 1.0;
	}if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
		fig_idx += 1;
		if(fig_idx >= no_of_figures){
			fig_idx = 0;
		}
	}if (key == GLFW_KEY_L && action == GLFW_PRESS){
		if(chosen_fig->X < COLUMNS-1){
			if (figure_in_square((chosen_fig->X)+1, chosen_fig->Y) == false){
				chosen_fig->X += 1;
			}
		}
	}if (key == GLFW_KEY_J && action == GLFW_PRESS){
		if(chosen_fig->X > 0){
			if (figure_in_square((chosen_fig->X)-1, chosen_fig->Y) == false){
				chosen_fig->X -= 1;
			}
		}
	}if (key == GLFW_KEY_I && action == GLFW_PRESS){
		if(chosen_fig->Y < ROWS-1){
			if (figure_in_square(chosen_fig->X, (chosen_fig->Y)+1) == false){
				chosen_fig->Y += 1;
			}
		}
	}if (key == GLFW_KEY_K && action == GLFW_PRESS){
		if(chosen_fig->Y > 0){
			if (figure_in_square(chosen_fig->X, (chosen_fig->Y)-1) == false){
				chosen_fig->Y -= 1;
			}
		}
	}
	if (key == GLFW_KEY_1 && action == GLFW_PRESS){
		board_no = 1;
		new_board_no = true;
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS){
		board_no = 2;
		new_board_no = true;
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS){
		board_no = 3;
		new_board_no = true;
	}
	if (key == GLFW_KEY_4 && action == GLFW_PRESS){
		board_no = 4;
		new_board_no = true;
	}
}

bool figure_in_square(int X, int Y){
	for (int i = 0; i <= no_of_figures; i++){
		if (square_taken[4-Y][X] == 1){
			return true;
		}
	}
	return false;
}
