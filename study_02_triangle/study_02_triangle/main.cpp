#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// vertex data point
float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

// vertex shader
const char* vertexShaderSource =
"#version 330 core									  \n"
"layout(location = 0) in vec3 aPos;					  \n"
"void main()										  \n"
"{gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}	  \n";

// fragment shader
const char* fragmentShaderSource =
"#version 330 core							   \n"
"out vec4 FragColor;						   \n"
"void main()								   \n"
"{FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}   \n";


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


	// complie shaders
	/*unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);*/
	unsigned int vertexShader;
	unsigned int fragmentShader;
	vertexShader = compileShaders(GL_VERTEX_SHADER, vertexShaderSource);
	fragmentShader = compileShaders(GL_FRAGMENT_SHADER, fragmentShaderSource);

	// create shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	

	glViewport(0, 0, 800, 600);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glUseProgram(shaderProgram);
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

int compileShaders(int shaderType, const char* shaderSource)
{
	//int shader = shaderType == "vertex" ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
	int success;
	char infoLog[512];
	// complie shaders
	unsigned int shader;
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILER::" << infoLog << std::endl;
		return -1;
	}

	return shader;
}