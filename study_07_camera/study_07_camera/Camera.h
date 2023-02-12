#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);
	Camera(glm::vec3 position, glm::vec3 worldUp, float pitch, float yaw);

	inline glm::mat4 GetViewMatrix() const { return ViewMatrix; };

	void ProcessMouseMove(double deltaX, double deltaY);

public:
	glm::vec3 Position;
	glm::vec3 Direction;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	float Pitch;
	float Yaw;

private:
	glm::mat4 ViewMatrix;
};

