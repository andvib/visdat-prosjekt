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

int no_of_figures = 6;
Figure* list_of_figures = new Figure[no_of_figures];
int fig_idx = 0;
Figure* chosen_fig;
	

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

static std::chrono::steady_clock::time_point _previousTimePoint = std::chrono::steady_clock::now();
double getTimeDeltaSeconds() {
	// Determine the current time
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	// Look up the time when the previous call to this function occurred.
	std::chrono::steady_clock::time_point previousTime = _previousTimePoint;

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
	shader.makeBasicShader("/home/shomeb/a/andreanv/Documents/visdat-prosjekt/graphics/gloom/gloom/shaders/simple.vert",
						   "/home/shomeb/a/andreanv/Documents/visdat-prosjekt/graphics/gloom/gloom/shaders/simple.frag");
	shader.link();

	float i = 0.0;

	glm::mat4x4 trans_mat(1.0f);

	GLuint board = createBoardVAO(ROWS, COLUMNS);
	Figure* triangle = createFigure(1, 1, 0, TRIANGLE);
	Figure* triangle2 = createFigure(3, 2, 0, STAR);
	Figure* triangle3 = createFigure(5, 3, 0, WHITE_HEX);
	Figure* triangle4 = createFigure(7, 1, 0, BLACK_HEX);
	Figure* triangle5 = createFigure(3, 1, 0, PARALLELOGRAM);
	Figure* triangle6 = createFigure(4, 4, 0, A_ISH);

	Figure* list_of_figures[] = {triangle, triangle2, triangle3, triangle4, triangle5, triangle6};
	double time_elapsed = 0;

    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
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
			chosen_fig->X += 1;
		}
	}if (key == GLFW_KEY_J && action == GLFW_PRESS){
		if(chosen_fig->X > 0){
			chosen_fig->X -= 1;
		}
	}if (key == GLFW_KEY_I && action == GLFW_PRESS){
		if(chosen_fig->Y < ROWS-1){
			chosen_fig->Y += 1;
		}
	}if (key == GLFW_KEY_K && action == GLFW_PRESS){
		if(chosen_fig->Y > 0){		
			chosen_fig->Y -= 1;
		}
	}
}
