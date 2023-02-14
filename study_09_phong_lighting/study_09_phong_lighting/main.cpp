#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "Texture.h"
#include <string>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp>

#include "Camera.h"

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 targetPos = glm::vec3(0.0f, 0.0f, -4.0f);
glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
//Camera camera = { cameraPos, worldUp, 523.0f, 101.0f };
Camera camera = { cameraPos, worldUp, 0.0f, -90.0f };
glm::vec3 lightCubePos(1.2f, 1.0f, 2.0f);
glm::vec3 objectPos(0.5f, 0.3f, 0.3f);
float fov = 45.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xpos, double ypos);
bool firstMove = true;

// vertex data point
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

void processInput(GLFWwindow* window);
int compileobjectShader(int shaderType, const char* objectShaderource);
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
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	// Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		printf("Failed to initialize GLEW");
		return -1;
	}

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int lightCubeVAO;
	
	// light Cube 
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//// set color
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	//glEnableVertexAttribArray(1);

	// set texture
	/*glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);*/

	Shader objectShader = { "VertexShader.glsl", "FragmentShader.glsl" };
	Shader lightCubeShader = { "lightCube.vert", "lightCube.frag" };
	objectShader.Build();
	lightCubeShader.Build();

	glViewport(0, 0, 800, 600);

	Texture tex1 = { "wall.jpg", false };
	Texture tex2 = { "awesomeface.png", true };
	/*objectShader.Use();
	lightCubeShader.Use();*/

	//const std::string t1 = "texture1";
	//const std::string t2 = "texture2";

	/*objectShader.SetValue(std::string{ "texture1" }, 0);
	objectShader.SetValue(std::string{ "texture2" }, 1);*/

	//transform setting
	//glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 lightCubeModel = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	//trans = glm::translate(trans, glm::vec3{ 1.0f, 1.0f, 0.0f });
	/*trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 1.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));*/

	//glm::vec3 cameraPos = { 0.0f, 0.0f, 3.0f };
	//glm::vec3 targetPos = { 0.0f, 0.0f, 0.0f };
	//glm::vec3 worldUp = { 0.0f, 1.0f, 0.0f };

	//objectShader.SetValue("view", glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)));
	/*std::cout << "camera pos::" << glm::to_string(camera.GetViewMatrix()) << std::endl;
	std::cout << "view pos::" << glm::to_string(glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f))) << std::endl;*/

	//model = glm::rotate(model, 45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -2.0f, -6.0f));
	glEnable(GL_DEPTH_TEST);
	lightCubeModel = glm::translate(lightCubeModel, lightCubePos);
	lightCubeModel = glm::scale(lightCubeModel, glm::vec3(0.2f));

	objectShader.SetValue("lightPos", lightCubePos);
	objectShader.SetValue("viewPos", cameraPos);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//tex1.Bind(0);
		//tex2.Bind(1);
		projection = glm::perspective(glm::radians(fov), (float)800 / (float)600, 0.1f, 100.0f);
		// object
		objectShader.Use();
		objectShader.SetValue("model", model);
		objectShader.SetValue("view", camera.GetViewMatrix());

		glm::vec3 lightColor = { 1.0f, 1.0f, 1.0f };
		objectShader.SetValue("projection", projection);
		objectShader.SetValue("objectColor", glm::vec3{ 1.0f, 0.5f, 0.31f });
		objectShader.SetValue("lightColor", lightColor);
		
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		lightCubeShader.Use();
		lightCubeShader.SetValue("projection", projection);
		lightCubeShader.SetValue("view", camera.GetViewMatrix());
		
		// a smaller cube
		lightCubeShader.SetValue("model", lightCubeModel);
		lightCubeShader.SetValue("lightColor", lightColor);
		// light cube
		glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		

		glfwSwapBuffers(window); // Double Buffer
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow* window)
{
	float cameraSpeed = 0.05f;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * targetPos;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * targetPos;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(targetPos, worldUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(targetPos, worldUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	double lastX = 0.0, lastY = 0.0, deltaX, deltaY;
	if (firstMove)
	{
		lastX = xpos;
		lastY = ypos;
		firstMove = false;
	}

	deltaX = xpos - lastX;
	deltaY = lastY - ypos ;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMove(deltaX, deltaY);


	std::cout << "posX = " << lastX <<",,," << lastY << std::endl;
}

void scroll_callback(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << "scoll_callback" << std::endl;
	fov -= (float)ypos;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}