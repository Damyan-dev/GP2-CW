#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// Contains method that attribute to the creation of the in-game camera and allows for its adjustability.
struct Camera
{
public:
	Camera()
	{
	}

	void createCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	glm::vec3 getPos()
	{
		return this->pos;
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}

protected:
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};


