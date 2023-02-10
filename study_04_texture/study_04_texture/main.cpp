#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "Texture.h"
#include <string>


// vertex data point
float vertices[] = {
	-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
	0.0f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f,  0.5, 1.0f
};

void processInput(GLFWwindow* window);
int compileShaders(int shaderType, const char* shaderSource);
int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open GLFW window
	GLFWwindow* window = glfwCreateWindow(800, 600, "MY OpenGL Game", NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to open window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		printf("Failed to initialize GLEW");
		return -1;
	}

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	Shader shaders = { "VertexShader.txt", "FragmentShader.txt" };
	shaders.Build();

	// set position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// set color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	// set texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glViewport(0, 0, 800, 600);

	Texture tex1 = { "wall.jpg", false };
	Texture tex2 = { "awesomeface.png", true };
	shaders.Use();

	//const std::string t1 = "texture1";
	//const std::string t2 = "texture2";

	shaders.SetValue(std::string{ "texture1" }, 0);
	shaders.SetValue(std::string{ "texture2" }, 1);


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(211/255.0f, 211 / 255.0f, 211 / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		tex1.Bind(0);
		tex2.Bind(1);
		shaders.Use();
		glBindVertexArray(VAO);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glfwSwapBuffers(window); // Double Buffer
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

