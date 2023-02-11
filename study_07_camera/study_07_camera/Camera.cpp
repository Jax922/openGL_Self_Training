#include "Camera.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp) : Position(position), Worldup(worldUp)
{
	Direction = glm::normalize(position - target);
	Right = glm::normalize(glm::cross(worldUp, Direction));
	Up = glm::normalize(glm::cross(Direction, Right));

	ViewMatrix = glm::lookAt(position, position + Direction, worldUp);
}

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, float pitch, float yaw) 
	: Position(position), Worldup(worldUp), Pitch(pitch), Yaw(yaw)
{
	
	/*Direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	Direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	Direction.y = sin(glm::radians(pitch));
	Direction = glm::normalize(Direction);

	Right = glm::normalize(glm::cross(Direction, worldUp));
	Up = glm::normalize(glm::cross(Right, Direction));*/
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front = glm::normalize(front);
	// also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(front, Worldup));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, front));

	ViewMatrix = glm::lookAt(Position, Position + front, Up);

}

void Camera::ProcessMouseMove(double deltaX, double deltaY)
{
	Yaw += deltaX * 0.0001f;
	Pitch += deltaY * 0.0001f;

	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front = glm::normalize(front);
	// also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(front, Worldup));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, front));

	ViewMatrix = glm::lookAt(Position, Position + front, Up);
}