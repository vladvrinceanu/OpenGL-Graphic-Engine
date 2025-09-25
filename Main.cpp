#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


int main()
{
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // left  
		 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // right 
		 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
	   -0.5 / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
	   0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f// top   
	};

	GLuint indices[] = {  // note that we start from 0!
		0, 3, 5,   // first triangle
		3, 2, 4,
		5, 4, 1    // second triangle
	};
	// Initialize GLFW
	glfwInit();

	// Configure GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Load OpenGL function pointers with GLAD
	gladLoadGL();

	// Set the viewport
	glViewport(0, 0, 800, 600);

	Shader shaderProgram("default.vert", "default.frag");
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);	
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		VAO1.Bind();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();	
	shaderProgram.Delete();

	// Clean up and exit
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}