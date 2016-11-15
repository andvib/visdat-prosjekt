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

	/*float x = 2;
	float triangle_coord[] = {-x, x, -15.0, -x, -x, -15.0, x, -x, -15.0,
				  			  x, -x, -15.0, x, x, -15.0, -x, x, -15.0,
							  x, -x, -15.0, x, x, -15.0, x, -x, -19.0,
							  x, x, -15.0, x, -x, -19.0, x, x, -19.0,
							  x, x, -15.0, x, x, -19.0, -x, x, -19.0,
							  x, x, -15.0, -x, x, -19.0, -x, x, -15.0};

	GLuint triangle_idx[] = {0, 1, 2, 3, 4, 5, 7, 6, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
	float triangle_color[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
							  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
							  0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
							  0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
	GLuint triangle = 0;
	triangle = set_vao(triangle_coord, triangle_idx, triangle_color, 60);*/

	float i = 0.0;

	glm::mat4x4 trans_mat(1.0f);

	GLuint board = createBoardVAO();
	Figure* triangle = createFigure(1, 1, 0, TRIANGLE);

    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
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

		glBindVertexArray(triangle->VAO);
		glUniformMatrix4fv(3, 1, GL_FALSE, glm::value_ptr(trans_mat*figure_translation));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		printGLError();

		glBindVertexArray(0);

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

    } if (key == GLFW_KEY_W){// && action == GLFW_PRESS){
		forward += 0.1;
	} if (key == GLFW_KEY_S){// && action == GLFW_PRESS){
		forward -= 0.1;
	} if (key == GLFW_KEY_A){// && action == GLFW_PRESS){
		horizontal -= 1.0;
	} if (key == GLFW_KEY_D){// && action == GLFW_PRESS){
		horizontal += 1.0;
	} if (key == GLFW_KEY_UP){// && action == GLFW_PRESS){
		vertical_rot -= 0.1;
	} if (key == GLFW_KEY_DOWN){// && action == GLFW_PRESS){
		vertical_rot += 0.1;
	} if (key == GLFW_KEY_LEFT){// && action == GLFW_PRESS){
		horizontal_rot -= 0.1;
	} if (key == GLFW_KEY_RIGHT){// && action == GLFW_PRESS){
		horizontal_rot += 0.1;
	} if (key == GLFW_KEY_Q){// && action == GLFW_PRESS){
		vertical += 1.0;
	}if (key == GLFW_KEY_E){// && action == GLFW_PRESS){
		vertical -= 1.0;
	}
}