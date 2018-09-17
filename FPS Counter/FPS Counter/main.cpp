#include <GLFW/glfw3.h>
#include <Windows.h>
#include <GL/GLU.h>
#include "Application.h"

void onWindowResized(GLFWwindow* window, int width, int height)
{
	if (height == 0) height = 1;						// Prevent A Divide By Zero By making Height Equal One

	glViewport(0, 0, width, height);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	gluOrtho2D(-width/2, width/2, -height / 2, height / 2);					// Calculate The Aspect Ratio Of The Window

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

int main(void)
{
	GLFWwindow *window;

	/* Initialize the Library */
	if (!glfwInit())
		return -1;

	/*Create a windowed mode window and its OpenGL context*/
	window = glfwCreateWindow(RESOLUTION_X, RESOLUTION_Y, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(window, onWindowResized);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	onWindowResized(window, RESOLUTION_X, RESOLUTION_Y);

	Application app;
	app.Start();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		app.Update();
		app.Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;
}